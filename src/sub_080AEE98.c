extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s16 findKindIndex(s32);
extern void initSpriteFromTemplate(void *, void *, s32, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void releaseActorEffectSubObject(void);
extern s32 gScriptStepCallbackTable;

struct S_02025FF0 {
    u8 _0x000[0x18C2];
    u16 spriteFlags;
};
extern struct S_02025FF0 gMainWorkspace;

/* Spawns an entity's child sprite, copies its motion and position, then
 * advances the entity's step script and dispatches the next handler. */
void sub_080AEE98(void *entity)
{
    void *sprite;
    void *motion;
    void *status;

    sprite = allocSpriteObject();
    if (sprite == 0)
        goto fail;

    *(void **)((u8 *)entity + 0x38) = sprite;
    allocWorkSlot(entity, 0, 0x48, 0);

    if (*(void **)((u8 *)entity + 0x3C) == 0)
        goto fail;

    *(u32 *)((u8 *)sprite + 0x1C) = 0xB4;
    motion = *(void * volatile *)((u8 *)entity + 0x3C);
    status = (u8 *)motion + 0x34;
    installUpdateHandler(entity, motion, releaseActorEffectSubObject);
    *(u16 *)((u8 *)motion + 0x1C) = 0x64;
    *(u32 *)((u8 *)motion + 0x08) = *(u32 *)((u8 *)entity + 0x4C);
    *(u32 *)((u8 *)motion + 0x0C) = *(u32 *)((u8 *)entity + 0x5C);
    *(s16 *)((u8 *)motion + 0x22) = findKindIndex(0x64);
    if (*(s16 *)((u8 *)motion + 0x22) >= 0)
        goto ok;

fail:
    sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
    return;

ok:
    *(u16 *)((u8 *)sprite + 0x00) |= gMainWorkspace.spriteFlags;
    initSpriteFromTemplate(sprite, status, 0x9E, 6);
    setObjectAnimation(sprite, status, 0x4B, 1);

    *(u8 *)((u8 *)entity + 0x6C) = 0x10;
    *(u16 *)((u8 *)entity + 0x02) |= 0x1000;

    *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = 0;

    {
        s32 *scriptTable = &gScriptStepCallbackTable;
        u8 *stepBase = (u8 *)entity + 0x18;
        s16 stepIndex;

        sub_080C31E4(stepBase, (u8 *)entity + 0x22, *scriptTable);

        stepIndex = *(s16 *)((u8 *)entity + 0x22);
        *(u8 *)((u8 *)entity + stepIndex * 2 + 0x19) += 1;

        stepIndex = *(s16 *)((u8 *)entity + 0x22);
        stepBase += stepIndex * 2;
        sub_080C31E0(entity, *(void **)(*(u8 **)((u8 *)entity + 0x14) + *stepBase * 4));
    }
}
