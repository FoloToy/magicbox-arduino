---
name: magicbox-arduino-build
description: Compile the baseline and its standalone diagnostic demo for magicbox-arduino.
---

[简体中文](SKILL.zh_CN.md)

# Compile the baseline and its standalone diagnostic demo

Run python3 tools/check_boundaries.py. Run ./tools/build.sh for the MagicBox baseline and standalone demo. Inspect compiler exit codes, warnings and image/partition fit. Do not infer runtime behavior from compilation. Record Build, Host tests, Device tests and Unverified separately.
