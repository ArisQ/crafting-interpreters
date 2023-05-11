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
        for (int i = 0; i < from->capacity; ++i) {
            auto entry = &from->entries[i];
            if (entry->key != nullptr) {
                set(entry->key, entry->value);
            }
        }
    }
private:
    void adjustCapacity() {
        auto oldEntries = entries;
        auto oldCapacity = capacity;

        capacity = capacity < 8 ? 8 : (capacity << 1); // grow capacity
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
    Entry *findEntry(const ObjString *const key) {
        auto index = key->hash % capacity;
        Entry *tombstone = nullptr;
        for(;;) {
            Entry *entry = &entries[index]; // entries + index;
            if (entry->key == nullptr) {
                if(IS_NIL(entry->value)) { // find to end
                    return tombstone == nullptr ? entry : tombstone;
                } else { // find tombstone
                    if (tombstone == nullptr) tombstone = entry;
                }
            } else if (entry->key == key) {
                return entry;
            }
            index = (index + 1) % capacity;
        }
    }
};

}

#endif // _VM_TABLE_H_