#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
struct SpawnSprite { u16 flags0; u8 pad2[0x12]; u32 worldX, worldY, typeId; u8 pad20[0x60]; };
struct Part { u8 unk0; u8 kind; u8 layer; u8 priority; u16 gfxIndex; u16 anim0, anim1, anim2, anim3; u16 palette; u32 object; };
struct Work {
    u8 unk0[8];
    u32 worldX, worldY;
    u8 pad10[8];
    u32 state;
    s16 kind;
    u8 pad1e[4];
    s16 slot;
    u8 pad24[4];
    struct Part *part1;
    u8 pad2c[0x1c];
    struct Part *part2;
    u8 pad4c[0x18];
};
struct EffectTemplate { u8 unk0[4]; u16 gfxIndex; u16 palette; u8 unk8[0x28 - 8]; };
extern struct SpawnSprite *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *entity, s32 heapId, s32 size, s32 slot);
extern void installUpdateHandler(void *a, void *b, void *c);
extern void sub_0803A9CC(void);
extern s32 findKindIndex(s16 kind);
extern void initSpriteGraphics(void *sprite, void *init, s32 desc);
extern void *allocEffectPart(void);
extern void sub_080C31E0(u8 *, void *);
extern void sub_080C31E4(u8 *, u8 *, u32);
extern void registerScriptObject(void *, s32);
extern struct EffectTemplate gEffectGfxTable[];
extern u32 gSpriteAnimDataTable[];
extern u16 gScriptedSpriteAffineParams[];
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u32 gMainObjTimerCallbacks[];

void sub_0803A478(u8 *arg0) {
int __repair_literal;

    struct SpawnSprite *sprite;
    struct Work *work;
    u8 *anim;
    u8 *cam;
    u8 *ws;
    u32 idx;
    u8 *scrollX;
    u8 *scrollY;
    u8 *scriptData;
    u32 *audioCmd;
    u16 *affine;
    u16 *affine2;

    sprite = allocSpriteObject();
    if (sprite == 0) goto fail;
    U32(arg0, 0x38) = (u32)sprite;
    allocWorkSlot(arg0, 0, 0x4c, 0);
    if (U32(arg0, 0x3c) == 0) goto fail;
    sprite->typeId = 0x8000000A;
    work = (struct Work *)U32(arg0, 0x3c);
    anim = (u8 *)work + 0x34;
    installUpdateHandler(arg0, work, sub_0803A9CC);
    work->kind = gSpriteAnimDataTable[U8(arg0, 0x4c)];
    work->slot = findKindIndex(work->kind);
    if (work->slot < 0) goto fail;
    initSpriteGraphics(sprite, anim, (s32)(u8 *)0x080CF190 + work->kind * 12);
    affine = gScriptedSpriteAffineParams;
    work->part1 = (struct Part *)allocEffectPart();
    if (work->part1 == 0) goto fail;
    work->part1->kind = 0;
    work->part1->layer = 8;
    work->part1->priority = 1;
    work->part1->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
    { u16 *__fence_affine; do { __fence_affine = affine; } while (0); work->part1->anim0 = __fence_affine[0]; }
    work->part1->anim1 = affine[1];
    work->part1->anim2 = affine[2];
    work->part1->anim3 = affine[3];
    work->part1->palette = gEffectGfxTable[work->kind].palette;
    work->part1->object = (u32)sprite;
    affine2 = affine + 4;
    work->part2 = (struct Part *)allocEffectPart();
    if (work->part2 == 0) goto fail;
    goto body;
fail:
    sub_080C31E0(arg0, (void *)U32(arg0, 0x24));
    return;
body:
    work->part2->kind = 0;
    work->part2->layer = 8;
    work->part2->priority = 1;
    work->part2->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
    work->part2->anim0 = affine2[0];
    work->part2->anim1 = affine2[1];
    work->part2->anim2 = affine2[2];
    work->part2->anim3 = affine2[3];
    work->part2->palette = gEffectGfxTable[work->kind].palette;
    work->part2->object = (u32)sprite;
    do { ws = gMainWorkspace + 0x18A8; } while (0);
    idx = ((u32)*ws + 1) * 0x40;
    scrollX = (cam = gCameraState) + 0x1278;
    *((u32 *)((u8 *)sprite + 0x14)) = (*((u32 *)((u8 *)work + 0x08))) - ((*((u32 *)(scrollX + idx)) + 0x8000) & 0xFFFF0000);
    idx = ((u32)*ws + 1) * 0x40;
    scrollY = cam + 0x127C;
    *((u32 *)((u8 *)sprite + 0x18)) = (*((u32 *)((u8 *)work + 0x0C))) - ((*((u32 *)(scrollY + idx)) + 0xFFFF8000) & 0xFFFF0000);
    registerScriptObject(arg0, 0);
    U16(arg0, 2) |= 0x1000;
    U8(arg0, 0x19 + (s16)U16(arg0, 0x22) * 2) = 0;
    audioCmd = (u32 *)gMainObjTimerCallbacks;
    scriptData = arg0 + 0x18;
    sub_080C31E4(scriptData, (u8 *)arg0 + 0x22, *audioCmd);
    U8(arg0, 0x19 + (s16)U16(arg0, 0x22) * 2)++;
__repair_literal = 2;

    sub_080C31E0(arg0, *(void **)(U32(arg0, 0x14) + U8(scriptData, (s16)U16(arg0, 0x22) * __repair_literal) * 4));
}
