void setAnimationFrame(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);

// Clears this object from the graphics manager's 6-entry slot table (unless
// the flag at +0x5C is set) during graphics reinitialization.
void sub_08020020(void *object) {
    if (!(2 & *(u16 *)((u8 *)object + 0x5C))) {
        u32 *slotTable = *(u32 **)(*(u8 **)((u8 *)object + 0x8C) + 0x3C);
        u32 zero = 0;
        u32 *slot = slotTable + 0x16;
        s32 i = 5;
        do {
            if (*slot == (u32)object) *slot = zero;
            slot++;
        } while (--i >= 0);
    }
}
