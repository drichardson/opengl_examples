#!/bin/bash
# Update the generated gl3w files.

set -e

# Checkout the source
rm -rf gl3w
git clone https://github.com/skaslev/gl3w.git

# Generate the files
pushd gl3w
./gl3w_gen.py
popd

# Copy the files into place.
mkdir -p include/GL
cp gl3w/include/GL/*.h include/GL
cp gl3w/src/gl3w.c .

rm -rf gl3w

echo OK
