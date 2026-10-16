[English](BSP.md)

# MagicBox Arduino hardware and API

这些 profile 来自产品配置的硬件字段；没有导入其中的网络配置或应用逻辑。Pro 和 Pro2 的喇叭 DATA/WS 不同，必须选择准确版本。

| Hardware | HW0.2.0 / ESP32 | Pro HW1.0.0 / S3 | Pro2 HW2.1.0 / S3 |
| --- | --- | --- | --- |
| Mic BCLK / DATA / WS | 23 / 22 / 21 | 42 / 2 / 1 | 42 / 2 / 1 |
| Speaker BCLK / DATA / WS | 2 / 15 / 4 | 40 / 39 / 41 | 40 / 41 / 39 |
| RGB | 27 | 46 | 46 |
| Knob ADC | 34 | 8 | 8 |
| Physical buttons | 36 / 14 / 26 | 4 / 3 / 6 | 4 / 3 / 6 |
| I2C SDA / SCL | not exposed | 12 / 13 | 12 / 13 |
| Accelerometer IRQ | not exposed | 14 | 14 |

## API 与所有权

`bsp::begin()` 只初始化 GPIO、ADC 与 RGB。`button_pressed(index)` 返回原始低电平按键状态，未做消抖；消抖和按键业务由应用负责。0.2.0 的 GPIO36 无内部上拉，依赖 PCB 外部上拉。`knob_raw()` 返回 0–4095 原始值，不改音量。`rgb(r,g,b)` 控制单颗 GRB 灯，必须先 begin。

音频显式调用 `audio_begin()`；I2S0 为 32-bit 单声道输入，转换为 16-bit PCM，I2S1 为 16-bit 单声道输出，16kHz。`audio_read` 每次最多 256 个采样；read/write 返回实际数量，可能短读/短写，应用需检查。超时单位为毫秒；一个任务拥有音频生命周期与读写，`audio_end` 释放两个端口。不能同时使用其他库占用这些 I2S 资源。麦克风左右声道与移位/增益还需真机确认。

Pro/Pro2 可显式调用 `i2c_begin` 与 `i2c_read` 访问板载总线；调用方与其他 Wire 使用者必须串行。0.2.0 返回不支持；没有虚构的电池/加速度 API：具体器件与修订需按实体板和配置确认，再添加独立硬件适配。没有从其他产品套用电池充电或低功耗寄存器。

## Demo 与验证

独立 Demo 播放短低音量方波，打印三键与旋钮，采集短麦克风数据并打印峰值，以绿色指示灯显示初始化。它不自动录音回放、不发送 UID/音频到网络，不改量产身份分区。

运行 `./tools/build.sh` 编译六种组合。真机验收需分别记录芯片/板号、串口日志、三键和旋钮全程、RGB 颜色、非零麦克风峰值以及可听清的回放。编译不能证明麦克风声道、音量、供电或 PCB 修订正确。上电引导管脚、Flash/PSRAM 与外部上拉也需确认。

N16 基线使用 16MB Flash：NVS 0x9000/24KB、PHY 0xF000/4KB、factory 0x10000/0xFF0000，无 OTA/文件系统分区。烧录前核对实体模组。
