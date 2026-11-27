void *createChildObject(void *parent, s32 kind);

/* Create a kind-0x22 object under `parent` and store `value` in its +0x3C
 * field; returns NULL when the object cannot be allocated. */
void *sub_08008D18(void *parent, s32 value) {
    void *child = createChildObject(parent, 0x22);
    if (child == NULL) return NULL;
    *(s32 *)((u8 *)child + 0x3C) = value;
    return child;
}

/* Point the object's sprite at the frame picked by (obj->f4C, owner->f4C) in
 * the frame table, and set or clear the sprite attribute bit 0x40 depending on
 * whether the owner's direction field is negative. */
void sub_08008C28(u8 *obj) {
    u8 *sprite;
    u8 *entry;
    sprite = *(u8 **)(obj + 0x38);
    if (*(s32 *)(*(u8 **)(obj + 0x28) + 0x4C) < 0) {
        entry = sprite + 0x2A;
        *(u8 *)entry &= 0xBF;
        return;
    }
    entry = sprite + 0x2A;
    *(u8 *)entry |= 0x40;
    entry = (u8 *)0x080CA9F4 + *(s32 *)(obj + 0x4C) * 2 + *(s32 *)(*(u8 **)(obj + 0x28) + 0x4C) * 4;
    *(u32 *)(sprite + 0x24) = *(u16 *)entry * 8 + 0x08639ECC;
}
