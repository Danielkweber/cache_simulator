#include <map>
#include <list>
#include "block.h"

using std::map; using std::list;

class Set {
    private:
        // Tracks set size
        uint32_t set_size;
        // Number of blocks
        uint32_t num_blocks;

        // Stores the eviction policy and booleans for
        // write through and allocation policy
        // Different methods will be called based on these
        int evict_policy;
        bool write_through;
        bool write_alloc;

        // Map to store blocks abd index
        map<uint32_t, Block*>* blocks;
        // List of indeces in eviction order
        // Will be order based on evict policy
        list<uint32_t>* evict_order;
  
    public:
        // Contractor
        Set(uint32_t set_size, int evict_policy, bool write_through, bool write_allocate);

        ~Set();
        // Checks if a tag is in a set
        bool is_in_set(uint32_t tag);
        // adds a tag to block
        int add_block(uint32_t tag);
        // updates eviction order
        void update_evict_order(uint32_t tag);
        // erases block based on evict order
        int kickout();

        // returns pointer to blocks map
        map<uint32_t, Block*>* get_blocks() { return blocks; }
};
