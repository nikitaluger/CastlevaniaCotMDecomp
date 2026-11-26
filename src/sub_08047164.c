extern u8 D_080CF86A[];
extern u8 D_080CF5B8[];
extern u8 D_080CF5D8[];
extern void copyPoseAttrs(void *, void *);

struct SlotOwner { u8 pad[0x4C]; u8 slot; };
struct FirstTarget { u8 pad[0x28]; u32 object; };
struct SecondTarget { u8 pad[0x04]; u8 *object; };
struct ReadyFlag { u8 pad[0x01]; u8 ready; };
struct LookupKey { u8 pad[0x28]; u16 id; };
struct RecordPair { void *first; void *second; };

/* Applies the size record matching the requested id to two objects: marks the
 * second object ready, then looks the id up in the 4x3 slot table and copies
 * the matching 8-byte record from both record tables into the two objects. */
void sub_08047164(struct SlotOwner *owner, struct FirstTarget *first, struct SecondTarget *second, struct LookupKey *key) {
    struct RecordPair record;
    u32 i;
    u8 *firstRecord, *secondRecord;
    u16 *entry;
    u8 slot;
    u16 id;
    u8 *table;

    ((struct ReadyFlag *)second->object)->ready = 1;
    i = 0;
    table = D_080CF86A;
    slot = owner->slot;
    id = key->id;
    entry = (u16 *)(table + slot * 2);
    secondRecord = D_080CF5D8;
    firstRecord = D_080CF5B8;
    do {
        if (id == *entry) {
            record.first = firstRecord;
            record.second = secondRecord;
            break;
        }
        entry += 3;
        secondRecord += 8;
        firstRecord += 8;
        i++;
    } while (i <= 3);
    copyPoseAttrs((void *)first->object, record.first);
    copyPoseAttrs((void *)second->object, record.second);
}
