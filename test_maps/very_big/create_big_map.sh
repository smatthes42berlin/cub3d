#!/bin/bash

# Function to write zeros to a text file
write_zeros() {
    local width=$1
    local height=$2
    local filename=$3

    # Check if width and height are valid
    if [ $width -le 0 ] || [ $height -le 0 ]; then
        echo "Error: Width and height must be greater than 0."
        exit 1
    fi

    # Create the block of zeros
    local zeros=$(printf '%*s' $width | tr ' ' '0')
    local block=$(printf '%s\n' "$zeros")

    # Repeat the block 'height' times
    no=$(printf '%s\n' "NO ./test_maps/textures/bluestone.xpm")
    so=$(printf '%s\n' "SO ./test_maps/textures/bluestone.xpm")
    we=$(printf '%s\n' "WE ./test_maps/textures/bluestone.xpm")
    ea=$(printf '%s\n' "EA ./test_maps/textures/bluestone.xpm")
    floor=$(printf '%s\n' "F 200,111,119")
    ceil=$(printf '%s\n' "C 225,111,0")

    local full_block=""
    full_block+="$no\n"
    full_block+="$so\n"
    full_block+="$we\n"
    full_block+="$ea\n"
    full_block+="$floor\n"
    full_block+="$ceil\n"

    for ((i = 0; i < height; i++)); do
        full_block+="$block\n"
    done

    # Write the block to the file
    echo -e "$full_block" >"$filename"
}

# # Usage: ./write_zeros.sh <width> <height> <filename>
# if [ "$#" -ne 3 ]; then
#     echo "Usage: $0 <width> <height> <filename>"
#     exit 1
# fi

map_1=(5 5)
map_2=(10 10)


write_zeros ${map_1[0]} ${map_1[1]} "${map_1[0]}x${map_1[1]}.cub"

