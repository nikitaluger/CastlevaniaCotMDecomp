struct S_02025FF0_37604 { u8 _0x000[0x174C]; u32 targetX; u32 targetY; };
extern struct S_02025FF0_37604 gMainWorkspace;
s32 getAngleFromDelta(s32, s32);
s32 stepAnimationTrack(s32, void *);
s32 sub_08037724(s32, void *);
s32 getAngleTurnDirection(s32, s32);
void _call_via_r1(void *, s32, void *);
void setPolarOffset(u8 *, s32, s32);
void advanceMotion(u8 *, s32);

void sub_08037604(void *arg0) {
    s32 sprite = *(s32 *)((u8 *)arg0 + 0x38);
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *animator = work + 0x34;
    u8 *part = work + 0x48;
    u8 *self = arg0;
  s32 hoisted_const;

    if (*(u8 *)(part + 0xb) != 0 &&
        (*(u8 *)(((s16 *)((u8 *)arg0 + 0x22))[0] * 2 + (u8 *)arg0 + 0x19) & 1) != 0)
        *(u8 *)(sprite + 0x2a) &= 0xbf;
    else
        *(u8 *)(sprite + 0x2a) = 0x40 | *(u8 *)(sprite + 0x2a);

    stepAnimationTrack(sprite, animator);
    sub_08037724(sprite, part);

    *(s32 *)part += 0x200;
    if (*(s32 *)part > 0x4000)
        *(s32 *)part = 0x4000;

    {
        s32 oldAngle = *(s32 *)(part + 4);
        s32 angle = getAngleFromDelta((s32)gMainWorkspace.targetY - *(s32 *)(work + 0xC),
                                      (s32)gMainWorkspace.targetX - *(s32 *)(work + 8));
        s32 result = getAngleTurnDirection(oldAngle, angle);
        if (result != -1) {
            if (result == 1)
                *(s32 *)(part + 4) += 1024;
        } else
            *(s32 *)(part + 4) -= 1024;
        *(u32 *)(part + 4) = (u16) *(u32 *)(part + 4);

        hoisted_const = 79;
        switch (*(u16 *)(sprite + 0x28)) {
        case 0x4e:
            *(u8 *)(part + 9) = 0;
            break;
        case 0x4f:
            if (*(u8 *)(part + 9) == 0) {
                s32 t;
                *(u8 *)(part + 9) = 1;
                t = *(u8 *)(part + 0xa) + 1;
                *(u8 *)(part + 0xa) = t;
                if ((u8)t == 0xb) {
                    _call_via_r1(self, *(s32 *)(self + 0x24), self);
                    return;
                }
                if ((u8)t == 9) {
                    *(u8 *)(*(u32 *)(work + 0x28) + 1) = 0;
                    *(u8 *)(part + 0xb) = 1;
                }
            }
            break;
        }
    }
    setPolarOffset(work, *(s32 *)(part + 4), *(s32 *)part);
    advanceMotion(work, 0);
}
