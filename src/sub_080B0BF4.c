extern void updateActorWorldPosition(void *);
extern s32 updateObjectDisplayState(void *, void *);
extern void sub_08013C8C(void *, void *);
extern void uploadPendingSpriteGraphic(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08007E24(s32);
extern void sub_08097F88(s32, u16 *, u8 *, void *);
extern void updateSceneObjectFromActor(u16 *, u8 *, s32);
extern void sub_08098338(s32, u16 *);

/* Per-frame update for an entity: recompute sprite graphics attributes from
 * its state, refresh its child objects, then either finish the current action
 * or advance the script, finally updating world position and state flags. */
void sub_080B0BF4(void *arg0) {
    u8 *sprite = *(u8 **)((u8 *)arg0 + 0x38);
    u8 *actor = *(u8 **)((u8 *)arg0 + 0x3C);
    s32 param4C = *(s32 *)((u8 *)arg0 + 0x4C);
    u8 *entity = (u8 *)arg0;
    u8 zero;
    u32 gfxAttr;

    gfxAttr = (*(u16 *)sprite & 0x0FFF) | ((*(u16 *)(actor + 0x22) + 8) << 12);
    zero = 0;
    *(u16 *)sprite = gfxAttr;

    sub_08097F88(3, (u16 *)sprite, actor, *(void **)(actor + 0x28));
    uploadPendingSpriteGraphic(entity, *(u32 *)(actor + 0x28));
    uploadPendingSpriteGraphic(entity, *(u32 *)(actor + 0x48));

    if (*(u16 *)actor & 1) {
        s32 ctrlOffset;
        u8 *ctrlPtr;
        s32 *scriptData;
        u8 stepByte;

        updateActorWorldPosition(entity);
        sub_08007E24(0xB9);
        *(u8 *)(*(u32 *)(actor + 0x28) + 1) = zero;
        *(u8 *)(*(u32 *)(actor + 0x48) + 1) = zero;
        ctrlOffset = *(s16 *)(entity + 0x22) * 2;
        *(u8 *)((u32)ctrlOffset + (u32)entity + 0x19) = zero;
        scriptData = (s32 *)0x08671BB0;
        ctrlPtr = entity;
        ctrlPtr += 0x18;
        sub_080C31E4(ctrlPtr, entity + 0x22, *scriptData);
        ctrlOffset = *(s16 *)(entity + 0x22) * 2;
        *(u8 *)((u32)ctrlOffset + (u32)entity + 0x19) = *(u8 *)((u32)ctrlOffset + (u32)entity + 0x19) + 1;
        ctrlOffset = *(s16 *)(entity + 0x22) * 2;
        ctrlPtr += ctrlOffset;
        stepByte = *ctrlPtr;
        sub_080C31E0(entity, *(void **)(stepByte * 4 + *(u32 *)(entity + 0x14)));
        return;
    }

    if (updateObjectDisplayState(sprite, actor) == 0) {
        s32 ctrlOffset;
        u8 *ctrlPtr;
        u8 stepByte;

        *(u32 *)(entity + 0x14) = 0x0867026C;
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
        ctrlOffset = *(s16 *)(entity + 0x22) * 2;
        *(u8 *)((u32)ctrlOffset + (u32)entity + 0x19) = *(u8 *)((u32)ctrlOffset + (u32)entity + 0x19) + 1;
        ctrlOffset = *(s16 *)(entity + 0x22) * 2;
        ctrlPtr = entity;
        ctrlPtr += 0x18;
        ctrlPtr += ctrlOffset;
        stepByte = *ctrlPtr;
        sub_080C31E0(entity, *(void **)(stepByte * 4 + *(u32 *)(entity + 0x14)));
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    }
    updateSceneObjectFromActor((u16 *)sprite, actor, param4C);
    sub_08098338(0x30, (u16 *)sprite);
    sub_08013C8C(entity, sprite);
}
