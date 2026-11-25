/* If the target's primary flag is set, mark the state's direction field when
 * another flag is set and raise flag 0x400; then lay out the target using the
 * state's stored coordinates. */
s32 sub_080160A0(s32, s32, s32, s32, void *);

void sub_08092374(void *entity, void *target) {
    s32 position;
    u16 *flags;
    void *state;
    state = *(void **)((s8 *)entity + 0x3C);
    flags = (u16 *)((s8 *)target + 2);
    if (1 & *flags) {
        if (8 & *(u16 *)((s8 *)target + 0)) {
            *(s16 *)((s8 *)state + 0xE) = 1;
        }
        if (1 & *flags) {
            *flags = (u16)(0x400 | *flags);
        }
    }
    position = *(s32 *)((s8 *)state + 4);
    sub_080160A0(position, *(s32 *)((s8 *)state + 0x10), position, *(s32 *)((s8 *)state + 0x14), target);
}
