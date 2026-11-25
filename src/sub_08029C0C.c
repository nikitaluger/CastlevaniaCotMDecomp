extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_08014668(u8 *, s32);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);
extern void sub_0802A030(void);

struct EffectGfx {
    u8 unk0;
    u8 type;
    u8 layer;
    u8 priority;
    u16 gfxIndex;
    u16 anim0, anim1, anim2, anim3;
    u16 palette;
    u32 object;
    u16 tail;
};
struct OwnerEffect {
    u8 unk0[8];
    s32 worldX;
    s32 worldY;
    u32 radiusA;
    u32 radiusB;
    u32 state;
    s16 kind;
    u8 unk1E[4];
    s16 slot;
    u32 updateCb;
    struct EffectGfx *gfx;
    u8 unk2C[0x1C];
    u16 timer;
    u16 timerMax;
};
struct MainObj {
    u8 unk0[2];
    u16 flags;
    u8 unk4[0x22-4];
    s16 index;
    u8 unk24[0x38-0x24];
    u8 *object;
    struct OwnerEffect *effect;
    u8 unk40[0x4C-0x40];
    s16 x;
    u8 unk4E[6];
    s16 y;
    u8 unk56[0x6C-0x56];
    u32 tablePtr;
};
struct GameState { u8 unk0[0x18A8]; u8 scrollIndex; u8 unk18A9[0x19]; u16 renderFlags; };
extern struct GameState D_02025FF0;
struct ScrollTable { u8 unk0[0x1278]; u32 cameraX; u32 cameraY; };
extern struct ScrollTable D_02021E90;
struct EffectDef { u8 unk0[4]; u16 gfxIndex; u16 palette; u8 unk8[0x20]; };
extern struct EffectDef D_080CBDD0[];
extern u16 D_080CE96C[];
extern u8 D_080CD400[];

/* Spawn an effect for an object: allocate its sprite and work block, set up the
 * single render part, place it in world/screen space and schedule its update. */
void sub_08029C0C(struct MainObj *arg0) {
    u8 *sprite;
    struct OwnerEffect *effect;
    u8 *animState;
    struct EffectGfx *part;
    s32 kindIndex;
    u32 gfxFlags;
    u8 *scrollTable;
    s32 *scriptOps;
    s32 *distanceFn;
    u16 *timerPtr;

    sprite = sub_0800355C();
    if (sprite == NULL) goto fail0;
    goto ok0;
fail0:
    _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
    return;
ok0:
    arg0->object = sprite;
    sub_0800168C((u8 *)arg0, 0, 0x4C, 0);
    effect = arg0->effect;
    if (effect == NULL) goto fail;
    animState = (u8 *)effect + 0x34;
    effect->updateCb = *(u32 *)((u8 *)arg0 + 0x24);
    *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_0802A030 + 1;
    effect->kind = 0x2C;
    effect->state = 1;
    effect->worldX = arg0->x << 16;
    effect->worldY = arg0->y << 16;
    kindIndex = sub_08013C2C(0x2C);
    effect->slot = kindIndex;
    if ((s32)(kindIndex << 16) < 0) goto fail;
    sub_0801131C(sprite, animState, (s32)D_080CD400 + effect->kind * 0xC);
    part = sub_08016190();
    effect->gfx = part;
    if (part == NULL) goto fail;
    goto fields;
fail:
    _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
    return;
fields:
    effect->gfx->type = 0;
    effect->gfx->layer = 8;
    effect->gfx->priority = 1;
    effect->gfx->gfxIndex = D_080CBDD0[effect->kind].gfxIndex;
    effect->gfx->anim0 = D_080CE96C[0];
    effect->gfx->anim1 = D_080CE96C[1];
    effect->gfx->anim2 = D_080CE96C[2];
    effect->gfx->anim3 = D_080CE96C[3];
    effect->gfx->palette = D_080CBDD0[effect->kind].palette;
    effect->gfx->object = (u32)sprite;
    effect->gfx->tail = 0;
    gfxFlags = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)effect + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)effect + 0x22) + 8) << 12));
    *(u16 *)sprite = gfxFlags;
    *(u16 *)sprite = gfxFlags | D_02025FF0.renderFlags;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    scrollTable = (u8 *)&D_02021E90;
    { u32 xOff = 0x1278; *(u32 *)(sprite + 0x14) = effect->worldX - ((*(u32 *)(scrollTable + xOff + ((D_02025FF0.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 yOff = 0x127C; *(u32 *)(sprite + 0x18) = effect->worldY - ((*(u32 *)(scrollTable + yOff + ((D_02025FF0.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    timerPtr = (u16 *)((u8 *)effect + 0x48);
    { u16 initialTimer = 0x12C; *timerPtr = initialTimer; }
    timerPtr[1] = 5;
    scriptOps = (s32 *)0x08671BFC;
    effect->radiusA = (u32)((s64)_call_via_r1((u8 *)arg0->tablePtr + 0x4000, *scriptOps) * 3);
    effect->radiusB = (u32)((s64)_call_via_r1((u8 *)arg0->tablePtr, *scriptOps) * 3);
    *(u16 *)((u8 *)effect + 4) = 2;
    sub_08014668(sprite, effect->radiusA);
    sub_08011368(sprite, animState, 0x0B, 1);
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->index + 0x19) = 0;
    distanceFn = (s32 *)0x08671BB0;
    _call_via_r2((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *distanceFn);
}
