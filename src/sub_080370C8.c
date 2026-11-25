extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_0803B194(void *);
extern void sub_0803B1A4(void *);

/* Mark the three graphic slots at work+0x54 as loaded and, after 45 frames,
 * release them and advance to the next script step. */
void sub_080370C8(void *arg0) {
    void *gfxSlots;
    const u32 *handlerTable;
    gfxSlots = *(u32 *)((u8 *)arg0 + 0x3C) + 0x54;
    sub_0803B194(gfxSlots);
    if (*(u8 *)(arg0 + (s32)*(s16 *)(arg0 + 0x22) * 2 + 0x19) == 0x2D) {
        sub_0803B1A4(gfxSlots);
        *(u8 *)(arg0 + (s32)*(s16 *)(arg0 + 0x22) * 2 + 0x19) = 0;
        handlerTable = (const u32 *)0x08671BD0;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0, *handlerTable);
    }
}
