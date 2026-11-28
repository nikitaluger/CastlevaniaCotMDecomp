extern s32 getAngleFromDelta(s32, s32);
extern s32 getSpriteFacingSign(s32);
extern void setPolarOffset(u8 *, s32, s32);
extern void sub_080C31E4(u8 *, u8 *, u32);

struct CameraXY { u8 _0[0x174C]; s32 x; s32 y; };
extern struct CameraXY gMainWorkspace;

void sub_0804C4C4(u8 *self)
{
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    s32 angle;

    angle = getAngleFromDelta(gMainWorkspace.y - *(s32 *)(work + 0xC),
                              gMainWorkspace.x - *(s32 *)(work + 8)) & 0xFFFF;
    if (getSpriteFacingSign(sprite) < 0) {
        if (angle > 0x6000) {
            angle = 0x6000;
        } else if (angle <= 0x47FF) {
            angle = 0x4800;
        }
    } else if (angle <= 0x1FFF) {
        angle = 0x2000;
    } else if (angle > 0x3800) {
        angle = 0x3800;
    }
set:
    setPolarOffset(work, angle, 0x30000);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *stepCallback = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *stepCallback);
    }
}
