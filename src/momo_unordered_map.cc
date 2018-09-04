#include <inttypes.h>
#include <string>
#include "momo/stdish/unordered_map.h"

typedef momo::stdish::unordered_map<int64_t, int64_t> map_t;
typedef momo::stdish::unordered_map<std::string, int64_t> str_map_t;

#define SETUP map_t map; str_map_t str_map;

#define INSERT_INT(key, value) map.insert({ key, value })
#define DELETE_INT(key) map.erase(key)
#define FIND_INT_EXISTING(key) if (!map.contains(key)) { printf("error"); exit(1); }
#define FIND_INT_MISSING(key) if (map.contains(key)) { printf("error"); exit(2); }
#define CHECK_INT_VALUES(value) for (const auto& ref : map) if (ref.second != value) { printf("error"); exit(3); }

#define INSERT_STR(key, value) str_map.insert({ key, value })
#define DELETE_STR(key) str_map.erase(key);
#define FIND_STR_EXISTING(key) if (!str_map.contains(key)) { printf("error"); exit(4); }
#define FIND_STR_MISSING(key) if (str_map.contains(key)) { printf("error"); exit(5); }

#include "template.c"

