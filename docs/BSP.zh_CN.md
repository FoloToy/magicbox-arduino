[English](BSP.md)

# MagicBox Arduino hardware and API

本项目仅支持 MagicBox HWv2.1.0 / ESP32-S3。硬件字段来自对应产品配置，没有导入网络配置或应用逻辑。

| Hardware | MagicBox HWv2.1.0 / ESP32-S3 |
| --- | --- |
| Mic BCLK / DATA / WS | 42 / 2 / 1 |
| Speaker BCLK / DATA / WS | 40 / 41 / 39 |
| RGB | 46 |
| Knob ADC | 8 |
| Physical buttons | 4 / 3 |

## API 与所有权

`bsp::begin()` 只初始化 GPIO、ADC 与 RGB。`button_pressed(index)` 返回原始低电平按键状态，未做消抖；消抖和按键业务由应用负责。`knob_raw()` 返回 0–4095 原始值，不改音量。`rgb(r,g,b)` 控制单颗 GRB 灯，必须先 begin。

音频显式调用 `audio_begin()`；I2S0 为 32-bit 单声道输入，转换为 16-bit PCM，I2S1 为 16-bit 单声道输出，16kHz。`audio_read` 每次最多 256 个采样；read/write 返回实际数量，可能短读/短写，应用需检查。超时单位为毫秒；一个任务拥有音频生命周期与读写，`audio_end` 释放两个端口。不能同时使用其他库占用这些 I2S 资源。麦克风左右声道与移位/增益还需真机确认。


## Demo 与验证

独立 Demo 启动时播放短低音量提示音并点亮绿色指示灯，持续报告按键边沿、旋钮原始值和麦克风峰值。115200 串口命令：`t` 播放提示音、`l` 循环红/绿/蓝/关闭、`r` 本地录音两秒后回放、`h` 查看帮助。启动还报告检测到的 Flash/PSRAM。它不自动录音回放、不发送 UID/音频到网络，不改量产身份分区。

运行 `./tools/build.sh` 编译默认工程与独立 Demo。真机验收需分别记录芯片/板号、串口日志、两键和旋钮全程、RGB 颜色、非零麦克风峰值以及可听清的回放。编译不能证明麦克风声道、音量、供电或 PCB 修订正确。上电引导管脚、Flash/PSRAM 与外部上拉也需确认。

N16 基线使用 16MB Flash：NVS 0x9000/24KB、PHY 0xF000/4KB、factory 0x10000/0xFF0000，无 OTA/文件系统分区。烧录前核对实体模组。

测试已有量产设备时保留其实际分区表及身份分区。本次实机包含 factory 和两个 4MB OTA 槽；诊断镜像写入未启用的 app0（0x410000），通过 otadata 选择启动，原 factory 镜像保留。本次测试不刷入仓库的独立开发分区表。

实体诊断操作：按 GPIO3 录音键后红灯录音两秒、蓝灯回放；按 GPIO4 按键播放提示音并循环 RGB 颜色。每个状态周期还输出旋钮最小/最大值。
