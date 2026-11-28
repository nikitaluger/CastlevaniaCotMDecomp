extern s32 stepDelayTimer(void *, void *);
extern s32 applyAreaEffectBehavior(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void setDirectionVector(void *, u32);
extern void sub_080C31E0(void *, void *);

struct HomingTargetState {
    u8 _pad0[0x14ED];
    u8 mode;
    u8 _pad1[0x174C - 0x14EE];
    s32 worldTargetX;
    s32 worldTargetY;
    u8 _pad2[0x18C2 - 0x1754];
    u16 spriteAttr;
};
extern struct HomingTargetState gMainWorkspace;

/* Homing-projectile tick: rotate the angle, ease the actor toward the global
 * target, project it to screen, and abort when its timer expires or the global
 * mode changes. */
void sub_080751C4(void *arg0) {
    void *actor;
    void *mover;
    void *world;
    struct HomingTargetState *d;
    s32 targetX;
    s32 targetY;
    s32 currentX;
    s32 deltaX;
    s32 currentY;
    s32 deltaY;
    u32 angle;

    actor = *(void **)((u8 *)arg0 + 0x6C);
    mover = (u8 *)actor + 4;
    world = *(void **)((u8 *)arg0 + 0x38);
    if (applyAreaEffectBehavior(arg0, world, mover) != 0)
        return;

    angle = *(u32 *)((u8 *)mover + 0x54);
    angle = (angle - 4) & 0xFF;
    *(u32 *)((u8 *)mover + 0x54) = angle;
    setDirectionVector(mover, angle);

    d = &gMainWorkspace;
    targetX = d->worldTargetX + (*(s32 *)((u8 *)mover + 8) << 5);
    targetY = d->worldTargetY + (*(s32 *)((u8 *)mover + 0xC) << 5);

    currentX = *(s32 *)((u8 *)actor + 4);
    deltaX = targetX - currentX;
    if (deltaX < 0)
        deltaX += 3;
    *(s32 *)((u8 *)actor + 4) = currentX + (deltaX >> 2);

    currentY = *(s32 *)((u8 *)mover + 4);
    deltaY = targetY - currentY;
    if (deltaY < 0)
        deltaY += 3;
    *(s32 *)((u8 *)mover + 4) = currentY + (deltaY >> 2);

    sub_0806D588(world, mover);
    *(u16 *)world = d->spriteAttr;
    if (stepDelayTimer((u8 *)actor + 0x20, world) == 0) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }
    if (d->mode != 0x32)
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
}
