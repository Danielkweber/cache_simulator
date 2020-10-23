#include <map>
#include <list>
#include "block.h"

using std::map; using std::list;

class Set {
    private:
        int set_size;
        int num_blocks;
        char evict_policy;
        bool write_through;
        bool write_alloc;
        map<int, Block*>* blocks;
        list<int>* evict_order;
    public:
        Set::Set(int set_size, char evict_policy, bool write_through, bool write_allocate);
        bool is_in_set(int tag);
        int add_block(int tag);
        void update_evict_order(int tag);
        int kickout();
        map<int, Block*>* get_blocks() { return blocks; }
};