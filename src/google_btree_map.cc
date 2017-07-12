#include <inttypes.h>
#include <string>
#include "btree/btree_map.h"

typedef btree::btree_map<int64_t, int64_t> map_t;
typedef btree::btree_map<std::string, int64_t> str_map_t;

#define SETUP map_t map; str_map_t str_map;

#define INSERT_INT(key, value) map.insert(map_t::value_type(key, value))
#define DELETE_INT(key) map.erase(key)
#define FIND_INT_EXISTING(key) if(map.find(key) == map.end()) { printf("error"); exit(1); }
//#define FIND_INT_MISSING(key) if(map.find(key) != map.end()) { printf("error"); exit(2); }
#define CHECK_INT_VALUES(value) for(auto&& ref : map) if(ref.second != value) { printf("error"); exit(3); }

#define INSERT_STR(key, value) str_map.insert(str_map_t::value_type(key, value))
#define DELETE_STR(key) str_map.erase(key);
#define FIND_STR_EXISTING(key) if(str_map.find(key) == str_map.end()) { printf("error"); exit(4); }
//#define FIND_STR_MISSING(key) if(str_map.find(key) != str_map.end()) { printf("error"); exit(5); }

#include "template.c"
