[简体中文](AGENTS.zh_CN.md)

# Agent entry

Read docs/BSP.md and lib/bsp/src/bsp_pins.h. Start with git status and preserve user changes. Select the exact hardware profile; Pro/Pro2 speaker WS/DATA differ. Keep hardware implementation in lib/bsp, applications downstream, and diagnostics in examples. Never commit credentials, private product applications or device identity. Run tools/check_boundaries.py then tools/build.sh. Report build, host, device and unverified results separately. Obtain authorization for the exact device/image before flashing.

[Read the matching repository Agent skill](skills/README.md).
