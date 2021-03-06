#include <inttypes.h>
#include <unordered_map>
#include <string>
#include "momo/stdish/pool_allocator.h"

typedef std::unordered_map<int64_t, int64_t, std::hash<int64_t>, std::equal_to<int64_t>,
  momo::stdish::unsynchronized_pool_allocator<std::pair<const int64_t, int64_t>>> hash_t;
typedef std::unordered_map<std::string, int64_t, std::hash<std::string>, std::equal_to<std::string>,
  momo::stdish::unsynchronized_pool_allocator<std::pair<const std::string, int64_t>>> str_hash_t;

#define SETUP hash_t hash; str_hash_t str_hash;

#define INSERT_INT_INTO_HASH(key, value) hash.insert(std::make_pair(key, value))
#define DELETE_INT_FROM_HASH(key) hash.erase(key)
#define FIND_INT_EXISTING_FROM_HASH(key) if(hash.find(key) == hash.end()) { printf("error"); exit(1); }
#define FIND_INT_MISSING_FROM_HASH(key) if(hash.find(key) != hash.end()) { printf("error"); exit(2); }
#define CHECK_INT_ITERATOR_VALUE(iterator, value) if(iterator->second != value) { printf("error"); exit(3); }

#define INSERT_STR_INTO_HASH(key, value) str_hash.insert(std::make_pair(key, value))
#define DELETE_STR_FROM_HASH(key) str_hash.erase(key);
#define FIND_STR_EXISTING_FROM_HASH(key) if(str_hash.find(key) == str_hash.end()) { printf("error"); exit(4); }
#define FIND_STR_MISSING_FROM_HASH(key) if(str_hash.find(key) != str_hash.end()) { printf("error"); exit(5); }

#include "template.c"
