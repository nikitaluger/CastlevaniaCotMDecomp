extern void sub_080C31E0(void *entity, void *release);
extern void sub_080161F0(void *object);

/* Game state: the global entity slot table starts at +0x1780. */
struct S_02025FF0 {
    u8 pad0[0x14EC];
    u8 b14EC;
    u8 pad1[0x1780 - 0x14ED];
    u32 arr1780[1];
};
extern struct S_02025FF0 gMainWorkspace;

/*
 * Releases the entity: frees the object attached to its state block (+0x30),
 * clears its entry in the global entity slot table and runs the state block's
 * release handler (+0x1C, slot 7).
 */
void sub_0806E6BC(void *entity) {
    u8 *p = (u8 *)entity;
    u8 *state = *(u8 **)(p + 0x6C) + 4;

    sub_080161F0(*(void **)(state + 0x2C));
    gMainWorkspace.arr1780[*(s32 *)(p + 0xAC)] = 0;
    sub_080C31E0(entity, *(void **)(state + 0x18));
}
