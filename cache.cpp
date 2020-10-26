#include "cache.h"
#include <math.h>



/**
 *  Full Cache Constructor
 *  Input:  number of sets, size of sets, block size, and string versions of the write 
 *  and string versions of write allocate, write throguh and eviction policies
 */
Cache::Cache(int num_sets, int set_size, int block_size, string write_alloc, string write_through, string evict_policy) {
    // Makes new set of stats set to 0
    this->stats = new Statistics;

    // updates number and size of sets, block size
    this->num_sets = num_sets;
    this->set_size = set_size;
    this->block_size = block_size;

    // For policies passed as strings, check which
    // of 2 possibilities (already checked) is passed
    // and store in boolean or int value for easier handling
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

/**
 *  Processes a cache address and returns its tag and index
 *  Input: address, an int representing the address in question
 *  Output: a pointer to a tag and index value value, reping the address
 */
pair<int, int>* Cache::process_address(int address) {
    // remove offset
    int addr_no_offset = address >> (int) log2(block_size);
    // get tag
    int tag = addr_no_offset >> (int) log2(num_sets);
    // get index
    int index = addr_no_offset - tag;

    // return tag, index pair
    return new pair<int, int>(tag, index);
}

/**
 *  Checks if address pair gives a hit
 *  Input: tag and index ints representing an address
 *  Output: boolean value of if there was a hit
 */
bool Cache::is_hit(int tag, int index) {
    // check if index is in set
    if (sets->find(index) != sets->end()) {
        // return if tag in index
        return sets->at(index)->is_in_set(tag);
    } else {
        // false if can't find
        return false;
    }
}

/**
 *  Reads cache for given address and counts stats
 *  Input: tag and index ints representing an address
 *  Output: boolean of if cache was read
 */
bool Cache::read_cache(int tag, int index) {
    // count loads
    stats->total_loads++;
    // if there's a hit
    if (this->is_hit(tag, index)) {
        // if lru evict policy, update order appropriately
        if (evict_policy == 1) {
            this->sets->at(index)->update_evict_order(tag);
        }
	// count hits and cycles
        stats->load_hits++;
        stats->cycles++;

	// return true read because hit
        return true;
    } else {
        // count misses
        stats->load_misses++;
	// if miss, load cache
        this->load_cache(tag, index);
    }
}

/**
 *  Loads cache for given address and counts stats
 *  Input: tag and index ints representing an address
 *  Output: N/A doesn't return whether read or not
 */
void Cache::load_cache(int tag, int index) {
    // check address not already in cache
    if (sets->find(index) != sets->end()) {
        // access memory
        int mem_accesses = sets->at(index)->add_block(tag);
	// update cycle stat
        stats->cycles += this->block_size*25*mem_accesses;
    }
}

/**
 *  Writes cache for given address and counts stats
 *  Input: tag and index ints representing an address
 *  Output: N/A doesn't return
 */
void Cache::write_cache(int tag, int index) {
    // update store stats
    stats->total_stores++;

    // if hit 
    if (this->is_hit(tag, index)) {
        // update stats
        stats->store_hits++;
        stats->cycles++;
    } else {
        // update misses stat
        stats->store_misses++;
	// if write allocate, load cache
        if (write_alloc) {
            load_cache(tag, index);
        }
    }
    //if write through update cycles
    if (this->write_through) {
        stats->cycles += 25*block_size;
    } else {
        // otherwise set appropriate block to dirty
        this->sets->at(index)->get_blocks()->at(tag)->is_dirty = true;
    }
}
