//Daniel Weber JHED:dweber11
//Vance Wood JHED: vwood3
#ifndef BLOCK_H
#define BLOCK_H

#include <map>

using std::map;

class Block {
    public:
        // Track if block is dirty, can be accessed to change
        bool is_dirty;

        // Contructor, can't be dirty when first added
        Block() { this->is_dirty = false; }
        // Destructor
        ~Block() {}

};
#endif