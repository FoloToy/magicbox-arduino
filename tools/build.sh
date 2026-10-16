#!/usr/bin/env bash
set -euo pipefail
root="$(cd "$(dirname "$0")/.." && pwd)"
python3 "$root/tools/check_boundaries.py"
pio run -d "$root" -e magicbox -e magicbox-demo -e magicbox-pro -e magicbox-pro-demo -e magicbox-pro2 -e magicbox-pro2-demo
