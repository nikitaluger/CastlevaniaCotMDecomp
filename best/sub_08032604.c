extern s32 checkActorViewBounds(s32, s32);
extern s32 getAngleFromDelta(s32, s32);
extern s32 sub_080147D4(s32);
extern void setSpriteFlipForDirection(s32, s32);
extern void sub_08011344(s32, void *, s32, s32);
extern void sub_0803B7E4(void *, void *, void *);
extern void sub_0803B7E0(void *, void *);
extern u8 gMainWorkspace[];
extern void *gMainObjTimerCallbacks;

void sub_08032604(void *arg0) {
    u8 *self = arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animTrack = work + 0x34;
    u8 *stepState = work + 0x48;
    u8 *ws;
    s32 dx, dy, angle, val, a, b, stepIndex, stepOffset;
    u8 opcode;
    u32 *table;
    void *handler;

    if (checkActorViewBounds((s32)sprite, (s32)work) == 1) return;
    stepState[5] = 0;
    stepState[4] = 0;
    stepState[0xD] = (stepState[0xD] + 0x10) & 0x10;
    stepState[0xE] = 0;
    self[0x80] = 0;
    stepState[0xC] = (stepState[0xC] + 1) & 1;
    ws = gMainWorkspace;
    ws += 0x1750;
    dx = *(s32 *)ws - *(s32 *)(work + 0xC);
    ws = gMainWorkspace;
    ws += 0x174C;
    dy = *(s32 *)ws - *(s32 *)(work + 8);
    angle = getAngleFromDelta(dx, dy);
    if (stepState[0xC] == 0) {
        a = sub_080147D4(*(s32 *)(stepState + 0x10));
        b = sub_080147D4(angle);
        if (a != b) stepState[0xC]++;
    }
    switch (stepState[0xC]) {
    case 0:
        if (*(s32 *)stepState >= 0)
            val = -0x2000;
        else
            val = 0x80 << 6;
        *(s32 *)stepState = val;
        *(s32 *)(work + 0x10) = val;
        break;
    case 1:
        ws = gMainWorkspace;
        ws += 0x1750;
        dx = *(s32 *)ws - *(s32 *)(work + 0xC);
        ws = gMainWorkspace;
        ws += 0x174C;
        dy = *(s32 *)ws - *(s32 *)(work + 8);
        angle = getAngleFromDelta(dx, dy);
        *(s32 *)(stepState + 0x10) = angle;
        if (sub_080147D4(angle) >= 0)
            val = 0xC0 << 6;
        else
        *(s32 *)(work + 0x10) = (-0x3000);
        *(s32 *)stepState = *(s32 *)(stepState + 0x10);
        setSpriteFlipForDirection((s32)sprite, angle);
        break;
    default:
        break;
    }
    sub_08011344((s32)sprite, animTrack, 0, 1);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    sub_0803B7E4(self + 0x18, self + 0x22, gMainObjTimerCallbacks);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepIndex = *(s16 *)(self + 0x22);
    stepOffset = stepIndex * 2;
    opcode = *(u8 *)(self + 0x18 + stepOffset);
    table = *(u32 **)(stepState + 0x14);
    handler = (void *)table[opcode];
    sub_0803B7E0(self, handler);
}
