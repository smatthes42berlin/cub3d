#!/bin/bash
clear

write_zeros_outer_ones() {
    local width=$1
    local height=$2
    local filename=$3

    # Repeat the block 'height' times
    no=$(printf '%s\n' "NO ./textures/bluestone.xpm")
    so=$(printf '%s\n' "SO ./textures/bluestone.xpm")
    we=$(printf '%s\n' "WE ./textures/bluestone.xpm")
    ea=$(printf '%s\n' "EA ./textures/bluestone.xpm")
    floor=$(printf '%s\n' "F 200,111,119")
    ceil=$(printf '%s\n' "C 225,111,0")

    local full_block=""
    full_block+="$no\n"
    full_block+="$so\n"
    full_block+="$we\n"
    full_block+="$ea\n"
    full_block+="$floor\n"
    full_block+="$ceil\n"

    map=""

    local ones=$(printf '%*s' $((width + 2)) | tr ' ' '1')
    local block1=$(printf '%s\n' "$$ones")

    # Create the block of zeros
    local zeros=$(printf '%*s' $width | tr ' ' '0')
    local block0=$(printf '%s\n' "$zeros")

    map+="$ones\n"

    for ((i = 0; i < height; i++)); do
        block="1"
        block+=$block0
        block+="1"
        map+="$block\n"
    done

    map+="$ones\n"

    random_width=$(($RANDOM % $width))
    random_height=$(($RANDOM % $height))

    random_pos=$((($random_height + 1) * ($width + 4) + $random_width + 1))
    string_with_E="${map:0:random_pos}E${map:random_pos+1}"
    full_block+=$string_with_E
    echo -e $full_block

    echo "creating $filename"
    echo -e "$full_block" >"$filename"
    echo "$filename created"
    echo
}



width=50
height=50
filename="../maps_final_tests/${width}x${height}_closed.cub"

write_zeros_outer_ones $width $height "$filename"
