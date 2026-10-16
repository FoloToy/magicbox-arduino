---
name: magicbox-arduino-build
description: magicbox-arduino 的 build 工作流。
---

[English](SKILL.md)

# 构建

先运行 `python3 tools/check_boundaries.py`，再执行 `./tools/build.sh`。构建全部六种板卡/示例组合。检查退出码、警告及镜像/分区适配。编译、主机测试、真机测试与剩余验证分别报告，不能用编译推断硬件行为。
