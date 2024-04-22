#!/bin/bash

directory="./error"

rm test_res

# Use find to locate all .c files in the specified directory
# -type f: only search for files
# -name "*.cub": match files with the .cub extension
# -print0: separate file names with null character (for filenames with spaces)
# You can adjust the options as per your requirement
find "$directory" -type f -name "*.cub" -print0 |
while IFS= read -r -d '' file; do
    # Loop through each found .c file
    # res=$(../cub3D $file 2>&1)
    # echo $res
    # echo $file
    # valgrind ../cub3D $file 2>&1 >> test_res
    ../cub3D $file 2>&1 >> test_res
    echo $file >> test_res
    printf "\n\n" >> test_res
    # printf "\n\n\n"
    # echo
    # Add your processing commands here
    # For example, you can compile each .c file
    # gcc "$file" -o "${file%.c}"
done

cat test_res | grep Success