#!/bin/bash

EXEC=./cub3D
GOOD_DIR=maps/good
BAD_DIR=maps/bad

GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

echo "========== TESTING GOOD MAPS =========="

for map in "$GOOD_DIR"/*.cub
do
	echo "Testing $map"
	$EXEC "$map"
	if [ $? -eq 0 ]
	then
		echo -e "${GREEN}OK${RESET}"
	else
		echo -e "${RED}KO (should be valid)${RESET}"
	fi
done

echo
echo "========== TESTING BAD MAPS =========="

for map in "$BAD_DIR"/*.cub
do
	echo "Testing $map"
	$EXEC "$map"
	if [ $? -ne 0 ]
	then
		echo -e "${GREEN}OK (correctly rejected)${RESET}"
	else
		echo -e "${RED}KO (should be invalid)${RESET}"
	fi
done
