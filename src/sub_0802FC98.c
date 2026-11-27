void stepAnimationTrack(void *, void *);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void updateActorWorldPosition(void *);
s32 updateObjectDisplayState(void *, void *);
void applySpritePaletteVariant(void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_08014090(s16);
s32 checkActorViewBounds(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, u32, u32);
struct FlagWord { u8 pad[0x6C]; u16 flags; };

/*
 * Updates an entity: runs its state and attack checks, dispatches the handler
 * for the current script step, and clears or sets flags on its linked objects
 * according to the result.
 */
void sub_0802FC98(void *entity)
{
    void *sprite;
    void *motion;
    void *status;
    u8 *motionEx;
    u32 *scriptFn;

    sprite = *(void **)((u8 *)entity + 0x38);
    motion = *(void **)((u8 *)entity + 0x3C);
    status = (u8 *)motion + 0x34;
    motionEx = (u8 *)motion + 0x48;

    if (checkActorViewBounds(sprite, motion) == 1)
        return;

    applySpritePaletteVariant(entity, sprite);
    if (sub_08013558(sprite, motion, *(void **)((u8 *)motion + 0x28)) != 0)
        spawnContactEffectOnHit(entity, *(void **)((u8 *)motion + 0x28));
    uploadPendingSpriteGraphic(entity, *(void **)((u8 *)motion + 0x28));

    if (*(u16 *)motion & 1)
    {
        if (*(u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity + 0x1A) != 4)
        {
            updateActorWorldPosition(entity);
            *(u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity + 0x1B) = 0;
            scriptFn = (u32 *)0x08671BDC;
            sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 4, *scriptFn);
        }
    }

    if (updateObjectDisplayState(sprite, motion) == 0)
    {
        u8 *stepData;
        u8 *stepTable;
        s32 stepOffset;
        u8 stepByte;
        u32 handlerTable;
        s32 handler;

        ((struct FlagWord *)*(u8 **)motionEx)->flags &= 0xFFDF;
        ((struct FlagWord *)*(u8 **)(motionEx + 4))->flags &= 0xFFDF;

        *(u32 *)((u8 *)entity + 0x14) = 0x0866DC10;
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) + 1;
        stepData = (u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
        *(u8 *)(stepData + 0x19) = *(u8 *)(stepData + 0x19) + 1;
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)entity + 0x22)) * 2;
        stepTable = (u8 *)entity;
        stepTable += 0x18;
        stepTable += stepOffset;
        stepByte = *stepTable;
        handlerTable = *(u32 *)((u8 *)entity + 0x14);
        handler = *(s32 *)((u32)(stepByte * 4) + handlerTable);
        sub_080C31E0((s32)entity, handler);
        *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;

        if (*(u16 *)((u8 *)entity + 2) & 0x8000)
            return;
        stepAnimationTrack(sprite, status);
    }
    else
    {
        if (sub_08014090(*(s16 *)((u8 *)motion + 0x1C)) == 0)
        {
            ((struct FlagWord *)*(u8 **)motionEx)->flags |= 0x20;
            ((struct FlagWord *)*(u8 **)(motionEx + 4))->flags |= 0x20;
        }
    }

    sub_08013C8C(entity, sprite);
}
