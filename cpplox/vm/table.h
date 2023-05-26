#ifndef _VM_TABLE_H_
#define _VM_TABLE_H_

// hash table

#include <cstddef>

#include "value.h"

namespace vm {

struct ObjString;
struct Entry {
    ObjString *key;
    Value value;
};

struct Table {
    static constexpr double TABLE_MAX_LOAD = 0.75;

    size_t count;
    size_t capacityMask; // capacityMask = capacity - 1
    Entry *entries;

    Table() : count(0), capacityMask(-1), entries(nullptr) {}
    ~Table() {
        free(entries);
        entries = nullptr;
        count = 0;
        capacityMask = -1;
    }

    bool set(ObjString *const key, Value value) {
        if (count + 1 > (capacityMask + 1) * TABLE_MAX_LOAD) {
            adjustCapacity();
        }
        auto entry = findEntry(key);
        bool isNewKey = entry->key == nullptr;
        if(isNewKey && IS_NIL(entry->value)) ++count;

        entry->key = key;
        entry->value = value;
        return isNewKey;
    }
    bool get(const ObjString *const key, Value *value) {
        if (count == 0) return false;
        auto entry = findEntry(key);
        if(entry->key==nullptr) return false;
        *value = entry->value;
        return true;
    }
    bool remove(const ObjString *const key) {
        if (count == 0) return false;
        auto entry = findEntry(key);
        if(entry->key==nullptr) return false;
        entry->key=nullptr;
        entry->value=BOOL_VAL(true);
        return true;
    }

    void addAll(Table *from) {
        for (int i = 0; i <= from->capacityMask; ++i) {
            auto entry = &from->entries[i];
            if (entry->key != nullptr) {
                set(entry->key, entry->value);
            }
        }
    }

    const ObjString *findString(const ObjString *const key);

private:
    Entry *findEntry(const ObjString *const key);
    void adjustCapacity() {
        auto oldEntries = entries;
        auto oldCapacity = capacityMask + 1;
        auto capacity = oldCapacity < 8 ? 8 : (oldCapacity << 1); // grow capacity
        capacityMask = capacity - 1;
        entries = (Entry *)malloc(sizeof(Entry) * capacity);
        for (int i = 0; i < capacity; ++i) {
            entries[i].key = nullptr;
            entries[i].value = NIL_VAL;
        }

        count = 0;
        for (int i = 0; i < oldCapacity; i++) {
            auto entry = &oldEntries[i];
            if (entry->key == nullptr) continue;
            auto dest = findEntry(entry->key);
            dest->key = entry->key;
            dest->value = entry->value;
            ++count;
        }
        free(oldEntries);
    }
};

}

#endif // _VM_TABLE_H_