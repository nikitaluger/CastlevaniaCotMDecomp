extern void sub_080C31E0(void *, s32);

/* Entity work state: +0x24 holds a pending update callback, +0x6C a flag word. */
struct Entity6C {
    u8 _0[0x24];
    s32 update;
    u8 _28[0x44];
    u16 flags;
};

/* If the entity's flag word has bit 0x10 set, chain to its pending update
 * callback. */
void sub_080307F4(struct Entity6C *entity) {
    if (0x10 & entity->flags) {
        sub_080C31E0(entity, entity->update);
    }
}
