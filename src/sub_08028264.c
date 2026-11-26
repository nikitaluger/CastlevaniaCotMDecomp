extern s32 sub_0800583C(s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 sub_080C364C(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 D_08671BFC;
extern s32 gMainObjTimerCallback;
extern u8 D_0866DA10[];

/* Bob this object sideways: advance its phase timer, offset the sub-object's
 * x position from its base by the curve value, and reset the phase after 0x50
 * steps. */
void sub_08029020(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *sub = *(u8 **)(self + 0x3C);
    u8 *anim = sub + 0x34;
    u8 *state = sub + 0x48;
    s32 *sineFn;
    s32 phase;

    setAnimationFrame(sprite, anim, 0, 1);
    sineFn = &D_08671BFC;
    phase = sub_080C364C(*(s32 *)(state + 8) << 16, 0x50);
    *(s32 *)(sub + 0xC) = *(s32 *)(state + 4) + (sub_080C31E0(phase + 0x4000, *sineFn) << 4);
    if ((*(s32 *)(sub + 0x50))++ > 0x50) {
        *(s32 *)(state + 8) = 0;
    }
}

/* Enter the next state of this object: give it its state-handler table, bump
 * the state index and that index's counter, then dispatch to the handler. */
void sub_08028264(void *arg0) {
    u8 *self = (u8 *)arg0;
    s16 idx;
    s32 entryOff;
    u8 *stateBase;
    u8 *entry;

    setAnimationFrame(*(s32 *)(self + 0x38), *(u8 **)(self + 0x3C) + 0x34, 3, 1);
    *(u32 *)(self + 0x14) = (u32)D_0866DA10;

    *(u16 *)(self + 0x22) += 1;
    idx = *(s16 *)(self + 0x22);
    *(u8 *)(self + idx * 2 + 0x19) += 1;

    idx = *(s16 *)(self + 0x22);
    entryOff = idx * 2;
    stateBase = self + 0x18;
    entry = stateBase + entryOff;
    sub_080C31E0((s32)self, *(s32 *)(*(u8 **)(self + 0x14) + *(u8 *)entry * 4));

    *(u16 *)(self + 0x22) -= 1;
}
