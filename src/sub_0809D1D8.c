extern s32 sub_0809D0E0();

/* Advance the actor step, then set the body sub-structure's bytes at +0x14 and
 * +0x15 to 0 and 0x28. */
void sub_0809D1D8(void *entity) {
    void *body;

    body = *(s32 *)((s8 *)entity + 0x3C) + 0x48;
    sub_0809D0E0();
    *(s8 *)((s8 *)body + 0x14) = 0;
    *(s8 *)((s8 *)body + 0x15) = 0x28;
}
