/* Release the child object linked at pose+0x14: set bit 0 of its u16 state
 * word at +0x5C, then clear the parent's link to it. */
void sub_0803F24C(void *entity) {
    void *work = *(void **)((u8 *)entity + 0x3C);
    u8 *pose = (u8 *)work + 0x48;
    void *child = *(void **)(pose + 0x14);
    if (child != 0) {
        u16 *flags;
        s32 oldFlags;
        s32 newFlags;
        s32 zero;
        flags = (u16 *)((u8 *)child + 0x5C);
        oldFlags = *flags;
        newFlags = 1;
        zero = 0;
        newFlags |= oldFlags;
        *flags = newFlags;
        *(void **)(pose + 0x14) = zero;
    }
}
