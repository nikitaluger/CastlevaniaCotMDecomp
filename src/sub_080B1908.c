extern void sub_080C31E0(void *, s32);

/* Set the global state word at gMainWorkspace+0x3C to 2, then chain to the
 * entity's saved update callback at +0x24. */
void sub_080B1908(void *entity) {
    s16 *state = (s16 *)0x02025FF0;
    state[0x1E] = 2;
    sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
}
