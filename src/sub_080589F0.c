extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void sub_08011368(u8 *, u8 *, s16, s32);
extern void *sub_08016190(void);
extern void sub_08058D40(void);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

struct EffectPart { u8 unk0; u8 kind; u8 layer; u8 priority; u16 gfxIndex; u16 anim0; u16 anim1; u16 anim2; u16 anim3; u16 palette; u32 object; u16 tail; };
struct EffectWork { u8 unk0[8]; s32 worldX; s32 worldY; u32 radiusA; u32 radiusB; u32 state; s16 kind; u8 unk1E[4]; s16 slot; u32 updateCb; struct EffectPart *gfx; };
struct GameState { u8 unk0[0x18A8]; u8 scrollIndex; u8 unk18A9[0x19]; u16 renderFlags; };
extern struct GameState D_02025FF0;
struct ScrollState { u8 unk0[0x1278]; u32 cameraX; u32 cameraY; };
extern struct ScrollState D_02021E90;
struct EffectStats { u16 gfxIndex; u8 unk2[2]; u16 palette; u8 unk6[0xE]; };
extern struct EffectStats D_080CB2B8[];
extern u16 D_080CFD60[];
extern s16 D_080CFD70[];
extern u8 D_080CD400[];

/* Allocate a scripted object's sprite, work block and optional render part,
 * initialise their graphics and position, then run the entry script. */
void sub_080589F0(u8 *arg0) {
    u8 *sprite;
    struct EffectWork *work;
    struct EffectWork *newWork;
    u8 *animState;
    struct EffectPart *part;
    s32 kindIndex;
    u32 gfxFlags;
    u32 zero;
    u8 *scrollTable;
    s32 *scriptOps;
    s16 *animIndexPtr;
    s16 *animTable;
    s32 animIndex;

    sprite = sub_0800355C();
    work = NULL;
    part = NULL;
    kindIndex = 0;
    if ((sprite == NULL) ||
        (*(u8 **)(arg0 + 0x38) = sprite, sub_0800168C(arg0, 0, 0x48, 0), (newWork = *(struct EffectWork **)(arg0 + 0x3C)) == NULL) ||
        ((work = newWork),
         animState = (u8 *)work + 0x34, work->updateCb = *(u32 *)(arg0 + 0x24), *(u32 *)(arg0 + 0x24) = (u32)sub_08058D40,
         work->kind = 0x32,
         work->worldX = *(s16 *)(arg0 + 0x4C) << 16, work->worldY = *(s16 *)(arg0 + 0x54) << 16,
         kindIndex = sub_08013C2C(0x32), work->slot = kindIndex, ((s32)(kindIndex << 16) < 0)) ||
        (sub_0801131C(sprite, animState, (s32)D_080CD400 + work->kind * 0xC),
         animIndexPtr = (s16 *)(arg0 + 0x7C),
         animTable = D_080CFD70,
         animIndex = *animIndexPtr,
         sub_08011368(sprite, animState, animTable[animIndex], 1),
         (*(u16 *)(arg0 + 0x84) & 2) && (part = sub_08016190(), work->gfx = part, part == NULL))) {
        sub_080C31E0(arg0, *(s32 *)(arg0 + 0x24));
        return;
    }
    if (part != NULL) {
        work->gfx->kind = 0;
        work->gfx->layer = 8;
        work->gfx->priority = 1;
        work->gfx->gfxIndex = D_080CB2B8[work->kind].gfxIndex;
        work->gfx->anim0 = D_080CFD60[0];
        work->gfx->anim1 = D_080CFD60[1];
        work->gfx->anim2 = D_080CFD60[2];
        work->gfx->anim3 = D_080CFD60[3];
        work->gfx->palette = D_080CB2B8[work->kind].palette;
        work->gfx->object = (u32)sprite;
        work->gfx->tail = 0;
    }
    gfxFlags = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    zero = 0;
    *(u16 *)sprite = gfxFlags;
    *(u16 *)sprite = gfxFlags | D_02025FF0.renderFlags;
    *(u32 *)(sprite + 0x1C) = 0x8000000B;
    work->radiusA = *(u32 *)(arg0 + 0x5C);
    work->radiusB = *(u32 *)(arg0 + 0x6C);
    scrollTable = (u8 *)&D_02021E90;
    { u32 xOff = 0x1278; *(u32 *)(sprite + 0x14) = work->worldX - ((*(u32 *)(scrollTable + xOff + ((D_02025FF0.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 yOff = 0x127C; *(u32 *)(sprite + 0x18) = work->worldY - ((*(u32 *)(scrollTable + yOff + ((D_02025FF0.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) | 0x1000;
    *(u8 *)(arg0 + 2 * *(s16 *)(arg0 + 0x22) + 0x19) = (u8)zero;
    scriptOps = (s32 *)0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *scriptOps);
}
