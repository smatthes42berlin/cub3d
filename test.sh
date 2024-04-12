clear
make
printf "\n\n"

map1=./test_maps/1.cub
map2=./test_maps/very_big/500x500.cub
map3=./test_maps/very_big/1000x1000.cub
map4=./test_maps/very_big/10000x10000.cub
map5=./test_maps/very_big/20000x10000.cub

map=$map1

if [ $# -eq 0 ]; then
    ./cub3D $map
else
    valgrind --leak-check=full --show-leak-kinds=all ./cub3D $map
fi

