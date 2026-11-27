struct GameState {
    u8 _0[0x10];
    s32 field10;
    u8 _1[0x14ED - 0x14];
    u8 field14ED;
    u8 _2[0x14FC - 0x14EE];
    s32 field14FC;
    u8 _3[0x173A - 0x1500];
    u8 field173A;
};
extern struct GameState gMainWorkspace;

s32 stepDelayTimer(void *, s32);
s32 cullOffscreenEntity(void *, s32);
s32 sub_0806D450(void *, s32, void *);
s32 sub_0806D588(s32, void *);
s32 spawnKind2CEntity(s32, s32, s32, s32);
s32 sub_080C31E0(void *, s32);

/* One frame of a scripted actor: apply camera/movement overrides, integrate
 * velocity into its position, advance the script, then choose between
 * aborting the script and running the off-screen check. */
void sub_080705C4(void *arg0) {
    void *actor;
    void *mover;
    s32 world;

    actor = *(void **)((u8 *)arg0 + 0x6C);
    mover = (u8 *)actor + 4;
    world = *(s32 *)((u8 *)arg0 + 0x38);
    if (sub_0806D450(arg0, world, mover) > 0) {
        goto abort;
    }
    {
        s32 delta = *(s32 *)((u8 *)mover + 0x08) * (*(s32 *)((u8 *)mover + 0x1C) >> 8);
        if (delta < 0) delta += 0xFF;
        *(s32 *)((u8 *)actor + 0x04) += delta >> 8;
        delta = *(s32 *)((u8 *)mover + 0x0C) * (*(s32 *)((u8 *)mover + 0x1C) >> 8);
        if (delta < 0) delta += 0xFF;
        *(s32 *)((u8 *)mover + 0x04) += delta >> 8;
    }
    stepDelayTimer((u8 *)actor + 0x30, world);
    sub_0806D588(world, mover);
    {
        void *moveCtrl = *(void **)((u8 *)mover + 0x3C);
        if (*(u16 *)((u8 *)moveCtrl + 0x14) & 1) {
            spawnKind2CEntity(*(s32 *)((u8 *)arg0 + 0x28), 8, *(s32 *)((u8 *)actor + 0x04), *(s32 *)((u8 *)mover + 0x04));
            goto abort;
        }
        if (gMainWorkspace.field14FC != 0) goto abort;
        if (gMainWorkspace.field173A == 0x1C) goto abort;
        if (gMainWorkspace.field14ED != 0) goto offscreen;
        if (gMainWorkspace.field10 == 0) goto offscreen;
    abort:
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    offscreen:
        cullOffscreenEntity(arg0, world);
    }
}
