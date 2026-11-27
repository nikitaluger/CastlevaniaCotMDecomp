/*
 * Actor script step: when the actor has fallen below the camera, start a
 * bounce (random horizontal scatter and upward speed from sub_0804C674), set
 * the bounce angle from its facing, clear the step flag and go to step 1.
 */
extern void sub_0804C674(void *, s32 *, s32 *);  /* random bounce velocities */
extern s32 getSpriteFacingSign(s32);  /* +1 when the sprite faces right, -1 when left */
extern void sub_080C31E8(void *, void *, s32, s32);

struct CameraY {
    u8 _pad[0x172C];
    s32 y;
};
extern struct CameraY gMainWorkspace;

void sub_0804C56C(u8 *arg0) {
    s32 sprite = *(s32 *)(arg0 + 0x38);
    u8 *work = *(u8 **)(arg0 + 0x3C);
    u8 *pose = work + 0x48;
    if (*(s32 *)(work + 0x0C) >= gMainWorkspace.y + 0x200000) {
        sub_0804C674(arg0, (s32 *)(work + 0x54), (s32 *)(work + 0x58));
        {
            s32 facing = getSpriteFacingSign(sprite);
            s32 angle = 0xE000;
            if (facing < 0)
                angle = 0xA000;
            *(s32 *)(pose + 0x20) = angle;
        }
        *(u8 *)(arg0 + (*(s16 *)(arg0 + 0x22) * 2) + 0x17) = 0;
        {
            s32 *stepCallback = (s32 *)0x08671BD8;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 1, *stepCallback);
        }
    }
}
