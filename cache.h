#include <map>
#include <utility>
#include <string>
#include "set.h"

using std::map; using std::pair;
using std::string;

class Cache {
    private:
        struct Statistics {
                int cycles = 0;
                int total_loads = 0;
                int total_stores = 0;
                int store_hits = 0;
                int store_misses = 0;
                int load_hits = 0;
                int load_misses = 0;
        };
        Statistics* stats;
        int num_sets;
        int set_size;
        int block_size;
        bool write_alloc;
        bool write_through;
        int evict_policy;
        map<int, Set*>* sets;
        bool is_hit(int tag, int index);
    public:
        Cache::Cache(int num_sets, int set_size, int block_size, string write_alloc, string write_through, string evict_policy);
        Cache();   
        pair<int, int>* process_address(int address);
        int store_in_cache(int tag, int index);
        bool read_cache(int tag, int index);
        void load_cache(int tag, int index);
        void write_cache(int tag, int index);

};