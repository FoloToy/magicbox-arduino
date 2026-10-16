[简体中文](VALIDATION.zh_CN.md)

# Validation record — 2026-10-16

- Build: PASS — PlatformIO 6.1.19, espressif32 6.7.0, Arduino ESP32 2.0.16; baseline and standalone demo (two environments).
- Host tests: NOT RUN — no separate host-test harness.
- Architecture checks: PASS — minimal entry, BSP/application boundary, public dependencies and credential guard.
- Device tests: PARTIAL — one connected MagicBox identified as ESP32-S3 revision v0.2, stored HardwareVersion v2.1.0, 16MB Flash and approximately 8MB PSRAM. Only this hardware version is supported.

## Observed on the device

Both physical buttons are identified by the operator as Mode (GPIO4) and Voice (GPIO3); press/release and correct recording/playback LED transitions were observed. Startup tone and steady green LED passed operator acceptance. Flash was detected as 16MB; runtime reported 8386279 PSRAM bytes and a 256KB PSRAM pattern read/write test passed. On GPIO12/13, I2C addresses 0x19, 0x62 and 0x6b responded; 0x19 returned LIS3DH WHO_AM_I 0x33. The latter two addresses match the original battery/charger definitions but their functions were not exercised.

A local diagnostic compared 32-bit stereo input with the original ONLY_LEFT mono configuration, using a 1kHz speaker stimulus. Both captured it: stereo input RMS rose from 33.9 to 7093.6; mono from 70.4 to 7226.8. The second stereo slot was zero. This did not support changing the BSP's microphone channel or pins. The operator heard the recorded test-tone replay, then confirmed near-field speech recording/playback at 10–15cm, with low output volume. Human speech in the exported capture had low signal levels; a release transient dominated the peak. Idle heap was stable within each diagnostic run.

The standalone demo now supports holding Voice to record (up to ten seconds), releasing to replay, retaining raw PCM in RAM and exporting it over serial. Playback uses 8x gain by default, saturates at ±30000 and omits the final 80ms of hold recordings to reduce release noise. These adjustments affect the demo only. Raw PCM export is unchanged. Build and boundary checks passed. The operator reported 4x playback clear but quiet, then accepted 8x playback of the same recording as clear and sufficiently loud. That 102400-sample replay completed with ESP_OK and zero limited samples. The accepted 8x setting is now the demo default.

## Open acceptance items

Original-level speech recording/playback is audible but quiet; 8x diagnostic playback passed operator acceptance. Knob volume adjustment and hardware power switching passed operator acceptance: smooth quiet-to-loud changes, LED off at power-off and green after power-on. Serial captured two POWERON boots with ESP_OK audio initialization. GPIO8 first stopped near 1866, but later powered operation produced 1145, 1401 and 1609, with a maximum of 4095; the first stopping position is not treated as a fixed endpoint. The demo retains the original 0–4095 ADC span and scales tones and 8x speech replay to 5%–100%, with smoothing and per-block ramps. This policy belongs to the demo; BSP ADC/PCM remain raw. Periodic tones reset to disabled on boot, which caused one apparent silent-restart report; after re-enabling the test, the operator confirmed normal adjustment. Exact mechanical endpoint and sound-pressure calibration remain unverified. Battery/charger functions, power rails and long-duration reliability were not tested.

## Preservation and reproduction

The diagnostic application was written only to app0 at 0x410000 using the existing production partition table, then selected through otadata. The factory application remains intact. Before/after comparisons confirmed that the partition table and device identity partition were unchanged. Identity dumps are excluded from this repository. Do not flash the standalone development partition table onto a production unit as part of this procedure.

Reproduce compiler checks with `./tools/build.sh` and boundary checks with `python3 tools/check_boundaries.py`. Physical test commands and button controls are described in [BSP.md](BSP.md). Device results apply only to the tested unit and diagnostic image, not every peripheral or production application.
