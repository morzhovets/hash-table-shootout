#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>

#if !defined(INSERT_INT) && defined(INSERT_INT_INTO_HASH)
#define INSERT_INT INSERT_INT_INTO_HASH
#endif

#if !defined(DELETE_INT) && defined(DELETE_INT_FROM_HASH)
#define DELETE_INT DELETE_INT_FROM_HASH
#endif

#if !defined(FIND_INT_EXISTING) && defined(FIND_INT_EXISTING_FROM_HASH)
#define FIND_INT_EXISTING FIND_INT_EXISTING_FROM_HASH
#endif

#if !defined(FIND_INT_MISSING) && defined(FIND_INT_MISSING_FROM_HASH)
#define FIND_INT_MISSING FIND_INT_MISSING_FROM_HASH
#endif

#if !defined(CHECK_INT_VALUES) && defined(CHECK_INT_ITERATOR_VALUE)
#define CHECK_INT_VALUES(value) \
    using std::begin; using std::end; \
    for(auto it = begin(hash), end_it = end(hash); it != end_it; ++it) \
        CHECK_INT_ITERATOR_VALUE(it, value);
#endif

#if !defined(INSERT_STR) && defined(INSERT_STR_INTO_HASH)
#define INSERT_STR INSERT_STR_INTO_HASH
#endif

#if !defined(DELETE_STR) && defined(DELETE_STR_FROM_HASH)
#define DELETE_STR DELETE_STR_FROM_HASH
#endif

#if !defined(FIND_STR_EXISTING) && defined(FIND_STR_EXISTING_FROM_HASH)
#define FIND_STR_EXISTING FIND_STR_EXISTING_FROM_HASH
#endif

#if !defined(FIND_STR_MISSING) && defined(FIND_STR_MISSING_FROM_HASH)
#define FIND_STR_MISSING FIND_STR_MISSING_FROM_HASH
#endif

static const int64_t SEED = 0;
static std::mt19937_64 generator(SEED);

double get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (tv.tv_usec / 1000000.0);
}

std::string get_string_for_key(int64_t key) 
{
    return "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" + std::to_string(key);
}

std::string get_small_string_for_key(int64_t key) 
{
    return std::to_string(key);
}

// Range starts at 0
std::vector<int64_t> get_random_shuffle_range_ints(size_t range_end) 
{
    std::vector<int64_t> random_ints(range_end);
    std::iota(random_ints.begin(), random_ints.end(), 0);
    std::shuffle(random_ints.begin(), random_ints.end(), generator);
    
    return random_ints;
}

std::vector<int64_t> get_random_full_ints(size_t nb_ints, 
                                          int64_t min = 0, 
                                          int64_t max = std::numeric_limits<int64_t>::max()) 
{
    std::uniform_int_distribution<int64_t> rd_uniform(min, max);
    
    std::vector<int64_t> random_ints(nb_ints);
    for(size_t i=0; i < random_ints.size(); i++)
    {
        random_ints[i] = rd_uniform(generator);
    }
    
    return random_ints;
}

int main(int argc, char ** argv)
{
    if(argc != 3) 
    {
        return 1;
    }
    
    const int64_t num_keys = std::stoll(argv[1]);
    const std::string test_type = argv[2];
    const int64_t value = 1;

    SETUP

    double before = get_time();

    if(test_type == "randomfull")
    {
        std::vector<int64_t> keys = get_random_full_ints(num_keys);
        before = get_time();
        
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_INT(keys[i], value);
        }
    }

    else if(test_type == "randomfullread")
    {
        std::vector<int64_t> keys = get_random_full_ints(num_keys);
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_INT(keys[i], value);
        }
        
        std::shuffle(keys.begin(), keys.end(), generator);
        
        before = get_time();
        for(int64_t i = 0; i < num_keys; i++)
        {
            FIND_INT_EXISTING(keys[i]);
        }
    }

    else if(test_type == "randomfullreadmiss")
    {
#ifdef FIND_INT_MISSING
        std::vector<int64_t> keys_insert = get_random_full_ints(num_keys, 0, std::numeric_limits<int64_t>::max());
        std::vector<int64_t> keys_read = get_random_full_ints(num_keys, std::numeric_limits<int64_t>::min(), -3);
        
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_INT(keys_insert[i], value);
        }
        
        before = get_time();
        for(int64_t i = 0; i < num_keys; i++)
        {
            FIND_INT_MISSING(keys_read[i]);
        }
