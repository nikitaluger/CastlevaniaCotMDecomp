extern void sub_08011368(s32, void *, s32, s32);
extern void sub_0801468C(s32, s32);
extern s32 sub_08014900(s32);
extern s32 sub_08014A04(void *, s32, s32, s32, s32);
extern s32 sub_08014A6C(void *, s32, s32, s32);
extern void sub_08014B1C(void *, void *, s32, s32);
extern s32 sub_080C364C(s32, s32);
extern s32 _call_via_r1(void *, void *);
extern void _call_via_r3(void *, void *, s32, void *);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];

/*
 * Updates an entity's movement state: derives a screen-space position from the
 * camera, checks whether it falls inside a target region, converts a fixed-
 * point angle through a lookup function, and dispatches the matching script
 * step or fires its attack.
 */
void sub_08022E2C(u8 *entity) {
    s32 sprite = *(s32 *)(entity + 0x38);
    u8 *motion = *(u8 **)(entity + 0x3C);
    u8 *status = motion + 0x34;
    u8 *motionEx = motion + 0x48;
    s32 screenX, screenY;
    u8 *coordBase;
    u32 zero;

    sub_08011368(sprite, status, 0, 1);
    coordBase = D_02021E90;
    {
        u8 *globalState = D_02025FF0;
        u8 *camIndex = globalState + 0x18A8;
        u32 camOffset = (*(u8 *)camIndex + 1) << 6;
        u8 *coordXBase = coordBase + 0x1278;
        screenX = *(s32 *)(coordXBase + camOffset) + (0xF1 << 0xF);
    }
    screenY = *(s32 *)(motionEx + 0x20);
    if (sub_08014A04(motion, screenX, screenY, 0xC0 << 0xE, 0x80 << 0xD) == 1) {
        if (*(s16 *)(motionEx + 0xA) == 1) *(u16 *)(motionEx + 0xC) = 1;
    }
    if (*(u8 *)(status + 1) == 1 && *(s32 *)(status + 4) == 1) {
        *(u16 *)(motionEx + 4) = 0;
    }
    {
        void **trigFn = (void **)0x08671BFC;
        s32 trigArg = sub_080C364C(*(s16 *)(motionEx + 4) << 0x10, 0x24);
        *(u32 *)(motionEx + 0) = _call_via_r1((void *)trigArg, *trigFn) * 2;
    }
    {
        u16 step = *(u16 *)(motionEx + 4) + 1;
        zero = 0;
        *(u16 *)(motionEx + 4) = step;
    }
    if (*(s16 *)(motionEx + 0xC) == 1) {
        if (sub_08014A6C(motion, *(s32 *)(motionEx + 0x54), 0x80 << 0x6, 0) == 1) {
            u8 *stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            stepData[0x19] = zero;
            {
                void **scriptFn = (void **)0x08671BD0;
                _call_via_r3(entity + 0x18, entity + 0x22, 2, *scriptFn);
            }
        }
    } else {
        if (sub_08014900(*(s32 *)(motionEx + 0x1C)) > (0xD2 << 0x10)) {
            u8 *stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            stepData[0x19] = zero;
            {
                void **scriptFn = (void **)0x08671BD0;
                _call_via_r3(entity + 0x18, entity + 0x22, 4, *scriptFn);
            }
            return;
        }
        sub_08014B1C(motion, motionEx + 0x50, screenX, screenY);
        sub_0801468C(sprite, *(s32 *)(motionEx + 0x54));
    }
}
