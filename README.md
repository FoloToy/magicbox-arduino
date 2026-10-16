# Archived — moved to MagicBox

This repository is archived and retains only the historical Arduino BSP on `main`. **Use the maintained [FoloToy/MagicBox](https://github.com/FoloToy/MagicBox) repository for new development and issues.**

- [Multi-generation BSPs — main](https://github.com/FoloToy/MagicBox/tree/main): explicit model, chip and PCB revision profiles for M09 / ESP32-S3 / HW2.1.0 and the C5 reference hardware.
- [Original M09 Arduino BSP and examples](https://github.com/FoloToy/MagicBox/tree/main/legacy/m09-arduino): the Arduino implementation is preserved in the new repository.
- [M09 XiaoZhi — new repository only](https://github.com/FoloToy/MagicBox/tree/demo/xiaozhi): use the `demo/xiaozhi` branch in **FoloToy/MagicBox**. The former `codex/xiaozhi-port` branch has been removed from this Arduino repository.

Select the complete hardware profile; another ESP32-S3 PCB is not automatically compatible. The C5 model mapping is pending confirmation, and C5 XiaoZhi is not yet ported. The content below describes the historical Arduino project.

---

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
