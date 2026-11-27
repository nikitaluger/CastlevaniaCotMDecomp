extern void sub_08005E80(s32);
extern void stepAnimationTrack(s32, void *);
extern void moveObjectHorizontally(void *, s32, s32);
extern s32 sub_08013558(s32, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void updateActorWorldPosition(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void applySpritePaletteVariant(void *, s32);
extern void sub_08013C8C(void *, void *);
extern s32 checkActorViewBounds(s32, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *gScriptEventCallbacks;

/*
 * Entity AI update: after the state/contact checks, plays the contact sound and
 * launches a script step on a hit, then dispatches the handler for the current
 * script step and finally closes out the entity's update.
 */
void sub_0804B030(u8 *entity) {
    s32 sprite = *(s32 *)(entity + 0x38);
    u8 *motion = *(u8 **)(entity + 0x3C);
    u8 *status = motion + 0x34;

    if (checkActorViewBounds(sprite, motion) == 1) {
        u8 *stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        u8 stepKind = (u8)(*(u8 *)(stepData + 0x1A) - 2);
        if (stepKind > 1) return;
    }
    applySpritePaletteVariant(entity, sprite);
    if (sub_08013558(sprite, motion, *(void **)(motion + 0x28)) != 0) {
        spawnContactEffectOnHit(entity, *(void **)(motion + 0x28));
    }
    uploadPendingSpriteGraphic(entity, *(void **)(motion + 0x28));
    if (*(u16 *)motion & 1) {
        u8 *stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        if (*(u8 *)(stepData + 0x1A) != 4) {
            updateActorWorldPosition(entity);
            sub_08005E80(0x86);
            {
                u8 *stepData2 = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
                u8 zero = 0;
                *(u8 *)(stepData2 + 0x1B) = zero;
                { void **scriptFn = &gScriptEventCallbacks;
                  sub_080C31E8(entity + 0x18, entity + 0x22, 4, *scriptFn); }
            }
        }
    }
    if (updateObjectDisplayState(sprite, motion) == 0) {
        *(void **)(entity + 0x14) = (void *)0x0866E450;
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
        {
            u8 *stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            stepData[0x19] = (u8)(stepData[0x19] + 1);
        }
        {
            s32 stepOffset = (*(s16 *)(entity + 0x22)) * 2;
            u8 *stepTable = entity + 0x18;
            u8 stepByte = *(stepTable + stepOffset);
            void **handlerTable = *(void **)(entity + 0x14);
            void *handler = handlerTable[stepByte];
            sub_080C31E0(entity, handler);
        }
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
        if (*(u16 *)(entity + 0x02) & 0x8000) {
            return;
        }
        stepAnimationTrack(sprite, status);
        moveObjectHorizontally(motion, 0x180000, 0x180000);
    }
    sub_08013C8C(entity, sprite);
}
