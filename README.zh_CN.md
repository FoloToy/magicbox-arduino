[English](README.md)

# MagicBox Arduino BSP

按 AI Passport 面向 Agent 的设计组织：稳定硬件 API、唯一引脚表、最小默认入口和独立 Demo。支持 MagicBox HW0.2.0（ESP32）、Pro HW1.0.0、Pro2 HW2.1.0（ESP32-S3）。先读 [AGENTS](AGENTS.md) 和 [硬件/API 指南](docs/BSP.zh_CN.md)。

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
# Pro / Pro2: change environment to magicbox-pro[-demo] / magicbox-pro2[-demo]
./tools/build.sh  # all six environments
```

使用 espressif32 6.7.0 / Arduino ESP32 2.0.16；不得和 IDF 5 的新 I2S 驱动混用。BSP 不含云协议、Wi-Fi 凭据、角色/录音业务状态机、OTA 或媒体文件。MIT 许可；依赖保留原许可。编译通过不代表真机通过。
