[简体中文](BSP.zh_CN.md)

# MagicBox Arduino hardware and API

The sole supported board is MagicBox HWv2.1.0 / ESP32-S3. Hardware facts are extracted from its product configuration, excluding network configuration and application logic.

| Hardware | MagicBox HWv2.1.0 / ESP32-S3 |
| --- | --- |
| Mic BCLK / DATA / WS | 42 / 2 / 1 |
| Speaker BCLK / DATA / WS | 40 / 41 / 39 |
| RGB | 46 |
| Knob ADC | 8 |
| Physical buttons | 4 / 3 |

## API and ownership

`bsp::begin()` initializes GPIO, ADC and RGB only. `button_pressed(index)` returns raw active-low state without debouncing; debounce/event policy is application-owned. `knob_raw()` returns 0–4095 ADC counts without adjusting volume. `rgb(r,g,b)` controls one GRB pixel after begin.

Audio is opt-in via `audio_begin()`: I2S0 receives 32-bit left-channel samples and converts them to 16-bit PCM; I2S1 transmits 16-bit mono, both 16kHz. `audio_read` accepts at most 256 samples per call. Read/write return actual counts and may be partial; callers must check them. Timeouts are milliseconds. One task owns lifecycle and I/O; `audio_end` releases both ports. Other audio libraries must not own these controllers simultaneously. Microphone channel and shift/gain need device verification.


## Demo and validation

The independent demo starts a short quiet tone and a dim green pixel. It reports button edges, raw knob values and microphone peaks. Serial commands at 115200: `t` plays a tone, `l` cycles red/green/blue/off, `r` records and plays five seconds locally, `p` replays the retained recording, `d` exports it as framed base64 PCM over serial, `g` cycles playback gain through 1/2/4/8, `v` toggles a periodic quiet test tone for knob checks, and `h` prints help. The demo scales speaker output using GPIO8. Defaults retain the original 12-bit ADC span 0–4095 and map it to 5%–100% volume. The first stopping position read about 1866, but subsequent powered operation produced lower readings, so it is not treated as a fixed lower endpoint. Independently calibrated endpoints can be supplied with MAGICBOX_DEMO_KNOB_MIN_RAW / MAGICBOX_DEMO_KNOB_MAX_RAW. Four-sample averaging, smoothing and per-block ramps reduce abrupt volume changes. Both test tones and voice playback follow the knob; the BSP raw PCM API remains unchanged. Playback defaults to 8x with signed 32-bit arithmetic and saturation at ±30000; original PCM is retained for export. Hold-record audition omits the final 80ms to reduce the release click. The last recording stays in RAM until replaced or reset; the demo reserves one 320KB buffer after the first recording. Capture/playback logs include elapsed time. Startup reports detected Flash/PSRAM. It does not stream audio to a server, implement product recording behavior or modify identity partitions.

`./tools/build.sh` compiles the baseline and independent demo. Device acceptance records chip/revision, serial logs, both buttons/knob travel, RGB colors, nonzero microphone peak and audible playback. Builds cannot prove microphone channel, gain, power or PCB revision. Confirm boot-strapping pins, Flash/PSRAM and external pull-ups too.

The N16 baseline uses a 16MB Flash layout: NVS 0x9000/24KB, PHY 0xF000/4KB, factory 0x10000/0xFF0000. There is no OTA/filesystem partition. Confirm the physical module before flashing.

For device testing on an existing production unit, keep its actual partition table and identity partitions. The verified unit has a factory application plus two 4MB OTA slots; the diagnostic image is initially written to inactive app0 at 0x410000 and selected using otadata. The original factory image remains available. The standalone development partition table is not flashed during this test.

Physical diagnostic controls: hold Voice (GPIO3) to record (red), then release to play back (blue), with a ten-second limit. Brief queued audio and the initial press transient are discarded. Press Mode (GPIO4) for a tone and RGB cycle. Each status period also reports knob min/max.

The periodic tone is a temporary test mode, disabled on every boot; serial `v` toggles it again. Boot plays one knob-scaled tone, which may be very quiet at low settings. The rotary power switch is hardware-controlled.
