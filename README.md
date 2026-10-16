[简体中文](README.zh_CN.md)

# MagicBox Arduino BSP

Agent-oriented hardware baseline following [AI Passport](https://github.com/FoloToy/ai-passport): stable APIs, one pin map, minimal default entry and independent demo. This project supports only MagicBox HWv2.1.0 (ESP32-S3). Start with [AGENTS](AGENTS.md) and the [hardware/API guide](docs/BSP.md).

```text
lib/bsp/src/              reusable Arduino BSP and bsp_pins.h
src/main.cpp             minimal setup; no application behavior
examples/hardware-demo/   local tone, microphone, buttons, knob, RGB
skills/                  task-specific Agent workflows
```

```sh
python3 -m pip install platformio==6.1.19
pio run -e magicbox
pio run -e magicbox-demo
./tools/build.sh  # baseline + standalone demo
```

Pinned espressif32 6.7.0 / Arduino ESP32 2.0.16. Do not mix IDF5 new I2S drivers into this legacy-I2S project. No cloud protocols, Wi-Fi credentials, roles, product state machine, OTA or media bundles. MIT for FoloToy code; dependencies retain their licenses. A successful build is not device validation.
