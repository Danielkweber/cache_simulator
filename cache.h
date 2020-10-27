#include <map>
#include <utility>
#include <string>
#include <sstream>
#include "set.h"

using std::map; using std::pair;
using std::string; using std::endl;
using std::stringstream;

class Cache {
    private:

       // Structure to keep track of all the stats to be returned
       class Statistics {
            public:
                int cycles = 0;
                int total_loads = 0;
                int total_stores = 0;
                int store_hits = 0;
                int store_misses = 0;
                int load_hits = 0;
                int load_misses = 0;

	        // Constructor
	        Statistics() {}
	        //Prints the stats in output format in assignment
	        string to_string() {
                    stringstream statstream;
                    statstream << "Total loads: " << total_loads << endl;
                    statstream << "Total stores: " << total_stores << endl;
                    statstream << "Load hits: " << load_hits << endl;
                    statstream << "Load misses: " << load_misses << endl;
                    statstream << "Store hits: " << store_hits << endl;
                    statstream << "Store misses: " << store_misses << endl;
                    statstream << "Total cycles: " << cycles << endl;
                    return statstream.str();
                }
        };
        // Keeps track of one set of stats per instance
        Statistics* stats;

        // number of sets
        uint32_t num_sets;
        // how big each set is
        uint32_t set_size;
        // how big is each box, consistent
        uint32_t block_size;

        // tracks eviction policy and write through, write allocate policy
        bool write_alloc;
        bool write_through;
        int evict_policy;

        // map of sets and index
        map<uint32_t, Set*>* sets;
        // checks if certain tag gives a hit
        bool is_hit(uint32_t tag, uint32_t index);

    public:
        // Constructor
        Cache(uint32_t num_sets, uint32_t set_size, uint32_t block_size, string write_alloc, string write_through, string evict_policy);
        Cache();

        // Desctrutor
        ~Cache();   

        // given address, create new tag index pair
        pair<uint32_t, uint32_t> process_address(uint32_t address);
        // store given tag in chache
        uint32_t store_in_cache(uint32_t tag, uint32_t index);

        // read cache for given tag, and count stats
        void read_cache(uint32_t tag, uint32_t index);
        // load cache with tag and count stats
        void load_cache(uint32_t tag, uint32_t index);
        // write cache for given tag and count stats
        void write_cache(uint32_t tag, uint32_t index);

        // get's stats object so we can print the stats
        Statistics* get_stats() { return this->stats; }

};
