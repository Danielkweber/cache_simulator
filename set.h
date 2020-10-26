#include <map>
#include <list>
#include "block.h"

using std::map; using std::list;

class Set {
    private:
        // Tracks set size
        int set_size;
        // Number of blocks
        int num_blocks;

        // Stores the eviction policy and booleans for
        // write through and allocation policy
        // Different methods will be called based on these
        char evict_policy;
        bool write_through;
        bool write_alloc;

        // Map to store blocks abd index
        map<int, Block*>* blocks;
        // List of indeces in eviction order
        // Will be order based on evict policy
        list<int>* evict_order;
  
    public:
        // Contractor
        Set(int set_size, char evict_policy, bool write_through, bool write_allocate);

        // Checks if a tag is in a set
        bool is_in_set(int tag);
        // adds a tag to block
        int add_block(int tag);
        // updates eviction order
        void update_evict_order(int tag);
        // erases block based on evict order
        int kickout();

        // returns pointer to blocks map
        map<int, Block*>* get_blocks() { return blocks; }
};
