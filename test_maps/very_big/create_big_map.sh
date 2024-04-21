#!/bin/bash
clear
get_char() {
    prop_1=40
    prop_0=60
    rand_num=$((1 + $RANDOM % 100))
    if [ "$rand_num" -gt $prop_1 ]; then
        printf "0"
    else
        printf "1"
    fi
}

write_zeros() {
    local width=$1
    local height=$2
    local filename=$3

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

    echo "creating $filename"
    echo -e "$full_block" >"$filename"
    echo "$filename created"
    echo
}

# Function to write zeros to a text file
write_zeros_ones() {
    local width=$1
    local height=$2
    local filename=$3

    # Create the block of zeros
    # local zeros=$(printf '%*s' $width | tr ' ' '0')
    # local block=$(printf '%s\n' "$zeros")

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

    local zeros=$(printf '%*s' $((width + 2)) | tr ' ' '1')
    local block1=$(printf '%s\n' "$zeros")

    full_block+="$block1\n"

    for ((i = 0; i < height; i++)); do
        block="1"
        for ((j = 0; j < width; j++)); do
            block+=$(printf '%s' $(get_char))
        done
        block+="1"
        full_block+="$block\n"
    done

    full_block+="$block1\n"

    length=${#full_block}
    echo $length
    random_position=$(($RANDOM % length))
    echo $random_position
    string_with_E="${full_block:0:random_position}E${full_block:random_position+1}"
    echo -e $string_with_E

    echo "creating $filename"
    # echo -e "$full_block" >"$filename"
    echo -e "$string_with_E" >"$filename"
    echo "$filename created"
    echo
}

maps=(5 10 20 50 100 200 500 1000 2000 5000 10000 20000)
maps=(5 10 20 50 100 200 500)
maps=(1 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 35 40 50)
maps=(10)

# Iterate over maps array
for map in "${maps[@]}"; do
    width=${map[0]}
    height=${map[0]}
    filename="${width}x${height}.cub"
    rm $filename
    # write_zeros $width $height "$filename"
    write_zeros_ones $width $height "$filename"
done

# width=5000
# height=5000
# filename="${width}x${height}.cub"

# write_zeros $width $height $filename
