#!/bin/bash

# Save current directory
CURRENT_DIR=$(pwd)

# Script directory
SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)

# Patch GLFW -------------------------------------------------------------------

# Change to GLFW directory
cd $SCRIPT_DIR/../3rd-party/glfw

# Restore GLFW to original state
git checkout .

# Apply patch
PATCH_FILE=glfw_apple_renderer.patch
echo "Applying: $PATCH_FILE"
git apply $SCRIPT_DIR/$PATCH_FILE

# Change back to original directory
cd $CURRENT_DIR
