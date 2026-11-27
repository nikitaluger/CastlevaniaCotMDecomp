extern u32 gMainObjTimerCallbacks[];

s32 scaleByRandom(s32);
void stepAnimationTrack(s32, void *);
void advanceMotion(void *, s32);
void setSpriteFacingToTarget(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Steps the work object's physics and animation and flips the sprite with its
 * depth; when it falls below the bounce height limit it records the bounce
 * point, lowers the limit, sets the part's random timer and runs the next
 * script step. */
void sub_08044810(u8 *arg0) {
    u8 *self = arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animator = work + 0x34;
    u8 *part = 0x48 + work;
    s32 zero;

    advanceMotion(work, 0);
    stepAnimationTrack(sprite, animator);
    setSpriteFacingToTarget(sprite, *(s32 *)(work + 8));
    {
        s32 y = *(s32 *)(work + 0xC);
        if (y < *(s32 *)(self + 0x6C)) {
            s32 timer;
            *(s32 *)(work + 0x48) = y;
            *(s32 *)(self + 0x6C) = *(s32 *)(self + 0x6C) + (s32)0xFFE00000;
            timer = scaleByRandom(0x3C) + 0x78;
            zero = 0;
            *(u8 *)(part + 4) = timer;
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
            {
                u32 *scriptHandlers = gMainObjTimerCallbacks;
                sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
            }
        }
    }
}
