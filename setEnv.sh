#!/usr/bin/env bash

INSTALL_DIR="$(dirname "$0")/build"
TARGET_BIN="2048"

if [ ! -f "$INSTALL_DIR/$TARGET_BIN" ]; then
  echo "target binary $INSTALL_DIR/$TARGET_BIN found, please run the build command first"
  # exit 1
else
  export PATH="$INSTALL_DIR:$PATH"
fi
