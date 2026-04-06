#!/bin/bash
set -euo pipefail

##### place this file in "./scripts/" directory of a GARLIC project
##### Last updated: 2026/04/06

if [ ! -d "src" ] || [ ! -d "include" ]; then
    echo "Error: script must be run in the project folder containing 'src' and 'include' directories."
    exit 1
fi

if [ ! -d "vendors/garlic" ]; then
    bash scripts/garlic_fetch.sh
fi

cd vendors/garlic
python3 injector.py ../../src ../../include inject
cd - >/dev/null
