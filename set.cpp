//Daniel Weber JHED:dweber11
//Vance Wood JHED: vwood3

#include "set.h"
#include <utility>
#include <iterator>

using std::pair;

/**
 *  Full Set Constructor
 *  Takes in the set size, and policies for eviction,
 *  write through and wrtie allocate
 */
Set::Set(uint32_t set_size, int evict_policy, bool write_through, bool write_allocate) {
    // initially set num blocks to 0
    this->num_blocks = 0;
    
    // set the set size and the policies to the values passed
    this->set_size = set_size;
    this->evict_policy = evict_policy;
    this->write_through = write_through;
    this->write_alloc = write_allocate;

    // initialize block map and evict order to
    // empty map and list
    this->blocks = new map<uint32_t, Block*>;
    this->evict_order = new list<uint32_t>;
}

/**
 *  Full Set Destructor
 *  Eraces and deletes elements in Set
 */
Set::~Set() {
    // iterate over blocks in set
    for (map<uint32_t, Block*>::iterator it = this->blocks->begin(); it != this->blocks->end(); it++) {
        // erase block
        delete it->second;
    }
    
    // delete blocks object, and evict_order
    delete this->blocks;
    delete this->evict_order;
}

/**
 *  Checks if tag is in set
 *  Input: tag int which we check if is the given set
 *  Output: boolean value of if tag is in set or not
 */
bool Set::is_in_set(uint32_t tag) {
    //checks if tag is in set
    // return true if in, false if not
    return (this->blocks->find(tag) != blocks->end());
}

/**
 *  Adds block to set
 *  Input: tag int which we will add to set
 *  Output: an int which is the number of additonal blocks 
 */
int Set::add_block(uint32_t tag) {
    //  if the set is full
    if (this->num_blocks >= this->set_size) {
        // gets number of kickedout blocks 
        int write_back = kickout();
	// adds new block
        blocks->insert(pair<uint32_t, Block*>(tag, new Block));
        // update evict order
        evict_order->push_front(tag);
        // updates number of blocks
        this->num_blocks++;

	// additional blocks
        return 1 + write_back;
    } else {
        // add new block
        blocks->insert(pair<uint32_t, Block*>(tag, new Block));
        // update evict order
        evict_order->push_front(tag);
        // update num blocks
        this->num_blocks++;
        // return 1 block added
        return 1;

    }
}

/**
 *  Updates the eviction order of the tag in question
 *  Input: tag int of which we will update eviction order
 *  Output: N/A, updates evict_order in set
 */
void Set::update_evict_order(uint32_t tag) {
    // remove tag from original place
    this->evict_order->remove(tag);
    // add back in front
    this->evict_order->push_front(tag);
}

/**
 *  Kicksout a block (takes into account eviction order)
 *  Input: N/A
 *  Output: int value of number of write performed
 */
int Set::kickout() {
    // To use for stats update 
    int writes_perfomed = 0;
    // get next to evict
    int to_kick = evict_order->back();
    // checks if write back
    if (!this->write_through) {
        // make block to evict, so can check if dirty
        Block* kick_block = blocks->at(to_kick);
	//check if dirty
        if (kick_block->is_dirty) {
            // do extra write if dirty
            writes_perfomed++;
        }
    }
    // kick block to be evicted
    delete blocks->at(to_kick);
    blocks->erase(to_kick);
    // update evict order
    evict_order->pop_back();

    //return the number of writer performed
    return writes_perfomed;
}
