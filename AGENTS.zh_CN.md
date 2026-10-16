[English](AGENTS.md)

# Agent entry

先读 docs/BSP.zh_CN.md 与 lib/bsp/src/bsp_pins.h。首先运行 git status，保留用户修改。本仓库仅支持 MagicBox HWv2.1.0 / ESP32-S3。BSP 只实现 GPIO、总线、音频等硬件；应用放下游工程，示例放 examples。禁止提交凭据、私有应用代码、设备身份。先运行 tools/check_boundaries.py 再 tools/build.sh；分别报告编译、主机、真机与未验证项。烧录需对具体设备/镜像获得授权。

[按任务读取仓库内 Agent skills](skills/README.zh_CN.md)。
