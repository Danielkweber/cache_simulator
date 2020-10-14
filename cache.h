#include <map>
#include <utility>
#include <set.h>

using std::map; using std::pair;

class Cache {
    private:
        int num_sets;
        int set_size;
        int block_size;
        map<int, Set*>* sets;
        bool is_hit(int tag, int index);
    public:
        Cache(int num_sets, int set_size, int block_size);
        Cache();   
        pair<int, int>* process_address(int address);
        int store_in_cache(int tag, int index);
        bool read_cache(int tag, int index);

};