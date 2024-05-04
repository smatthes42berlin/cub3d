#!/bin/bash

clear

make fcleanall

rm -rf submission
mkdir submission
mkdir submission/libft
mkdir submission/mlx
mkdir submission/src
mkdir submission/textures
mkdir submission/include
mkdir submission/build

chmod +777 submission
chmod +777 submission/libft
chmod +777 submission/src

find ./libft/src -name \*.c -exec cp {} submission/libft \;
find ./libft/include -name \*.h -exec cp {} submission/libft \;

cp ./libft/Makefile_submit.submit ./submission/libft/Makefile
cp ./libft/Makefile_src ./submission/libft/Makefile_src



cp ./Makefile ./submission/Makefile
cp ./main.c ./submission/main.c

source_dir="./src/"

# Use find to locate all .c files in the source directory and its subdirectories
find "$source_dir" -type f -name "*.c" -exec bash -c '
    # Get the relative path of the source file
    source_file="$1"
    source_dir=$(dirname "$source_file")
    destination_dir="./submission/"

    mkdir "${destination_dir}${source_dir}"

    # Copy the source file to the destination directory
    cp "$source_file" "${destination_dir}${source_file}"
' bash {} \;

find ./include -name \*.h -exec cp {} submission/include/ \;

source_dir="./mlx/"

# Use find to locate all .c files in the source directory and its subdirectories
find "$source_dir" -type f -exec bash -c '
    # Get the relative path of the source file
    source_file="$1"
    source_dir=$(dirname "$source_file")
    destination_dir="./submission/"

    mkdir "${destination_dir}${source_dir}"

    # Copy the source file to the destination directory
    cp "$source_file" "${destination_dir}${source_file}"
' bash {} \;

texture_names=(
    "basalt_top.xpm"
    "bluestone.xpm"
    "bookshelf_01.xpm"
    "bookshelf_02.xpm"
    "bookshelf_03.xpm"
    "bookshelf.xpm"
    "cobblestone_01.xpm"
    "cobblestone_02.xpm"
    "cobblestone.xpm"
    "color_stone.xpm"
    "cyan_concrete.xpm"
    "eagle.xpm"
    "east.xpm"
    "forbidden.xpm"
    "grey_stone.xpm"
    "matrix.xpm"
    "mossy_cobblestone1.xpm"
    "mossy.xpm"
    "mycelium_top.xpm"
    "netherrack_01.xpm"
    "netherrack_02.xpm"
    "netherrack.xpm"
    "north.xpm"
    "purple_stone.xpm"
    "red_brick.xpm"
    "respawn_anchor_side0.xpm"
    "respawn_anchor_side1.xpm"
    "respawn_anchor_side2.xpm"
    "respawn_anchor_side3.xpm"
    "respawn_anchor_side4.xpm"
    "soul_sand.xpm"
    "soul_soil_01.xpm"
    "soul_soil.xpm"
    "south.xpm"
    "warped_nylium.xpm"
    "warped_planks.xpm"
    "west.xpm"
    "wet_sponge.xpm"
    "wood.xpm"
)

source_folder="./test_maps/textures/geklaut/"
destination_folder="./submission/textures/"

for file_name in "${texture_names[@]}"; do
    # Check if the file exists in the source folder
    if [ -e "$source_folder/$file_name" ]; then
        # Copy the file to the destination folder
        cp "$source_folder/$file_name" "$destination_folder/$file_name"
    fi
done

cp ./test_maps/eval.cub ./submission/eval.cub
cp ./test_maps/eval.cub ./submission/eval1.cub
cp ./test_maps/eval.cub ./submission/eval2.cub

rm ./submission/libft/src/main.c
rm ./submission/src/discuss.c

