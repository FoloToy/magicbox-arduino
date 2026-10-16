# 已归档 — 项目迁移至 MagicBox

本仓库已归档，`main` 仅保留原 Arduino BSP，供历史参考。**后续开发、使用和问题反馈，请前往新仓库 [FoloToy/MagicBox](https://github.com/FoloToy/MagicBox)。**

- [多代硬件 BSP：main 分支](https://github.com/FoloToy/MagicBox/tree/main)：按型号、芯片和 PCB 版本区分，目前包含 M09 / ESP32-S3 / HW2.1.0 和 C5 参考硬件配置。
- [M09 原 Arduino BSP 和示例](https://github.com/FoloToy/MagicBox/tree/main/legacy/m09-arduino)：原 Arduino 实现已保留在新仓库中。

请显式选择完整硬件配置，同为 S3 不代表其他 PCB 版本兼容。C5 的产品型号仍待确认。以下内容为原 Arduino 工程的历史说明。

---

[English](README.md)

# MagicBox Arduino BSP

按 AI Passport 面向 Agent 的设计组织：稳定硬件 API、唯一引脚表、最小默认入口和独立 Demo。仅支持 MagicBox HWv2.1.0（ESP32-S3）这一个版本。先读 [AGENTS](AGENTS.md) 和 [硬件/API 指南](docs/BSP.zh_CN.md)。

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

使用 espressif32 6.7.0 / Arduino ESP32 2.0.16；不得和 IDF 5 的新 I2S 驱动混用。BSP 不含云协议、Wi-Fi 凭据、角色/录音业务状态机、OTA 或媒体文件。MIT 许可；依赖保留原许可。编译通过不代表真机通过。
