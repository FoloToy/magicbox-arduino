[简体中文](VALIDATION.zh_CN.md)

# Validation record — 2026-10-16

Local compiler and source checks. No physical board was connected/tested.

- Build: PASS — PlatformIO 6.1.19, espressif32 6.7.0, Arduino ESP32 2.0.16; HW0.2.0 baseline + standalone demo (two environments).
- Host tests: NOT RUN — no separate host-test harness for this hardware adapter.
- Architecture checks: PASS — minimal default entry, BSP/application boundary, public dependency URLs and literal-credential guard.
- Device tests: NOT RUN.
- Unverified: physical revision, pins/rails, Flash/PSRAM, I2C, battery, keys/knob, microphone channel/gain/audible playback and fitted peripherals, including motor/haptic/NFC/touch/RTC/wake/4G where applicable. See the BSP guide for supported capabilities and known limits.

Reproduce: `./tools/build.sh`; architecture only: `python3 tools/check_boundaries.py`. Builds resolve through public dependencies without private repository access.
