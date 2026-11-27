extern void *spawnBudgetedEffect(s32, s32);

/* Spawns a 0x1C1 helper object for this parent and clears its state byte. */
void *spawnKind1C1Child(s32 parent)
{
    void *obj = spawnBudgetedEffect(parent, 0x1C1);
    if (obj == 0) {
        return 0;
    }
    *(u8 *)((u8 *)obj + 0x4C) = 0;
    return obj;
}

/* Spawns a 0x1C0 helper object carrying target in its +0x5C field. */
void *spawnParamChild(s32 parent, s32 target)
{
    void *obj = spawnBudgetedEffect(parent, 0x1C0);
    if (obj == 0) {
        return 0;
    }
    *(s32 *)((u8 *)obj + 0x5C) = target;
    *(u8 *)((u8 *)obj + 0x4C) = 0;
    return obj;
}

/* Sets bit 0 of the flags word in every 0x1C2 child of this object's list. */
void sub_080B722C(void *self)
{
    void *child = *(void **)((u8 *)self + 0x30);
    if (child != 0) {
        do {
            if (*(s16 *)child == 0x1C2) {
                u16 *flags = *(u16 **)((u8 *)child + 0x3C);
                *flags |= 1;
            }
            child = *(void **)((u8 *)child + 0x2C);
        } while (child != 0);
    }
}

extern void moveEntityWithCollision(void *, s32);
extern void stepAnimationTrack(s32, void *);
extern void sub_080B72CC(void *);
extern void sub_080C31E0(void *, s32);

/* Falling-object update: applies gravity to the child object, hands its
 * position to the parent, releases its held flag and runs its handler once it
 * has landed (state bit 1). */
void sub_080B6DD4(void *self)
{
    s32 parent = *(s32 *)((u8 *)self + 0x38);
    u8 *pos = (u8 *)*(void **)((u8 *)self + 0x3C) + 0x34;
    moveEntityWithCollision(*(void **)((u8 *)self + 0x3C), 0x4000);
    stepAnimationTrack(parent, pos);
    sub_080B72CC(self);
    if (pos[0] & 2) {
        sub_080C31E0(self, *(s32 *)((u8 *)self + 0x24));
    }
}
