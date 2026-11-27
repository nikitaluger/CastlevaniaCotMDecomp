extern void forceAnimationFrame(void *, void *, s32, s32);
extern void setEffectBehavior(s32, s32);
extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080C31E0(void *, void *);
extern void *gMainObjTimerCallbacks;

/* AI script step: pose the sprite at frame 0xF, clear a part field and several work
 * flags, play cue 0x165, then advance the script and dispatch the next state callback. */
void sub_0809A0C0(void *entity)
{
    u8 *self;
    void *sprite;
    u8 *work;
    u8 *animState;
    u8 *parts;
    u8 *stepBase;
    s32 zero;
    void **scriptCb;

    self = (u8 *)entity;
    sprite = *(void **)(self + 0x38);
    work = *(u8 **)(self + 0x3C);
    animState = work + 0x34;
    parts = work + 0x48;

    forceAnimationFrame(sprite, animState, 0xF, 0);
    setEffectBehavior(*(s32 *)(parts + 8), 0);

    zero = 0;
    *(u8 *)(parts + 0x1F) = 1;
    *(u8 *)(work + 0x69) = (u8)zero;
    *(u8 *)(work + 0x6A) = (u8)zero;
    *(u8 *)(self + 0x4C) = (u8)zero;

    sub_08005E80(0x165);

    *(s8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = (s8)zero;
    scriptCb = &gMainObjTimerCallbacks;
    stepBase = self + 0x18;
    sub_080C31E4(stepBase, self + 0x22, *scriptCb);

    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepBase = stepBase + *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + (*stepBase * 4)));
}
