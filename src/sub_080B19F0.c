extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s16 sub_08013C2C(void);
extern void sub_080B2FD4(void *, void *, s32, s32);
extern void sub_080114DC(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097D90(void);
extern s32 D_08671BB0;

struct S_02025FF0 {
    u8 _0x000[0x18C2];
    u16 w;
};
extern struct S_02025FF0 D_02025FF0;

/* Set up a companion sprite for this object, initialise its script state, then
 * dispatch the next script step; on failure use the object's default handler. */
void sub_080B19F0(void *obj)
{
    void *sprite;
    void *scriptState;
    void *stateArg;

    sprite = sub_0800355C();
    if (sprite == 0)
        goto fallback;

    *(void **)((u8 *)obj + 0x38) = sprite;
    sub_0800168C(obj, 0, 0x48, 0);

    if (*(void **)((u8 *)obj + 0x3C) == 0)
        goto fallback;

    *(u32 *)((u8 *)sprite + 0x1C) = 0x80000009;
    scriptState = *(void * volatile *)((u8 *)obj + 0x3C);
    stateArg = (u8 *)scriptState + 0x34;
    sub_08014288(obj, scriptState, sub_08097D90);
    *(u16 *)((u8 *)scriptState + 0x1C) = 0x65;
    *(s16 *)((u8 *)scriptState + 0x22) = sub_08013C2C();
    if (*(s16 *)((u8 *)scriptState + 0x22) >= 0)
        goto ready;

fallback:
    sub_080C31E0(obj, *(void **)((u8 *)obj + 0x24));
    return;

ready:
    *(u16 *)((u8 *)sprite + 0x00) |= D_02025FF0.w;
    sub_080B2FD4(sprite, stateArg, 0x90, 2);
    sub_080114DC(sprite, stateArg, 0x10, 0);

    *(u16 *)((u8 *)sprite + 0x02) |= 0x0400;
    *(u16 *)((u8 *)obj + 0x02) |= 0x1000;

    *(u8 *)((u8 *)obj + *(s16 *)((u8 *)obj + 0x22) * 2 + 0x19) = 0;

    {
        s32 *handlerTablePtr = &D_08671BB0;
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
