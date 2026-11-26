extern s32 setAnimationFrame(void *, void *, s32, s32);
extern s32 sub_08014114(void *, s32, s32, s32, s32, s32);
extern s32 sub_080146D0(void *, s32, s32);
extern s32 sub_08014900(s32);
extern s32 sub_080C31E0(u16, s32);
extern s32 sub_080C31E4(void *, void *, s32);

/* Steering block at motion+0x48 for this bobbing projectile. */
struct BobbingSteer {
    s32 base;   /* +0: baseline the sine bob oscillates around */
    u32 phase;  /* +4: rotating angle, advanced by 0x800 each frame */
    s32 angle;  /* +8: heading used when the projectile locks on */
};

/* Updates a bobbing projectile: spins a phase to drive a sine-wave vertical
 * motion; once it is on screen near the target it locks a heading and fires
 * the end callback. */
void sub_0804F220(void *entity)
{
    void *sprite;
    void *motion;
    void *collision;
    struct BobbingSteer *steer;
    u32 phase;
    s32 yVel;
    int callback;
    s16 stateIndex;

    sprite = *(void **)((u8 *)entity + 0x38);
    motion = *(void **)((u8 *)entity + 0x3C);
    collision = (u8 *)motion + 0x34;
    steer = (struct BobbingSteer *)((u8 *)motion + 0x48);
    setAnimationFrame(sprite, collision, 0, 1);
    phase = steer->phase + 0x800;
    phase &= 0xFFFF;
    steer->phase = phase;
    yVel = ((sub_080C31E0((u16)phase, *((s32 *)0x08671BFC)) << 1) + steer->base) - (*((s32 *)((u8 *)motion + 0x0C)));
    *((s32 *)((u8 *)motion + 0x14)) = yVel;
    if (sub_08014114(*((void **)((u8 *)motion + 8)), *((s32 *)((u8 *)motion + 0x0C)), 0, 0, 0, 0) != 0) {
        if (sub_08014900(*((s32 *)((u8 *)motion + 8))) <= 0x680000) {
            sub_080146D0(motion, steer->angle, 0x28000);
            stateIndex = *(s16 *)((u8 *)entity + 0x22);
            *((u8 *)entity + (stateIndex * 2) + 0x19) = 0;
            callback = 0x08671BB0;
            sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *((s32 *)callback));
        }
    }
}
