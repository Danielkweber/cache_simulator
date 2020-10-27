#include <map>

using std::map;

class Block {
    public:
        // Track if block is dirty, can be accessed to change
        bool is_dirty;

        // Contructor, can't be dirty when first added
        Block() { this->is_dirty = false; }
        ~Block() {}

};
