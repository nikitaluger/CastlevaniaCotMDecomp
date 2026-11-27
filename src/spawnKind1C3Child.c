void stepAnimationTrack(s32, void *);
void setSpriteFacingToTarget(s32, s32);
void sub_080C31E8(void *, void *, s32, s32);
void *spawnBudgetedEffect(s32, s32);
extern u8 gMainWorkspace[];

/* Play the effect's animation, face it toward the shared target X, and when the
 * screen flag at gMainWorkspace+0x3C is set, restart the script step/interpreter. */
void sub_080B7A90(void *entity) {
    u8 *self = (u8 *)entity;
    s32 sprite = *(s32 *)(self + 0x38);
    void *work = *(void **)(self + 0x3C);
    stepAnimationTrack(sprite, (u8 *)work + 0x34);
    setSpriteFacingToTarget(sprite, *(s32 *)((u8 *)work + 8));
    if (*(u16 *)(gMainWorkspace + 0x3C) != 0) {
        *(u8 *)(self + (*(s16 *)(self + 0x22) * 2) + 0x19) = 0;
        sub_080C31E8(self + 0x18, self + 0x22, 1, *(s32 *)0x08671BD0);
    }
}

/* Spawn a type-0x1C3 object under the entity and clear its state byte. */
void *spawnKind1C3Child(s32 parent) {
    void *obj = spawnBudgetedEffect(parent, 0x1C3);
    if (obj == 0) {
        return 0;
    }
    *(u8 *)((u8 *)obj + 0x4C) = 0;
    return obj;
}
