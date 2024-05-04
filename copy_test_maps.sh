#!/bin/bash

clear

rm -rf submission/test_maps
mkdir submission/test_maps

test_maps=(
    "10000x10000_closed.cub"
    "10000x1_closed.cub"
    "1x10000_closed.cub"
    "1x1_closed.cub"
    "50x50_closed.cub"
    "100x100_closed.cub"
    "200x200_closed.cub"
    "500x500_closed.cub"
    "1000x1000_closed.cub"
    "2000x2000_closed.cub"
    "5000x5000_closed.cub"
)

source_folder="./test_maps/maps_final_tests"
destination_folder="./submission/test_maps/"

for file_name in "${test_maps[@]}"; do
    # Check if the file exists in the source folder
    if [ -e "$source_folder/$file_name" ]; then
        # Copy the file to the destination folder
        cp "$source_folder/$file_name" "$destination_folder/$file_name"
    fi
done




