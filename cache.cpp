#include "cache.h"
#include <math.h>




Cache::Cache(int num_sets, int set_size, int block_size, string write_alloc, string write_through, string evict_policy) {
    this->stats = new Statistics;
    this->num_sets = num_sets;
    this->set_size = set_size;
    this->block_size = block_size;
    if (write_alloc.compare("write-allocate") == 0) {
        this->write_alloc = true;
    } else {
        this->write_alloc = false;
    }
    if (write_through.compare("write-through") == 0) {
        this->write_through = true;
    } else {
        this->write_through = false;
    }
    if (evict_policy.compare("lru")) {
        this->evict_policy = 1;
    } else {
        this->evict_policy = 0;
    }
}

pair<int, int>* Cache::process_address(int address) {
    int addr_no_offset = address >> (int) log2(block_size);
    int tag = addr_no_offset >> (int) log2(num_sets);
    int index = addr_no_offset - tag;
    return new pair<int, int>(tag, index);
}

bool Cache::is_hit(int tag, int index) {
    if (sets->find(index) != sets->end()) {
        return sets->at(index)->is_in_set(tag);
    } else {
        return false;
    }
}

bool Cache::read_cache(int tag, int index) {
    stats->total_loads++;
    if (this->is_hit(tag, index)) {
        if (evict_policy == 1) { //If evict_policy is lru
            this->sets->at(index)->update_evict_order(tag);
        }
        stats->load_hits++;
        stats->cycles++;
        return true;
    } else {
        stats->load_misses++;
        this->load_cache(tag, index);
    }
}

void Cache::load_cache(int tag, int index) {
    if (sets->find(index) != sets->end()) {
        int mem_accesses = sets->at(index)->add_block(tag);
        stats->cycles += this->block_size*25*mem_accesses;
    }
}

void Cache::write_cache(int tag, int index) {
    stats->total_stores++;
    if (this->is_hit(tag, index)) {
        stats->store_hits++;
        stats->cycles++;
    } else {
        stats->store_misses++;
        if (write_alloc) {
            load_cache(tag, index);
        }
    }
    if (this->write_through) {
        stats->cycles += 25*block_size;
    } else {
        this->sets->at(index)->get_blocks()->at(tag)->is_dirty = true;
    }
}