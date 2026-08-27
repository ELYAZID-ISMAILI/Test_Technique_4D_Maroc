#!/usr/bin/env bash
#
# build.sh — Compile tout le projet (Release).
# Aucune option : tout est fait en un coup.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

BUILD_DIR="build"
BUILD_TYPE="Release"

# --- 1. Conan ---------------------------------------------------------------
echo ">> [1/3] conan install"
conan install . \
    --output-folder="$BUILD_DIR" \
    --build=missing \
    --settings=build_type="$BUILD_TYPE"

# --- 2. CMake configure -----------------------------------------------------
echo ">> [2/3] cmake configure"
TOOLCHAIN="$BUILD_DIR/build/$BUILD_TYPE/generators/conan_toolchain.cmake"
if [[ ! -f "$TOOLCHAIN" ]]; then
    TOOLCHAIN="$BUILD_DIR/conan_toolchain.cmake"
fi

if command -v ninja >/dev/null 2>&1; then
    GENERATOR="Ninja"
else
    GENERATOR="Unix Makefiles"
fi

cmake -S . -B "$BUILD_DIR" \
    -G "$GENERATOR" \
    -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

# --- 3. CMake build ---------------------------------------------------------
echo ">> [3/3] cmake build"
cmake --build "$BUILD_DIR" -j "$(nproc)"

echo ""
echo ">> OK. Exécutables produits :"
find "$BUILD_DIR" -maxdepth 2 -type f -executable ! -name "*.so" ! -name "*.a" 2>/dev/null | sort
