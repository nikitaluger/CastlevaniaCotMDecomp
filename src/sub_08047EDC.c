extern s32 gScriptStepCallbacks;
s32 sub_080059DC(s32, s32);
void setAnimationFrame(void *, void *, u16, u8);
void sub_080C31E8(void *, void *, s32, s32);

extern struct { u8 _0[0x146C]; u16 keyInput; } gCameraState;
typedef struct {
    u8 _0[0x14ED];
    u8 chaseMode;                   /* 0xA9 cancels the chase */
    u8 _1[0x174C - 0x14EE];
    s32 followX;                    /* point the effect homes in on */
    s32 followY;
    u8 _2[0x18BC - 0x1754];
    u16 chaserCount;                /* effects currently chasing */
} S_25FF0;
extern S_25FF0 gMainWorkspace;

/* Homing-effect state: play pose 0x10, then run the chase countdown (it
 * drains 10 frames extra while a direction key is held). When the countdown
 * expires, or the follow point comes within 128 pixels, clear the effect's
 * velocity, drop the chaser count and mark it finished; otherwise steer the
 * velocity towards the follow point. Once finished, dispatch the next state. */
void sub_08047EDC(u8 *arg0) {
    u8 *chase;
    u8 *work;
    void *sprite;
    u8 *anim;
    S_25FF0 *world;
    s32 *handlers;
    u32 timer;

    sprite = *(void **)(arg0 + 0x38);
    chase = *(u8 **)(arg0 + 0x3C);
    work = *(u8 **)(arg0 + 0x3C);
    anim = work + 0x34;
    chase = chase + 0x48;

    setAnimationFrame(sprite, anim, 0x10, 0);
    if (*(s16 *)(chase + 0x0A) == 0) {
        *(s32 *)(work + 0x14) = 0;
        *(s32 *)(work + 0x10) = 0;
        arg0[*(s16 *)(arg0 + 0x22) * 2 + 0x19] = 0;
        handlers = &gScriptStepCallbacks;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 2, *handlers);
    } else {
        s32 zero;
        if (gCameraState.keyInput & 0xF0)
            *(u16 *)(chase + 8) -= 0x0A;
        world = &gMainWorkspace;
        if (world->chaseMode == 0xA9)
            *(u16 *)(chase + 8) = 0;
        timer = *(u16 *)(chase + 8);
        timer--;
        zero = 0;
        *(u16 *)(chase + 8) = timer;
        if ((s32)(timer << 16) < 0) {
            *(s16 *)(chase + 0x0A) = zero;
            world->chaserCount--;
        } else {
            s32 followX = *(s32 *)((u8 *)world + 0x174C);
            s32 followY = *(s32 *)((u8 *)world + 0x1750);
            if (sub_080059DC(followX - *(s32 *)(work + 8), followY - *(s32 *)(work + 0xC)) > 0x200000) {
                *(s16 *)(chase + 0x0A) = zero;
                world->chaserCount--;
            } else {
                *(s32 *)(work + 0x10) = followX - *(s32 *)(work + 8);
                *(s32 *)(work + 0x14) = followY - *(s32 *)(work + 0xC);
            }
        }
    }
}
