extern u8 gMainWorkspace[];

extern void advanceMotion(void *, s32);
extern void stepAnimationTrack(void *, void *);
extern s32 checkActorViewBounds(void *, void *);

typedef void (*Func)(void *);

/* Actor update: apply velocity, advance the animation, then run a movement
 * timer. At 0x80 finish when the actor has no follow-up flag; once past 0x80,
 * leaving the viewport flags the actor's stored parent before finishing. */
void sub_08032DA8(u8 *self) {
    void *sprite;
    u8 *work;
    u8 *animState;
    u8 *moveState;
    s32 nextTimer;
    s32 offScreen;
    s32 parent;
    u8 *base;
    u32 *parentPtr;

    sprite = *(void **)(self + 0x38);
    work = *(u8 **)(self + 0x3C);
    animState = work + 0x34;
    moveState = work + 0x48;
    *(s32 *)(work + 0x10) = *(s32 *)(work + 0x10) + *(s32 *)(moveState + 4);
    advanceMotion(work, 0);
    stepAnimationTrack(sprite, animState);
    nextTimer = moveState[0] + 1;
    moveState[0] = (u8)nextTimer;
    if ((u8)nextTimer == 0x80) {
        if (self[0x7C] == 0) {
            ((Func)(*(u32 *)(self + 0x24)))(self);
            return;
        }
    }
    if (moveState[0] > 0x80) {
        offScreen = checkActorViewBounds(sprite, work);
        if (offScreen == 1) {
            base = gMainWorkspace;
            parentPtr = (u32 *)(base + 0x1870);
            parent = *(s32 *)(self + 0x28);
            if (parent != *(s32 *)parentPtr) {
                *(u8 *)(parent + 0x80) = (u8)offScreen;
            }
            ((Func)(*(u32 *)(self + 0x24)))(self);
        }
    }
}
