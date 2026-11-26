void setAnimationFrame(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

// Unregisters this entity from the graphics manager's 10-slot table (unless
// the flag at +0x64 is set) by clearing its matching entry.
void sub_08019978(void *entity) {
    if (!(1 & *(u16 *)((u8 *)entity + 0x64))) {
        u32 *slotTable = *(u32 **)(*(u8 **)((u8 *)entity + 0x8C) + 0x3C);
        u32 zero = 0;
        u32 *slot = slotTable + 0x20;
        s32 i = 9;
        do {
            if (*slot == (u32)entity) *slot = zero;
            slot++;
        } while (--i >= 0);
    }
}
