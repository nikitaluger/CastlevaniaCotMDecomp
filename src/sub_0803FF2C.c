extern void sub_08005E80(s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern s16 D_080CF47C[];

/* Starts a short-lived effect: plays sound 0x80, applies an animation to the
 * state object, clears its per-frame flag byte, invokes the setup callback at
 * 0x08671BB0, then dispatches this entity's initial callback. */
void sub_0803FF2C(void *self) {
    void *handle;
    u8 *state;
    u8 *anim;
    u8 *state48;
    u8 *frameEntry;
    s32 animIndex;
    s32 *cbTable;

    handle = *(void **)(self + 0x38);
    state = *(u8 **)(self + 0x3C);
    anim = state + 0x34;
    state48 = state + 0x48;
    sub_08005E80(0x80);
    animIndex = D_080CF47C[*(u8 *)(self + 0x4C)];
    sub_08011368(handle, anim, animIndex, 0);
    {
        u16 val = *(u16 *)((u8 *)handle + 0x28);
        u16 zero = 0;
        *(u16 *)(state48 + 0x02) = val;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    }
    cbTable = (s32 *)0x08671BB0;
    frameEntry = self + 0x18;
    sub_080C31E4(frameEntry, self + 0x22, *cbTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    frameEntry = frameEntry + *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)((u32)*frameEntry * 4 + *(u32 *)(self + 0x14)));
}
