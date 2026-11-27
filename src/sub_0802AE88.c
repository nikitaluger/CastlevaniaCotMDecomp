void stepAnimationTrack(void *, void *);
void moveObjectHorizontally(void *, s32, s32);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void applySpritePaletteVariant(void *, void *);
void sub_08013C8C(void *, void *);
s32 checkActorViewBounds(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void sub_0802B178(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080C31E8(void *, void *, s32, void *);
extern void *sScriptStepCallbacks;
extern u8 D_0866DAE4[];

/* Updates an entity's child sprite: checks visibility/animation, handles a
 * flip request, advances the step script, then dispatches the current handler. */
void sub_0802AE88(void *obj) {
    void *sprite;
    void *owner;
    void *ownerWork;

    sprite = *(void **)((u8 *)obj + 0x38);
    owner = *(void **)((u8 *)obj + 0x3C);
    ownerWork = (u8 *)owner + 0x34;
    if (checkActorViewBounds(sprite, owner) == 1) {
        return;
    }
    applySpritePaletteVariant(obj, sprite);
    if (sub_08013558(sprite, owner, *(void **)((u8 *)owner + 0x28)) != 0)
        spawnContactEffectOnHit(obj, *(void **)((u8 *)owner + 0x28));
    uploadPendingSpriteGraphic(obj, *(void **)((u8 *)owner + 0x28));
    if (((*(u16 *)owner) & 1) && (*(u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj + 0x1A) != 2)) {
        updateActorWorldPosition(obj);
        *(u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj + 0x1B) = 0;
        {
            void **fnaddr = &sScriptStepCallbacks;
            sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 2, *fnaddr);
        }
    }
    if (updateObjectDisplayState(sprite, owner) == 0) {
        *(u32 *)((u8 *)obj + 0x14) = (u32)D_0866DAE4;
        *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) + 1;
        {
            u8 *stepBase;
            stepBase = (u8 *)((u32)(*(s16 *)((u8 *)obj + 0x22)) * 2 + (u32)obj);
            *(u8 *)(stepBase + 0x19) = *(u8 *)(stepBase + 0x19) + 1;
        }
        {
            s32 stepOffset = (s32)(s16)(*(s16 *)((u8 *)obj + 0x22)) * 2;
            u8 *stepData = (u8 *)obj;
            u8 stepByte;
            stepData += 0x18;
            stepData += stepOffset;
            stepByte = *stepData;
            sub_080C31E0(obj, *(void **)(*(u32 *)((u8 *)obj + 0x14) + (u32)(stepByte * 4)));
        }
        *(u16 *)((u8 *)obj + 0x22) = *(u16 *)((u8 *)obj + 0x22) - 1;
        if (*(u16 *)((u8 *)obj + 2) & 0x8000) {
            return;
        }
        stepAnimationTrack(sprite, ownerWork);
        moveObjectHorizontally(owner, 0x80000, 0x80000);
    }
    sub_0802B178(sprite, owner);
    sub_08013C8C(obj, sprite);
}
