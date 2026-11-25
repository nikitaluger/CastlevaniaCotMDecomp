extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_08016664(u8 *, s32);
extern s32 sub_0800583C(s32);
extern s32 sub_08005820(s32);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

struct SpriteDef {
    u8 _0; u8 kind; u8 subkind; u8 state;
    u16 tile; u16 f6; u16 f8; u16 fA; u16 fC; u16 mode;
    u32 sprite; u16 zero;
};
struct SpawnedObject {
    u8 _0[8];
    s32 x; s32 y;
    u32 f10; u32 f14; u32 frameIndex;
    s16 kind;
    u8 _1E[4];
    s16 tableSlot;
    u32 callback;
    struct SpriteDef *spriteDef;
};
struct ScriptRef { s16 value0; s16 value1; };
struct ScriptRefHolder { u8 _0[4]; struct ScriptRef *ref; };
struct ScriptThread {
    u8 _0[2]; u16 flags;
    u8 _4[0x22-4];
    s16 index;
    u8 _24[0x38-0x24];
    u8 *object;
    struct SpawnedObject *state;
    u8 _40[0x4C-0x40];
    s16 f4C;
    u8 _4E[6];
    s16 f54;
    u8 _56[0xAC-0x56];
    struct ScriptRefHolder *refHolder;
};
struct GlobalStateA { u8 _0[0x18A8]; u8 mapIndex; u8 _18A9[0x19]; u16 gfxFlag; };
extern struct GlobalStateA D_02025FF0;
struct GlobalStateB { u8 _0[0x1278]; u32 cameraX; u32 cameraY; };
extern struct GlobalStateB D_02021E90;
struct KindTable { u16 tile; s16 frame; u16 mode; u8 _6[0x14-6]; };
extern struct KindTable D_080CB2B8[];
extern u16 D_080CFE34[];
extern u8 D_080CD400[];
extern s32 D_08671BB0;

/* Script command: spawn a sprite/effect object from the thread's script ref,
 * configure its animation and sprite attributes from the kind tables, then
 * idle the thread and advance the menu command state. */
void sub_0805BF14(struct ScriptThread *thread) {
    u8 *sprite;
    struct SpawnedObject *work;
    u8 *anim;
    struct SpriteDef *gfx;
    s32 tableSlot;
    u32 attrs;
    u8 *gfxBase;
    u8 *extra;
    u8 *kindTable;
    s32 kind;
    u32 zero;
    struct ScriptRefHolder *refHolder;
    u8 **extraSlot;

    refHolder = thread->refHolder;
    sprite = sub_0800355C();
    if (sprite == NULL) goto fail0;
    goto ok0;
fail0:
    _call_via_r1((u8 *)thread, *(s32 *)((u8 *)thread + 0x24));
    return;
ok0:
    thread->object = sprite;
    sub_0800168C((u8 *)thread, 0, 0x84, 0);
    work = thread->state;
    if (work == NULL) goto fail;
    anim = (u8 *)work + 0x34;
    work->callback = *(u32 *)((u8 *)thread + 0x24);
    *(u32 *)((u8 *)thread + 0x24) = 0x0805C2F5;
    zero = 0;
    work->kind = 0x34;
    kindTable = (u8 *)D_080CB2B8;
    kind = work->kind;
    work->frameIndex = ((struct KindTable *)kindTable)[kind].frame;
    work->x = refHolder->ref->value0 << 16;
    work->y = refHolder->ref->value1 << 16;
    tableSlot = sub_08013C2C(0x34);
    work->tableSlot = tableSlot;
    if ((s32)(tableSlot << 16) < 0) goto fail;
    sub_0801131C(sprite, anim, (s32)D_080CD400 + work->kind * 0xC);
    gfx = (struct SpriteDef *)sub_08016190();
    work->spriteDef = gfx;
    if (gfx == NULL) goto fail;
    goto fields;
fail:
    _call_via_r1((u8 *)thread, *(s32 *)((u8 *)thread + 0x24));
    return;
fields:
    work->spriteDef->kind = 0;
    work->spriteDef->subkind = 8;
    work->spriteDef->state = 1;
    work->spriteDef->tile = ((struct KindTable *)kindTable)[work->kind].tile;
    work->spriteDef->f6 = D_080CFE34[0];
    work->spriteDef->f8 = D_080CFE34[1];
    work->spriteDef->fA = D_080CFE34[2];
    work->spriteDef->fC = D_080CFE34[3];
    work->spriteDef->mode = ((struct KindTable *)kindTable)[work->kind].mode;
    work->spriteDef->sprite = (u32)sprite;
    work->spriteDef->zero = zero;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | D_02025FF0.gfxFlag;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    gfxBase = (u8 *)&D_02021E90;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(gfxBase + k + ((D_02025FF0.mapIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(gfxBase + k + ((D_02025FF0.mapIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    extra = (u8 *)work + 0x48;
    *(u32 *)extra = work->x;
    ((u32 *)extra)[1] = work->y;
    extraSlot = &extra;
    ((u32 *)(*extraSlot))[2] = ((u32 *)extra)[0] + sub_0800583C(0x200000);
    ((u32 *)extra)[3] = ((u32 *)extra)[1] + sub_0800583C(0x200000);
    extra += 0x10;
    *(u32 *)((u8 *)work + 0x58) = zero;
    ((u32 *)extra)[1] = sub_08005820(0x10000);
    ((u32 *)extra)[2] = zero;
    ((u32 *)extra)[3] = 0x4000;
    ((u32 *)extra)[4] = 0x80;
    ((u32 *)extra)[5] = 0x80;
    sub_08011368(sprite, anim, 0, 1);
    sub_08016664((u8 *)thread, 0);
    thread->flags |= 0x1000;
    *(u8 *)((u8 *)thread + 2 * thread->index + 0x19) = 0;
    {
        s32 *st = (s32 *)0x08671BB0;
        extra = (u8 *)thread + 0x18;
        _call_via_r2(extra, (u8 *)thread + 0x22, *st);
    }
    {
        u32 idx2 = 2 * (u32)thread->index;
        u8 *stateBytePtr;
        idx2 += (u32)thread;
        stateBytePtr = (u8 *)idx2;
        *(u8 *)(stateBytePtr + 0x19) = *(u8 *)(stateBytePtr + 0x19) + 1;
    }
    extra += thread->index * 2;
    _call_via_r1((u8 *)thread, *(s32 *)(*(u8 **)((u8 *)thread + 0x14) + *(u8 *)extra * 4));
}
