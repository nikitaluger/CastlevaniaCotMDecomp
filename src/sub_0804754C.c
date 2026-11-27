/* Update this entity type: view-cull its sprite, resolve collisions with the
 * two nearby targets, run death/sound effects, advance its state script and
 * motion, then write camera-relative screen coordinates to the sprite. */
extern void applySpritePaletteVariant(void *, s32);
extern s32 checkActorViewBounds(s32, void *);
extern s32 sub_08014F14(s32, void *, void *, void *);
extern void spawnChildPair(void *, void *, void *, void *, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void updateActorWorldPosition(void *);
extern void sub_08005E80(s32);
extern s32 sub_0801576C(s32, void *, void *, void *, void *, void *);
extern void stepAnimationTrack(s32, void *);
extern void advanceMotion(void *, s32);
extern void sub_08047A30(s32, void *);
extern void sub_08013C8C(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);

void sub_0804754C(u8 *entity) {
    s32 sprite;          /* display object at entity+0x38 */
    u8 *motion;          /* physics/state object at entity+0x3C */
    u8 *animState;       /* motion+0x34: animation state */
    u8 *targetInfo;      /* motion+0x48: target descriptors */
    u8 *targetState;     /* motion+0x2C */
    s32 collisionResult;

    sprite = *(s32 *)(entity + 0x38);
    motion = *(u8 **)(entity + 0x3C);
    animState = motion + 0x34;
    targetInfo = motion + 0x48;

    if (checkActorViewBounds(sprite, motion) == 1) {
        *(u8 *)(*(u8 **)(targetInfo + 0x10) + 1) = 0;
        return;
    }
    *(u8 *)(*(u8 **)(targetInfo + 0x10) + 1) = 5;
    applySpritePaletteVariant(entity, sprite);
    collisionResult = sub_08014F14(sprite, motion, *(void **)(motion + 0x28), *(void **)(targetInfo + 0x10));
    targetState = motion + 0x2C;
    if (collisionResult != 0) {
        spawnChildPair(entity, *(void **)(motion + 0x28), *(void **)(targetInfo + 0x10), targetState, motion + 0x5C);
    }
    uploadPendingSpriteGraphic(entity, *(void **)(motion + 0x28));
    uploadPendingSpriteGraphic(entity, *(void **)(targetInfo + 0x10));
    if (*(u16 *)motion & 1) {
        u8 *frameData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        if (*(u8 *)(frameData + 0x1A) != 2) {
            u8 *frameEntry;
            s32 *scriptTable;
            updateActorWorldPosition(entity);
            sub_08005E80(0x8A);
            sub_08005E80(0x80);
            frameEntry = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(frameEntry + 0x1B) = 0;
            scriptTable = (s32 *)0x08671BDC;
            sub_080C31E8(entity + 0x18, entity + 0x22, 2, *scriptTable);
        }
    }
    if (sub_0801576C(sprite, motion, *(void **)(motion + 0x28), *(void **)(targetInfo + 0x10), targetState, targetInfo + 0x14) == 0) {
        u8 *frameEntry;
        s32 stateOffset;
        u8 *stateTable;
        u8 stateByte;
        void **stateTablePtr;
        void *handler;
        *(void **)(entity + 0x14) = (void *)0x0866E308;
        *(u16 *)(entity + 0x22) = (u16)(*(u16 *)(entity + 0x22) + 1);
        frameEntry = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        *(u8 *)(frameEntry + 0x19) = (u8)(*(u8 *)(frameEntry + 0x19) + 1);
        stateOffset = (*(s16 *)(entity + 0x22)) * 2;
        stateTable = entity + 0x18;
        stateByte = *(stateTable + stateOffset);
        stateTablePtr = *(void **)(entity + 0x14);
        handler = stateTablePtr[stateByte];
        sub_080C31E0(entity, handler);
        *(u16 *)(entity + 0x22) = (u16)(*(u16 *)(entity + 0x22) - 1);
        if ((*(u16 *)(entity + 2) & 0x8000) != 0) {
            goto end;
        }
        stepAnimationTrack(sprite, animState);
        advanceMotion(motion, 0);
        goto postUpdate;
    } else {
postUpdate:
        sub_08047A30(sprite, motion);
        sub_08013C8C(entity, sprite);
    }
end: ;
}
