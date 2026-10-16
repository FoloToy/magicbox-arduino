#!/usr/bin/env bash
set -euo pipefail
root="$(cd "$(dirname "$0")/.." && pwd)"
python3 "$root/tools/check_boundaries.py"
pio run -d "$root" -e magicbox -e magicbox-demo
