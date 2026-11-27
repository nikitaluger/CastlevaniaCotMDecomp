/* One frame of a scripted actor: integrate velocity into position, refresh the
 * sprite's screen position and timer, then spawn a marker and abort the script
 * when a movement flag is set, or run the off-screen check otherwise. */
s32 stepDelayTimer(void *, s32);
s32 cullOffscreenEntity(void *, s32);
s32 checkGlobalStateChange(void *, s32, void *);
s32 sub_0806D588(s32, void *);
s32 spawnKind2CEntity(s32, s32, s32, s32);
s32 sub_080C31E0(void *, s32);

void sub_0806F050(void *arg0) {
    s32 world;
    s32 delta;
    s32 delta2;
    void *mover;
    void *actor;

    actor = *(void **)((u8 *)arg0 + 0x6C);
    mover = (u8 *)actor + 4;
    world = *(s32 *)((u8 *)arg0 + 0x38);
    if (checkGlobalStateChange(arg0, world, mover) == 0) {
        delta = *(s32 *)((u8 *)mover + 0x08) * (*(s32 *)((u8 *)mover + 0x1C) >> 8);
        if (delta < 0) delta += 0xFF;
        *(s32 *)((u8 *)actor + 0x04) = (s32)(*(s32 *)((u8 *)actor + 0x04) + (delta >> 8));
        delta2 = *(s32 *)((u8 *)mover + 0x0C) * (*(s32 *)((u8 *)mover + 0x1C) >> 8);
        if (delta2 < 0) delta2 += 0xFF;
        *(s32 *)((u8 *)mover + 0x04) = (s32)(*(s32 *)((u8 *)mover + 0x04) + (delta2 >> 8));
        sub_0806D588(world, mover);
        stepDelayTimer((u8 *)actor + 0x30, world);
        if (1 & *(u16 *)((u8 *)(*(void **)((u8 *)mover + 0x3C)) + 0x14)) {
            spawnKind2CEntity(*(s32 *)((u8 *)arg0 + 0x28), 8, *(s32 *)((u8 *)actor + 0x04), *(s32 *)((u8 *)mover + 0x04));
            sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
            return;
        }
        cullOffscreenEntity(arg0, world);
    }
}
