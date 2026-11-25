extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_080212E4(u8 *);
extern void sub_080216B0(u8 *, void *);
extern void sub_080212C0(void);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

struct EffectPart { u8 unk0; u8 kind; u8 layer; u8 priority; u16 gfxIndex; u16 anim0; u16 anim1; u16 anim2; u16 anim3; u16 palette; u32 object; u16 tail; };
struct EffectWork { u8 unk0[8]; s32 worldX; s32 worldY; u32 radiusA; u32 radiusB; u32 state; s16 kind; u8 unk1E[4]; s16 slot; u32 updateCb; struct EffectPart *gfx; };
struct ScriptedObject { u8 unk0[2]; u16 flags; u8 unk4[0x22-4]; s16 index; u8 unk24[0x38-0x24]; u8 *sprite; struct EffectWork *work; u8 unk40[0x4C-0x40]; s16 worldX; u8 unk4E[6]; s16 worldY; u8 unk56[0x5C-0x56]; u32 radius; u8 unk60[0x6C-0x60]; u32 data; };
struct GameState { u8 unk0[0x18A8]; u8 scrollIndex; u8 unk18A9[0x19]; u16 renderFlags; };
extern struct GameState D_02025FF0;
struct ScrollState { u8 unk0[0x1278]; u32 cameraX; u32 cameraY; };
extern struct ScrollState D_02021E90;
struct EffectTemplate { u8 unk0[4]; u16 gfxIndex; u16 palette; u8 unk8[0x28-8]; };
extern struct EffectTemplate D_080CBDD0[];
extern u16 D_080CE7EC[];
extern u8 D_080CD400[];
extern u32 D_08671BB0;

/* Allocate this object's sprite, work block and render part, initialise their
 * graphics and screen position, then hand control to the entry script. */
void sub_08020EEC(struct ScriptedObject *arg0) {
    u8 *sprite;
    struct EffectWork *work;
    u8 *animState;
    u8 *partPtr;
    s32 kindIndex;
    u32 gfxFlags;
    u32 zero;
    u32 one;
    u8 *scrollTable;
    s32 *scriptOps;

    sprite = sub_0800355C();
    if (sprite == NULL) { sub_080212E4((u8 *)arg0); sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24)); return; }
    arg0->sprite = sprite;
    sub_0800168C((u8 *)arg0, 0, 0x48, 0);
    work = arg0->work;
    if (work == NULL) { sub_080212E4((u8 *)arg0); sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24)); return; }
    animState = (u8 *)work + 0x34;
    work->updateCb = *(u32 *)((u8 *)arg0 + 0x24);
    *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_080212C0;
    zero = 0;
    work->kind = 0x20;
    one = 1;
    work->state = one;
    work->worldX = arg0->worldX << 16;
    work->worldY = arg0->worldY << 16;
    kindIndex = sub_08013C2C(0x20);
    work->slot = kindIndex;
    if ((s32)(kindIndex << 16) < 0) { sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24)); return; }
    sub_0801131C(sprite, animState, (s32)D_080CD400 + work->kind * 0xC);
    partPtr = sub_08016190();
    work->gfx = (struct EffectPart *)partPtr;
    if (partPtr == NULL) { sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24)); return; }

    work->gfx->kind = zero;
    work->gfx->layer = 8;
    work->gfx->priority = one;
    work->gfx->gfxIndex = D_080CBDD0[work->kind].gfxIndex;
    work->gfx->anim0 = D_080CE7EC[0];
    work->gfx->anim1 = D_080CE7EC[1];
    work->gfx->anim2 = D_080CE7EC[2];
    work->gfx->anim3 = D_080CE7EC[3];
    work->gfx->palette = D_080CBDD0[work->kind].palette;
    work->gfx->object = (u32)sprite;
    work->gfx->tail = zero;
    gfxFlags = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = gfxFlags;
    *(u16 *)sprite = gfxFlags | D_02025FF0.renderFlags;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    scrollTable = (u8 *)&D_02021E90;
    { u32 xOff = 0x1278; *(u32 *)(sprite + 0x14) = work->worldX - ((*(u32 *)(scrollTable + xOff + ((D_02025FF0.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 yOff = 0x127C; *(u32 *)(sprite + 0x18) = work->worldY - ((*(u32 *)(scrollTable + yOff + ((D_02025FF0.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    *(u16 *)(sprite + 0x28) = 0x29;
    sub_080216B0(sprite, work);
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->index + 0x19) = zero;
    scriptOps = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptOps);
}
