#!/bin/bash

CUB3D="./cub3D"
MAP_DIR="maps"

if [ ! -x "$CUB3D" ]; then
	echo "Error: cub3D not found or not executable"
	exit 1
fi

for file in $(find "$MAP_DIR" -type f -name "*.cub" | sort)
do
	echo "=============================="
	echo "Running: $file"
	echo "------------------------------"
	$CUB3D "$file"
	echo ""
done
