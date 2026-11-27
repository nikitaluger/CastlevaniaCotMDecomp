extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

struct GameState1844 {
    u8 _0[0x1844];
    u32 flags;
};
extern struct GameState1844 gMainWorkspace;
extern s32 gMainObjTimerCallbacks;

/* Script restart for a mode-3 entity: allocate its 0x14-byte script buffer in
 * slot 3; if that fails, run the entity's current update callback instead,
 * otherwise raise the global 0x40000000 flag and restart the script step. */
void sub_08086EE8(void *arg0) {
    u8 *self = (u8 *)arg0;

    if (allocWorkSlot(arg0, 0, 0x14, 3) == 0) {
        sub_080C31E0(arg0, *(void **)(self + 0x24));
        return;
    }

    gMainWorkspace.flags |= 0x40000000;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *advanceTable = &gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *advanceTable);
    }
}
