/* Spawn a companion sprite, seed the entity's script state from its position,
 * then dispatch the current script action from its handler table. */
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);
extern s32 gMainObjTimerCallback;
struct S_02025FF0 { u8 _[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;

void sub_080A9870(void *entity) {
    void *sprite;
    void *scriptState;
    s32 scriptIndex;

    sprite = allocSpriteObject();
    if (sprite == 0) goto fail;
    *(void **)((u8 *)entity + 0x38) = sprite;
    allocWorkSlot(entity, 0, 0x48, 0);
    if (*(void **)((u8 *)entity + 0x3C) == 0) goto fail;

    *(u32 *)((u8 *)sprite + 0x1C) = 0x80000009;
    scriptState = *(void * volatile *)((u8 *)entity + 0x3C);
    installUpdateHandler(entity, scriptState, sub_08097DC8);
    *(u16 *)((u8 *)scriptState + 0x1C) = 0x5F;
    *(u32 *)((u8 *)scriptState + 0x08) = *(u32 *)((u8 *)entity + 0x4C);
    *(u32 *)((u8 *)scriptState + 0x0C) = *(u32 *)((u8 *)entity + 0x5C);
    scriptIndex = findKindIndex(0x5F);
    *(s16 *)((u8 *)scriptState + 0x22) = scriptIndex;
    if ((scriptIndex << 16) >= 0) goto ok;

fail:
    sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
    return;

ok:
    *(u16 *)sprite |= gMainWorkspace.w;
    *(u32 *)((u8 *)sprite + 0x24) = *(u32 *)((u8 *)entity + 0x6C);
    *(u16 *)((u8 *)entity + 2) |= 0x1000;
    *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = 0;
    {
        s32 *handlerTablePtr = &gMainObjTimerCallback;
        u8 *stepTable = (u8 *)entity + 0x18;
        s16 stepIndex;
        sub_080C31E4(stepTable, (u8 *)entity + 0x22, *handlerTablePtr);
        stepIndex = *(s16 *)((u8 *)entity + 0x22);
        *(u8 *)((u8 *)entity + stepIndex * 2 + 0x19) += 1;
        stepIndex = *(s16 *)((u8 *)entity + 0x22);
        stepTable += stepIndex * 2;
        sub_080C31E0(entity, *(void **)(*(u8 **)((u8 *)entity + 0x14) + *stepTable * 4));
    }
}
