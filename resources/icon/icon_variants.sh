#!/bin/bash
# Icon Variant generator script
# Takes an svg and generates different size variants for icon files:
# 16x16, 16x16@2, 32x32, 32x32@2, 64x64, 64x64@2, 128x128, 128x128@, 256x256, 256x256@2, 512x512, 512x512@2
#
# Usage:
#   ./icon_variants.sh input.svg output_folder/

SVG_FILE=$1
OUTPUT_DIR=$2

mkdir -p $OUTPUT_DIR

for pow in $(seq 4 9); do
    SIZE=$((2 ** $pow))
    SIZE_2=$((2 ** $(($pow + 1))))

    VARIANT_FILE="icon_${SIZE}x${SIZE}"

    convert ${SVG_FILE} -scale ${SIZE} "${OUTPUT_DIR}/${VARIANT_FILE}.png"
    convert ${SVG_FILE} -scale ${SIZE_2} "${OUTPUT_DIR}/${VARIANT_FILE}@2.png"
done;
