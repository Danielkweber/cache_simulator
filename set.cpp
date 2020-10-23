#include "set.h"
#include <utility>

using std::pair;

Set::Set(int set_size, char evict_policy, bool write_through, bool write_allocate) {
    this->num_blocks = 0;
    this->set_size = set_size;
    this->evict_policy = evict_policy;
    this->write_through = write_through;
    this->write_alloc = write_allocate;
    this->blocks = new map<int, Block*>;
    this->evict_order = new list<int>;

}


bool Set::is_in_set(int tag) {
    return (this->blocks->find(tag) != blocks->end());
}

int Set::add_block(int tag) {
    if (this->num_blocks > this->set_size) {
        int write_back = kickout();
        blocks->insert(pair<int, Block*>(tag, new Block));
        evict_order->push_front(tag);
        this->num_blocks++;
        return 1 + write_back;
    } else {
        blocks->insert(pair<int, Block*>(tag, new Block));
        evict_order->push_front(tag);
        this->num_blocks++;
        return 1;

    }
}
void Set::update_evict_order(int tag) {
    this->evict_order->remove(tag);
    this->evict_order->push_front(tag);
}
int Set::kickout() {
    int writes_perfomed = 0; //To use for statistics update
    int to_kick = evict_order->back();
    if (!this->write_through) {
        Block* kick_block = blocks->at(to_kick);
        if (kick_block->is_dirty) {
            writes_perfomed += 1;
        }
    }
    blocks->erase(to_kick);
    evict_order->pop_back();
    return writes_perfomed;
}