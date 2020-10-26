#include <map>
#include <utility>
#include <string>
#include "set.h"

using std::map; using std::pair;
using std::string;

class Cache {
    private:

       // Structure to keep track of all the stats to be returned
       struct Statistics {
                int cycles = 0;
                int total_loads = 0;
                int total_stores = 0;
                int store_hits = 0;
                int store_misses = 0;
                int load_hits = 0;
                int load_misses = 0;
        };
        // Keeps track of one set of stats per instance
        Statistics* stats;

        // number of sets
        int num_sets;
        // how big each set is
        int set_size;
        // how big is each box, consistent
        int block_size;

        // tracks eviction policy and write through, write allocate policy
        bool write_alloc;
        bool write_through;
        int evict_policy;

        // map of sets and index
        map<int, Set*>* sets;
        // checks if certain tag gives a hit
        bool is_hit(int tag, int index);

    public:
        // Constructor
        Cache(int num_sets, int set_size, int block_size, string write_alloc, string write_through, string evict_policy);
        Cache();

        // given address, create new tag index pair
        pair<int, int>* process_address(int address);
        // store given tag in chache
        int store_in_cache(int tag, int index);

        // read cache for given tag, and count stats
        bool read_cache(int tag, int index);
        // load cache with tag and count stats
        void load_cache(int tag, int index);
        // write cache for given tag and count stats
        void write_cache(int tag, int index);

};
