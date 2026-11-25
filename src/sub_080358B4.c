extern void sub_0803B194(void *);
extern void sub_0803B1A4(void *);
extern void sub_080C31E8(void *, void *, s32, s32);

/* When the selected element's countdown byte reaches 30 frames, clear the three
 * flag bytes and fire the callback selected from the 0x08671BD0 table. */
void sub_080358B4(void *actor) {
    void *flags;
    const u32 *callbackTable;

    flags = *(u32 *)((u8 *)actor + 0x3C) + 0x54;
    sub_0803B194(flags);
    if (*(u8 *)(actor + (s32)*(s16 *)(actor + 0x22) * 2 + 0x19) == 0x1E) {
        sub_0803B1A4(flags);
        *(u8 *)(actor + (s32)*(s16 *)(actor + 0x22) * 2 + 0x19) = 0;
        callbackTable = (const u32 *)0x08671BD0;
        sub_080C31E8(actor + 0x18, actor + 0x22, 0, *callbackTable);
    }
}
