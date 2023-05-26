#include "table.h"
#include "object.h"

namespace vm {

const ObjString *Table::findString(const ObjString *const key) {
    if (count == 0) return nullptr;
    for (auto index = key->hash & capacityMask; /**/; index = (index + 1) & capacityMask)
    {
        Entry *entry = &entries[index]; // entries + index;
        auto k = entry->key;
        if (k == nullptr) {
            if(IS_NIL(entry->value)) { // find to end
                return nullptr;
            }
            // tombstone continue
        } else if (
            k->length == key->length &&
            k->hash == key->hash &&
            memcmp(k->chars, key->chars, k->length) == 0
        ) {
            return k;
        }
    }
}

Entry *Table::findEntry(const ObjString *const key) {
    // auto index = key->hash % capacity;
    auto index = key->hash & capacityMask;
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
        index = (index + 1) & capacityMask;
    }
}
}
