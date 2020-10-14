#include <map>
#include <list>
#include <block.h>

using std::map; using std::list;

class Set {
    private:
        int num_blocks;
        map<int, Block*>* blocks;
        list<int> order_added;
        list<int> use_order;
    public:
        int is_in_set(int tag);
        int kickout(char policy);
        map<int, Block*>* get_blocks() { return blocks; }


};