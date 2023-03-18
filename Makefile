all: build/momo_unordered_map build/momo_unordered_map_open

build/momo_unordered_map: src/momo_unordered_map.cc Makefile src/template.c
	g++ -O3 -march=native -std=c++11 -DNDEBUG -lm -o build/momo_unordered_map src/momo_unordered_map.cc

build/momo_unordered_map_open: src/momo_unordered_map_open.cc Makefile src/template.c
	g++ -O3 -march=native -std=c++11 -DNDEBUG -lm -o build/momo_unordered_map_open src/momo_unordered_map_open.cc