#endif
    }

    else if(test_type == "iteration")
    {
        std::vector<int64_t> keys = get_random_full_ints(num_keys);
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_INT(keys[i], value);
        }
        
        before = get_time();
        CHECK_INT_VALUES(value);
    }
    
    else if(test_type == "delete")
    {
#ifdef DELETE_INT
        std::vector<int64_t> keys = get_random_full_ints(num_keys);
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_INT(keys[i], value);
        }
        
        std::shuffle(keys.begin(), keys.end(), generator);
        
        before = get_time();
        for(int64_t i = 0; i < num_keys; i++)
        {
            DELETE_INT(keys[i]);
        }
#endif
    }

    else if(test_type == "insertsmallstring")
    {
        std::vector<int64_t> keys = get_random_shuffle_range_ints(num_keys);
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_STR(get_small_string_for_key(keys[i]), value);
        }
    }

    else if(test_type == "readsmallstring")
    {
        std::vector<int64_t> keys = get_random_shuffle_range_ints(num_keys);
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_STR(get_small_string_for_key(keys[i]), value);
        }
        
        std::shuffle(keys.begin(), keys.end(), generator);
        
        before = get_time();
        for(int64_t i = 0; i < num_keys; i++)
        {
            FIND_STR_EXISTING(get_small_string_for_key(keys[i]));
        }
    }

    else if(test_type == "readsmallstringmiss")
    {
#ifdef FIND_STR_MISSING
        std::vector<int64_t> keys = get_random_shuffle_range_ints(num_keys*2);        
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_STR(get_small_string_for_key(keys[i]), value);
        }
        
        before = get_time();
        for(int64_t i = num_keys; i < num_keys*2; i++)
        {
            FIND_STR_MISSING(get_small_string_for_key(keys[i]));
        }
#endif
    }

    else if(test_type == "deletesmallstring")
    {
#ifdef DELETE_STR
        std::vector<int64_t> keys = get_random_shuffle_range_ints(num_keys);
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_STR(get_small_string_for_key(keys[i]), value);
        }
        
        std::shuffle(keys.begin(), keys.end(), generator);
        
        before = get_time();
        for(int64_t i = 0; i < num_keys; i++)
        {
            DELETE_STR(get_small_string_for_key(keys[i]));
        }
#endif
    }
    
    else if(test_type == "insertstring")
    {
        std::vector<int64_t> keys = get_random_shuffle_range_ints(num_keys);
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_STR(get_string_for_key(keys[i]), value);
        }
    }

    else if(test_type == "readstring")
    {
        std::vector<int64_t> keys = get_random_shuffle_range_ints(num_keys);
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_STR(get_string_for_key(keys[i]), value);
        }
        
        std::shuffle(keys.begin(), keys.end(), generator);
        
        before = get_time();
        for(int64_t i = 0; i < num_keys; i++)
        {
            FIND_STR_EXISTING(get_string_for_key(keys[i]));
        }
    }

    else if(test_type == "readstringmiss")
    {
#ifdef FIND_STR_MISSING
        std::vector<int64_t> keys = get_random_shuffle_range_ints(num_keys*2);
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_STR(get_string_for_key(keys[i]), value);
        }
        
        before = get_time();
        for(int64_t i = num_keys; i < num_keys*2; i++)
        {
            FIND_STR_MISSING(get_string_for_key(keys[i]));
        }
#endif
    }

    else if(test_type == "deletestring")
    {
#ifdef DELETE_STR
        std::vector<int64_t> keys = get_random_shuffle_range_ints(num_keys);
        for(int64_t i = 0; i < num_keys; i++)
        {
            INSERT_STR(get_string_for_key(keys[i]), value);
        }
        
        std::shuffle(keys.begin(), keys.end(), generator);
        
        before = get_time();
        for(int64_t i = 0; i < num_keys; i++)
        {
            DELETE_STR(get_string_for_key(keys[i]));
        }
#endif
    }
    
    double after = get_time();
    
    sleep(1);
    printf("%f\n", after-before);
    fflush(stdout);
    sleep(20);
}
