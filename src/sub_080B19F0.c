extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s16 findKindIndex(void);
extern void sub_080B2FD4(void *, void *, s32, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void releaseActorEffectSubObject(void);
extern s32 gScriptStepCallbackTable;

struct S_02025FF0 {
    u8 _0x000[0x18C2];
    u16 w;
};
extern struct S_02025FF0 gMainWorkspace;

/* Set up a companion sprite for this object, initialise its script state, then
 * dispatch the next script step; on failure use the object's default handler. */
void sub_080B19F0(void *obj)
{
    void *sprite;
    void *scriptState;
    void *stateArg;

    sprite = allocSpriteObject();
    if (sprite == 0)
        goto fallback;

    *(void **)((u8 *)obj + 0x38) = sprite;
    allocWorkSlot(obj, 0, 0x48, 0);

    if (*(void **)((u8 *)obj + 0x3C) == 0)
        goto fallback;

    *(u32 *)((u8 *)sprite + 0x1C) = 0x80000009;
    scriptState = *(void * volatile *)((u8 *)obj + 0x3C);
    stateArg = (u8 *)scriptState + 0x34;
    installUpdateHandler(obj, scriptState, releaseActorEffectSubObject);
    *(u16 *)((u8 *)scriptState + 0x1C) = 0x65;
    *(s16 *)((u8 *)scriptState + 0x22) = findKindIndex();
    if (*(s16 *)((u8 *)scriptState + 0x22) >= 0)
        goto ready;

fallback:
    sub_080C31E0(obj, *(void **)((u8 *)obj + 0x24));
    return;

ready:
    *(u16 *)((u8 *)sprite + 0x00) |= gMainWorkspace.w;
    sub_080B2FD4(sprite, stateArg, 0x90, 2);
    setObjectAnimation(sprite, stateArg, 0x10, 0);

    *(u16 *)((u8 *)sprite + 0x02) |= 0x0400;
    *(u16 *)((u8 *)obj + 0x02) |= 0x1000;

    *(u8 *)((u8 *)obj + *(s16 *)((u8 *)obj + 0x22) * 2 + 0x19) = 0;

    {
        s32 *handlerTablePtr = &gScriptStepCallbackTable;
        u8 *stepTable = (u8 *)obj + 0x18;
        s16 stepIndex;

        sub_080C31E4(stepTable, (u8 *)obj + 0x22, *handlerTablePtr);

        stepIndex = *(s16 *)((u8 *)obj + 0x22);
        *(u8 *)((u8 *)obj + stepIndex * 2 + 0x19) += 1;

        stepIndex = *(s16 *)((u8 *)obj + 0x22);
        stepTable += stepIndex * 2;
        sub_080C31E0(obj, *(void **)(*(u8 **)((u8 *)obj + 0x14) + *stepTable * 4));
    }
}
