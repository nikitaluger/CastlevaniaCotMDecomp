void sub_08061F88(void);
void sub_080C31E4(void *, void *, u32);
extern u16 D_03000830[];
extern u32 D_08671BB0[];

/* Publish the object's display word, refresh the screen state, then reset the
 * object's script slot counter and re-arm the command-script step. */
void sub_08061B10(void *obj) {
    void *display = *(void **)((u8 *)obj + 0x3C);
    D_03000830[3] = *(u16 *)display;
    sub_08061F88();
    *(u8 *)((u8 *)obj + (*(s16 *)((u8 *)obj + 0x22) * 2) + 0x19) = 0;
    {
        u32 *scriptTable;
        scriptTable = D_08671BB0;
        sub_080C31E4((u8 *)obj + 0x18, (u8 *)obj + 0x22, *scriptTable);
    }
}
