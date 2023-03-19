all: build/momo_unordered_map_open_stable build/momo_unordered_map_open_current

build/momo_unordered_map_open_stable:
	g++ -Imomo_stable -O3 -DNDEBUG -march=native -std=c++11 -o build/momo_unordered_map_open_stable src/momo_unordered_map_open.cc

build/momo_unordered_map_open_current:
	g++ -Imomo_current -O3 -DNDEBUG -march=native -std=c++11 -o build/momo_unordered_map_open_current src/momo_unordered_map_open.cc
