// Interactive local hardware diagnostics; no cloud or product behavior.
#include <Arduino.h>
#include <bsp.h>
#include <bsp_pins.h>
#include <stdlib.h>

static bool audio_ready;
static bool keys[BSP_KEY_COUNT];
static uint32_t last_status;
static uint16_t knob_min = 4095, knob_max = 0;

static void tone() {
    if (!audio_ready)
        return;
    int16_t pcm[1600];
    for (unsigned i = 0; i < 1600; ++i)
        pcm[i] = i % 32 < 16 ? 1000 : -1000;
    size_t count = 0;
    auto err = bsp::audio_write(pcm, 1600, &count, 1000);
    Serial.printf("TONE result=%s samples=%u\n", esp_err_to_name(err), (unsigned)count);
}

static void colors() {
    const uint8_t rgb[][3] = {{12, 0, 0}, {0, 12, 0}, {0, 0, 12}, {0, 0, 0}};
    const char *names[] = {"RED", "GREEN", "BLUE", "OFF"};
    for (unsigned i = 0; i < 4; ++i) {
        Serial.printf("LED %s\n", names[i]);
        bsp::rgb(rgb[i][0], rgb[i][1], rgb[i][2]);
        delay(800);
    }
    bsp::rgb(0, 8, 0);
}

static void record_playback() {
    if (!audio_ready)
        return;
    const size_t samples = BSP_SAMPLE_RATE * 2;
    int16_t *pcm = static_cast<int16_t *>(malloc(samples * sizeof(int16_t)));
    if (!pcm) {
        Serial.println("RECORD no memory");
        return;
    }
    Serial.println("RECORD start: speak for two seconds");
    bsp::rgb(12, 0, 0);
    size_t used = 0;
    int peak = 0;
    esp_err_t err = ESP_OK;
    while (used < samples) {
        size_t count = 0;
        const size_t chunk = min(static_cast<size_t>(256), samples - used);
        err = bsp::audio_read(pcm + used, chunk, &count, 200);
        if (err != ESP_OK || !count)
            break;
        for (size_t i = 0; i < count; ++i) {
            int value = pcm[used + i];
            if (value < 0)
                value = -value;
            if (value > peak)
                peak = value;
        }
        used += count;
    }
    Serial.printf("RECORD result=%s samples=%u peak=%d\n", esp_err_to_name(err), (unsigned)used,
                  peak);
    bsp::rgb(0, 0, 12);
    size_t sent = 0;
    while (sent < used) {
        size_t count = 0;
        err = bsp::audio_write(pcm + sent, min(static_cast<size_t>(256), used - sent), &count, 200);
        if (err != ESP_OK || !count)
            break;
        sent += count;
    }
    Serial.printf("PLAYBACK result=%s samples=%u\n", esp_err_to_name(err), (unsigned)sent);
    bsp::rgb(0, 8, 0);
    free(pcm);
}

void setup() {
    Serial.begin(115200);
    bsp::begin();
    Serial.printf("BOARD %s flash=%u psram=%u heap=%u\n", bsp::board_name(), ESP.getFlashChipSize(),
                  ESP.getPsramSize(), ESP.getFreeHeap());
    auto err = bsp::audio_begin();
    audio_ready = err == ESP_OK;
    Serial.printf("AUDIO init=%s\n", esp_err_to_name(err));
    Serial.println("COMMANDS t=tone l=RGB-cycle r=2s-record/playback h=help");
    tone();
    bsp::rgb(0, 8, 0);
}

void loop() {
    while (Serial.available()) {
        const char command = Serial.read();
        if (command == 't')
            tone();
        else if (command == 'l')
            colors();
        else if (command == 'r')
            record_playback();
        else if (command == 'h')
            Serial.println("COMMANDS t=tone l=RGB-cycle r=2s-record/playback h=help");
    }
    for (unsigned i = 0; i < BSP_KEY_COUNT; ++i) {
        bool pressed = bsp::button_pressed(i);
        if (pressed != keys[i]) {
            keys[i] = pressed;
            Serial.printf("BUTTON index=%u gpio=%d pressed=%u\n", i, BSP_KEYS[i], pressed);
            if (pressed && i == 1)
                record_playback();
            else if (pressed && i == 0) {
                tone();
                colors();
            }
        }
    }
    const uint16_t knob = bsp::knob_raw();
    knob_min = min(knob_min, knob);
    knob_max = max(knob_max, knob);
    if (millis() - last_status >= 1000) {
        last_status = millis();
        int16_t pcm[256];
        size_t count = 0;
        int peak = 0;
        auto err = bsp::audio_read(pcm, 256, &count, 100);
        for (size_t i = 0; i < count; ++i) {
            int value = pcm[i];
            if (value < 0)
                value = -value;
            if (value > peak)
                peak = value;
        }
        Serial.printf("STATUS knob=%u mic=%s samples=%u peak=%d heap=%u\n", knob,
                      esp_err_to_name(err), (unsigned)count, peak, ESP.getFreeHeap());
        Serial.printf("KNOB min=%u max=%u\n", knob_min, knob_max);
        knob_min = 4095;
        knob_max = 0;
    }
    delay(10);
}
