/* Per-frame update for the scripted multi-part object: refresh the owner
 * sprite's OAM attributes and render parts, upload pending graphics, then
 * either finish (final position, cue, timer callback and saved handler) or
 * advance the script step and dispatch its handler. */
void sub_08097F88(s32, void *, void *, void *); /* configure one render part */
void uploadPendingSpriteGraphic(void *, void *);
void updateActorWorldPosition(void *);
s32 sub_08007E24(s32); /* queue a sound effect */
s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);
void sub_080A2E98(void *, void *, void *);
void sub_08098338(s32, void *);
extern u32 gMultiPartStateHandlers[];

void updateScriptedMultiPartObject(u8 *entity) {
    void *work;
    void *sprite;
    u8 zero;
    u8 *gfxInit;
    u16 spriteAttrs;
    s32 handler;

    sprite = *(void **)(entity + 0x38);
    work = *(void **)(entity + 0x3C);
    gfxInit = (u8 *)work + 0x34;
    spriteAttrs = (*(u16 *)sprite & 0x0FFF) | ((u16)((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    zero = 0;
    *(u16 *)sprite = spriteAttrs;
    sub_08097F88(0, sprite, work, *(void **)((u8 *)work + 0x28));
    sub_08097F88(2, sprite, work, *(void **)((u8 *)work + 0x48));
    uploadPendingSpriteGraphic(entity, *(void **)((u8 *)work + 0x28));
    uploadPendingSpriteGraphic(entity, *(void **)((u8 *)work + 0x48));

    if (*(u16 *)work & 1) {
        u32 *timerCallback;
        u8 *stepStream;
        u8 stateId;
        s32 stepOffset;
        updateActorWorldPosition(entity);
        sub_08007E24(0xB5);
        *(u8 *)(*(u8 **)((u8 *)work + 0x28) + 1) = zero;
        *(u8 *)(*(u8 **)((u8 *)work + 0x48) + 1) = zero;
        {
            u8 *stepData;
            stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(stepData + 0x19) = zero;
        }
        timerCallback = (u32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
        stepStream = entity + 0x18;
        sub_080C31E4(stepStream, entity + 0x22, *timerCallback);
        {
            u8 *stepData;
            stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(stepData + 0x19) = *(u8 *)(stepData + 0x19) + 1;
        }
        stepOffset = (s32)(s16)(*(s16 *)(entity + 0x22)) * 2;
        stepStream += stepOffset;
        stateId = *stepStream;
        handler = *(s32 *)((u32)(stateId * 4) + *(u32 *)(entity + 0x14));
        sub_080C31E0((s32)entity, handler);
        return;
    }

    if (updateObjectDisplayState(sprite, work) == 0) {
        u8 *stepStream;
        u8 stateId;
        s32 stepOffset;
        *(u32 *)(entity + 0x14) = (u32)gMultiPartStateHandlers;
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
        {
            u8 *stepData;
            stepData = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
            *(u8 *)(stepData + 0x19) = *(u8 *)(stepData + 0x19) + 1;
        }
        stepOffset = (s32)(s16)(*(s16 *)(entity + 0x22)) * 2;
        stepStream = entity;
        stepStream += 0x18;
        stepStream += stepOffset;
        stateId = *stepStream;
        sub_080C31E0((s32)entity, *(s32 *)((u32)(stateId * 4) + *(u32 *)(entity + 0x14)));
        *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    }
    sub_080A2E98(gfxInit, *(void **)((u8 *)work + 0x28), *(void **)((u8 *)work + 0x48));
    sub_08098338(1, sprite);
    sub_08013C8C(entity, sprite);
}
