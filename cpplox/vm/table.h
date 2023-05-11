#ifndef _VM_TABLE_H_
#define _VM_TABLE_H_

// hash table

#include <cstddef>

#include "value.h"

namespace vm {

struct Entry {
    const ObjString *key;
    Value value;
};

struct Table {
    static const double TABLE_MAX_LOAD = 0.75;

    size_t count;
    size_t capacity;
    Entry *entries;

    Table() : count(0), capacity(0), entries(nullptr) {}
    ~Table() {
        free(entries);
        entries = nullptr;
        count = 0;
        capacity = 0;
    }

    bool set(const ObjString *const key, Value value) {
        if(count+1>capacity*TABLE_MAX_LOAD) {
            adjustCapacity();
        }
        auto entry = findEntry(key);
        bool isNewKey = entry->key == nullptr;
        if(isNewKey) ++count;

        entry->key = key;
        entry->value = value;
        return isNewKey;
    }
private:
    void adjustCapacity() {
        capacity = capacity < 8 ? 8 : (capacity << 1); // grow capacity
    }
    Entry *findEntry(const ObjString *const key) {
        auto index = key->hash % capacity;
        for(;;) {
            Entry *entry = &entries[index]; // entries + index;
            if (entry->key == key || entry->key == nullptr)
                return entry;
            index = (index + 1) % capacity;
        }
    }
};

}

#endif // _VM_TABLE_H_