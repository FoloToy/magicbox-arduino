// Serial diagnostics and a quiet local tone. No cloud/application behavior.
#include <Arduino.h>
#include <bsp.h>
void setup() {
    Serial.begin(115200);
    bsp::begin();
    Serial.println(bsp::board_name());
    auto err = bsp::audio_begin();
    Serial.printf("audio init: %s\n", esp_err_to_name(err));
    if (err == ESP_OK) {
        int16_t pcm[1600];
        for (unsigned i = 0; i < 1600; i++)
            pcm[i] = i % 32 < 16 ? 1000 : -1000;
        size_t count;
        err = bsp::audio_write(pcm, 1600, &count, 1000);
        Serial.printf("tone: %s samples=%u\n", esp_err_to_name(err), (unsigned)count);
    }
    bsp::rgb(0, 8, 0);
}
void loop() {
    Serial.printf("knob=%u buttons:", bsp::knob_raw());
    for (unsigned i = 0; i < 3; i++)
        Serial.printf(" %u", bsp::button_pressed(i));
    int16_t pcm[256];
    size_t count = 0;
    auto err = bsp::audio_read(pcm, 256, &count, 100);
    int peak = 0;
    for (size_t i = 0; i < count; i++) {
        int value = pcm[i];
        if (value < 0)
            value = -value;
        if (value > peak)
            peak = value;
    }
    Serial.printf(" mic=%s samples=%u peak=%d\n", esp_err_to_name(err), (unsigned)count, peak);
    delay(1000);
}
