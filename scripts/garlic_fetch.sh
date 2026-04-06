#!/bin/bash
set -euo pipefail

##### place this file in "./scripts/" directory of a GARLIC project
##### Last updated: 2026/04/06

if [ ! -d "src" ] || [ ! -d "include" ]; then
    echo "Error: script must be run in the project folder containing 'src' and 'include' directories."
    exit 1
fi

mkdir -p vendors
rm -rf vendors/garlic

git clone --depth 1 https://github.com/DiegoBarMor/garlic.git vendors/garlic
# cp -r ../../garlic vendors/garlic ### alternatively, if there's a local copy of GARLIC
rm -rf vendors/garlic/.git
