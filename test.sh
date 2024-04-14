clear
make
printf "\n\n"

maps=(5 10 20 50 100 200 500)

map1=./test_maps/1.cub
map2=./test_maps/very_big/5x5.cub
map3=./test_maps/very_big/10x10.cub
map4=./test_maps/very_big/20x20.cub
map5=./test_maps/very_big/50x50.cub
map6=./test_maps/very_big/100x100.cub
map7=./test_maps/very_big/200x200.cub
map8=./test_maps/very_big/500x500.cub
map9=./test_maps/very_big/1000x1000.cub
map10=./test_maps/very_big/2000x2000.cub
map11=./test_maps/very_big/5000x5000.cub
map12=./test_maps/very_big/10000x10000.cub
map13=./test_maps/very_big/20000x20000.cub

map=$map5

# bash ./test_maps/very_big/create_big_map.sh

clear

if [ $# -eq 0 ]; then
    ./cub3D $map
else
    valgrind --leak-check=full --show-leak-kinds=all ./cub3D $map
fi

