[English](BSP.md)

# MagicBox Arduino hardware and API

本项目仅支持 MagicBox HW0.2.0 / ESP32。硬件字段来自对应产品配置，没有导入网络配置或应用逻辑。

| Hardware | MagicBox HW0.2.0 / ESP32 |
| --- | --- |
| Mic BCLK / DATA / WS | 23 / 22 / 21 |
| Speaker BCLK / DATA / WS | 2 / 15 / 4 |
| RGB | 27 |
| Knob ADC | 34 |
| Physical buttons | 36 / 14 / 26 |

## API 与所有权

`bsp::begin()` 只初始化 GPIO、ADC 与 RGB。`button_pressed(index)` 返回原始低电平按键状态，未做消抖；消抖和按键业务由应用负责。0.2.0 的 GPIO36 无内部上拉，依赖 PCB 外部上拉。`knob_raw()` 返回 0–4095 原始值，不改音量。`rgb(r,g,b)` 控制单颗 GRB 灯，必须先 begin。

音频显式调用 `audio_begin()`；I2S0 为 32-bit 单声道输入，转换为 16-bit PCM，I2S1 为 16-bit 单声道输出，16kHz。`audio_read` 每次最多 256 个采样；read/write 返回实际数量，可能短读/短写，应用需检查。超时单位为毫秒；一个任务拥有音频生命周期与读写，`audio_end` 释放两个端口。不能同时使用其他库占用这些 I2S 资源。麦克风左右声道与移位/增益还需真机确认。


## Demo 与验证

独立 Demo 播放短低音量方波，打印三键与旋钮，采集短麦克风数据并打印峰值，以绿色指示灯显示初始化。它不自动录音回放、不发送 UID/音频到网络，不改量产身份分区。

运行 `./tools/build.sh` 编译默认工程与独立 Demo。真机验收需分别记录芯片/板号、串口日志、三键和旋钮全程、RGB 颜色、非零麦克风峰值以及可听清的回放。编译不能证明麦克风声道、音量、供电或 PCB 修订正确。上电引导管脚、Flash/PSRAM 与外部上拉也需确认。

N16 基线使用 16MB Flash：NVS 0x9000/24KB、PHY 0xF000/4KB、factory 0x10000/0xFF0000，无 OTA/文件系统分区。烧录前核对实体模组。
