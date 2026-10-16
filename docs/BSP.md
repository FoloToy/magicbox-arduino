[简体中文](BSP.zh_CN.md)

# MagicBox Arduino hardware and API

Profiles are extracted from product hardware fields, excluding network configuration and application logic. Pro and Pro2 speaker DATA/WS differ: select the exact board.

| Hardware | HW0.2.0 / ESP32 | Pro HW1.0.0 / S3 | Pro2 HW2.1.0 / S3 |
| --- | --- | --- | --- |
| Mic BCLK / DATA / WS | 23 / 22 / 21 | 42 / 2 / 1 | 42 / 2 / 1 |
| Speaker BCLK / DATA / WS | 2 / 15 / 4 | 40 / 39 / 41 | 40 / 41 / 39 |
| RGB | 27 | 46 | 46 |
| Knob ADC | 34 | 8 | 8 |
| Physical buttons | 36 / 14 / 26 | 4 / 3 / 6 | 4 / 3 / 6 |
| I2C SDA / SCL | not exposed | 12 / 13 | 12 / 13 |
| Accelerometer IRQ | not exposed | 14 | 14 |

## API and ownership

`bsp::begin()` initializes GPIO, ADC and RGB only. `button_pressed(index)` returns raw active-low state without debouncing; debounce/event policy is application-owned. GPIO36 on HW0.2.0 needs the PCB external pull-up. `knob_raw()` returns 0–4095 ADC counts without adjusting volume. `rgb(r,g,b)` controls one GRB pixel after begin.

Audio is opt-in via `audio_begin()`: I2S0 receives 32-bit left-channel samples and converts them to 16-bit PCM; I2S1 transmits 16-bit mono, both 16kHz. `audio_read` accepts at most 256 samples per call. Read/write return actual counts and may be partial; callers must check them. Timeouts are milliseconds. One task owns lifecycle and I/O; `audio_end` releases both ports. Other audio libraries must not own these controllers simultaneously. Microphone channel and shift/gain need device verification.

Pro/Pro2 expose opt-in `i2c_begin` and `i2c_read`; serialize with other Wire users. HW0.2.0 returns unsupported. No battery/accelerometer driver is claimed by these generic bus APIs: confirm the fitted device/revision before adding a dedicated adapter. Do not reuse charging or sleep registers from another product.

## Demo and validation

The independent demo plays a short quiet square-wave tone, logs three inputs/knob, captures microphone samples and reports their peak, and sets a dim green pixel. It does not stream audio to a server, implement product recording behavior or modify identity partitions.

`./tools/build.sh` compiles all six combinations. Device acceptance records chip/revision, serial logs, all buttons/knob travel, RGB colors, nonzero microphone peak and audible playback. Builds cannot prove microphone channel, gain, power or PCB revision. Confirm boot-strapping pins, Flash/PSRAM and external pull-ups too.

The N16 baseline uses a 16MB Flash layout: NVS 0x9000/24KB, PHY 0xF000/4KB, factory 0x10000/0xFF0000. There is no OTA/filesystem partition. Confirm the physical module before flashing.
