extern s32 sub_08000A70(s32 heapId, s32 size, s32 align);

/* Allocate `units` 8-byte blocks from heap 0 (4-byte aligned) as an object's
 * animation/gfx workspace; the block pointer comes back in r0. */
char sub_080111B0(s32 units) {
    sub_08000A70(0, units * 8, 4);
}
