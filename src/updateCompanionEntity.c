extern void applySpritePaletteVariant(void *, s32);
extern s32 checkActorViewBounds(s32, void *);
extern s32 detectActorHit(s32, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void updateActorWorldPosition(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void stepAnimationTrack(s32, void *);
extern void sub_08011EE8(void *, s32, s32);
extern void syncSpriteToWorldPosition(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *gScriptEventCallbacks;
struct SubObjectFlags { u8 unused; u8 flags; };

/* Companion entity update: refresh its sprite and hit handling, dispatch the
 * current pose handler from the companion pose table, fire the scripted attack
 * when its flag is set, and run the off-screen and cleanup paths. */
void updateCompanionEntity(u8 *companion) {
    s32 owner = *(s32 *)(companion + 0x38);
    u8 *entity = *(u8 **)(companion + 0x3C);
    u8 *animTrack = entity + 0x34;
    u8 *timers = entity + 0x48;
    u8 *subObject = *(u8 **)(timers + 0x14);
    u8 zero = 0;

    subObject[1] = zero;
    if (checkActorViewBounds(owner, entity) == 1) return;

    applySpritePaletteVariant(companion, owner);
    if (detectActorHit(owner, entity, *(void **)(entity + 0x28)) != 0) {
        spawnContactEffectOnHit(companion, *(void **)(entity + 0x28));
    }
    uploadPendingSpriteGraphic(companion, *(void **)(entity + 0x28));
    uploadPendingSpriteGraphic(companion, *(void **)(timers + 0x14));
    if (*(u16 *)entity & 1) {
        u8 *poseSlot = (u8 *)((u32)(*(s16 *)(companion + 0x22)) * 2 + (u32)companion);
        if (*(u8 *)(poseSlot + 0x1A) != 2) {
            updateActorWorldPosition(companion);
            {
                u8 *poseSlot = (u8 *)((u32)(*(s16 *)(companion + 0x22)) * 2 + (u32)companion);
                *(u8 *)(poseSlot + 0x1B) = zero;
                { void **attackCallback = &gScriptEventCallbacks;
                  sub_080C31E8(companion + 0x18, companion + 0x22, 2, *attackCallback); }
            }
        }
    }
    if (updateObjectDisplayState(owner, entity) != 0) goto cdc;
    *(u32 *)(companion + 0x14) = (u32)0x0866DC4C;
    *(u16 *)(companion + 0x22) = (u16)(*(u16 *)(companion + 0x22) + 1);
    {
        u8 *poseSlot = (u8 *)((u32)(*(s16 *)(companion + 0x22)) * 2 + (u32)companion);
        poseSlot[0x19] = (u8)(poseSlot[0x19] + 1);
    }
    {
        s32 handlerOffset = (*(s16 *)(companion + 0x22)) * 2;
        u8 *poseBase = companion + 0x18;
        u8 handlerIndex = *(poseBase + handlerOffset);
        void **poseTable = *(void **)(companion + 0x14);
        void *handler = poseTable[handlerIndex];
        sub_080C31E0(companion, handler);
    }
    *(u16 *)(companion + 0x22) = (u16)(*(u16 *)(companion + 0x22) - 1);
    if ((*(u16 *)(companion + 2) & 0x8000) != 0) goto done;
    stepAnimationTrack(owner, animTrack);
    sub_08011EE8(entity, 0x16C1, 0);
cdc:
    if ((*(u16 *)entity & 0xC) == 0 && *(u16 *)(owner + 0x28) == 0x17) {
        struct SubObjectFlags *subObjectFlags = (struct SubObjectFlags *)*(u8 **)(timers + 0x14);
        subObjectFlags->flags |= 1;
    }
    syncSpriteToWorldPosition(companion, owner);
done:
    ;
}
