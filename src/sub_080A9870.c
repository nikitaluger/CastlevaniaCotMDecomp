/* Spawn a companion sprite, seed the entity's script state from its position,
 * then dispatch the current script action from its handler table. */
extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s32 sub_08013C2C(s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);
extern s32 D_08671BB0;
struct S_02025FF0 { u8 _[0x18C2]; u16 w; };
extern struct S_02025FF0 D_02025FF0;

void sub_080A9870(void *entity) {
    void *sprite;
    void *scriptState;
    s32 scriptIndex;

    sprite = sub_0800355C();
    if (sprite == 0) goto fail;
    *(void **)((u8 *)entity + 0x38) = sprite;
    sub_0800168C(entity, 0, 0x48, 0);
    if (*(void **)((u8 *)entity + 0x3C) == 0) goto fail;

    *(u32 *)((u8 *)sprite + 0x1C) = 0x80000009;
    scriptState = *(void * volatile *)((u8 *)entity + 0x3C);
    sub_08014288(entity, scriptState, sub_08097DC8);
    *(u16 *)((u8 *)scriptState + 0x1C) = 0x5F;
    *(u32 *)((u8 *)scriptState + 0x08) = *(u32 *)((u8 *)entity + 0x4C);
    *(u32 *)((u8 *)scriptState + 0x0C) = *(u32 *)((u8 *)entity + 0x5C);
    scriptIndex = sub_08013C2C(0x5F);
    *(s16 *)((u8 *)scriptState + 0x22) = scriptIndex;
    if ((scriptIndex << 16) >= 0) goto ok;

fail:
    sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
    return;

ok:
    *(u16 *)sprite |= D_02025FF0.w;
    *(u32 *)((u8 *)sprite + 0x24) = *(u32 *)((u8 *)entity + 0x6C);
    *(u16 *)((u8 *)entity + 2) |= 0x1000;
    *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = 0;
    {
        s32 *handlerTablePtr = &D_08671BB0;
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
