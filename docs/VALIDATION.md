[简体中文](VALIDATION.zh_CN.md)

# Validation record — 2026-10-16

- Build: PASS — PlatformIO 6.1.19, espressif32 6.7.0, Arduino ESP32 2.0.16; baseline and standalone demo (two environments).
- Host tests: NOT RUN — no separate host-test harness.
- Architecture checks: PASS — minimal entry, BSP/application boundary, public dependencies and credential guard.
- Device tests: PARTIAL — one connected MagicBox identified as ESP32-S3 revision v0.2, stored HardwareVersion v2.1.0, 16MB Flash and approximately 8MB PSRAM. Only this hardware version is supported.

## Observed on the device

Both physical buttons (GPIO4 and GPIO3) produced press/release edges. Audio initialization and tone transmission returned ESP_OK; the operator heard the startup tone and confirmed a steady green LED. Microphone reads returned nonzero samples, with a peak of 18743 observed during the session. Two serial-triggered recordings each captured and transmitted 32000 samples at 16kHz with ESP_OK; this alone does not establish audible playback quality. The operator subsequently reported an issue with recording/playback or lighting; exact symptoms remain under investigation. Idle heap remained stable within each monitored firmware run.

## Open acceptance items

Audible recording/playback and the full RGB sequence have not passed operator acceptance. GPIO8 readings covered only 3752–4095 in the initial session and remained 4095 in the later session; full knob travel is unverified. The operator confirms two buttons and a rotary end stop that switches the device off. The demo reads raw ADC only and does not implement volume adjustment. Do not infer a failed potentiometer or a verified ADC mapping from these readings alone. Power rails, battery, optional I2C peripherals and long-duration reliability were not tested.

## Preservation and reproduction

The diagnostic application was written only to app0 at 0x410000 using the existing production partition table, then selected through otadata. The factory application remains intact. Before/after comparisons confirmed that the partition table and device identity partition were unchanged. Identity dumps are excluded from this repository. Do not flash the standalone development partition table onto a production unit as part of this procedure.

Reproduce compiler checks with `./tools/build.sh` and boundary checks with `python3 tools/check_boundaries.py`. Physical test commands and button controls are described in [BSP.md](BSP.md). Device results apply only to the tested unit and diagnostic image, not every peripheral or production application.
