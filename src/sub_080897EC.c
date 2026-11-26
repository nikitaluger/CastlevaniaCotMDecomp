extern u32 gMainWorkspace[];
void sub_0806D588(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Tick of a grounded actor while the global state is 0x10: mark the script
 * halted, clear the current script step and advance the script, then refresh
 * the sprite's screen offset from the mover's position. */
void sub_080897EC(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *moverPos = *(u8 **)(self + 0x6C) + 4;
    void *sprite = *(void **)(self + 0x38);
    if (gMainWorkspace[5] == 0x10) {
        gMainWorkspace[7] = 4;
        *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *stepTable = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *stepTable);
        }
    }
    sub_0806D588(sprite, moverPos);
}
