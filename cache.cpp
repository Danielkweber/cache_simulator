#include "cache.h"
#include <math.h>



Cache::Cache(int num_sets, int set_size, int block_size) {
    this->num_sets = num_sets;
    this->set_size = set_size;
    this->block_size = block_size;
}

pair<int, int>* Cache::process_address(int address) {
    int addr_no_offset = address >> (int) log2(block_size);
    int tag = addr_no_offset >> (int) log2(num_sets);
    int index = addr_no_offset - tag;
    return new pair<int, int>(tag, index);
}

bool Cache::is_hit(int tag, int index) {
    if (sets->find(index) != sets->end()) {
        if (sets->at(index)->get_blocks()->find(tag) != sets->at(index)->get_blocks()->end()) {
            return true;
        }
    }
    return false;   
}