#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
struct SpawnSprite { u16 flags0; u8 pad2[0x12]; u32 worldX, worldY, typeId; u8 pad20[0x60]; };
struct Work { u8 pad0[0x1c]; s16 kind; u8 pad1e[4]; s16 gfxIndex; u8 pad24[4]; void *part1; u8 pad2c[0x1c]; void *part2; u8 pad4c[0x18]; };
extern struct SpawnSprite *allocSpriteObject(void);
extern void allocWorkSlot(void *arg0, int a, int b, int c);
extern void installUpdateHandler(void *a, void *b, void (*c)(void));
extern void sub_08014290(void);
extern s16 findKindIndex(s16 kind);
extern void initSpriteGraphics(struct SpawnSprite *a, u8 *b, void *c);
extern void *allocEffectPart(void);
extern void _call_via_r1(void *a, u32 b);
extern void _call_via_r2(u8 *a, s16 *b, u32 c);
extern void registerScriptObject(void *a, u32 b);
extern u8 gSpriteAnimDataTable[];
extern u16 gEffectAnimTable[];
extern u8 gCameraState[]; extern u8 gMainWorkspace[]; extern u32 gMainObjTimerCallbacks;

void sub_0803A478(void *arg0) {
    struct SpawnSprite *sprite;
    struct Work *work;
    u8 *anim;
    void *part;
    u8 *cam, *ws, *base;
    u32 idx;
    u8 *scriptData;
    u32 *audioCmd;

    sprite = allocSpriteObject();
    if (sprite == 0) goto fail;
    U32(arg0, 0x38) = (u32)sprite;
    allocWorkSlot(arg0, 0, 0x4c, 0);
    if (U32(arg0, 0x3c) == 0) goto fail;
    sprite->typeId = 0x8000000A;
    work = (struct Work *)U32(arg0, 0x3c);
    anim = (u8 *)work + 0x34;
    installUpdateHandler(arg0, work, sub_08014290);
    work->kind = *(s16 *)(0x080CD400 + U8(arg0, 0x4c) * 4);
    work->gfxIndex = findKindIndex(work->kind);
    if (work->gfxIndex < 0) goto fail;
    initSpriteGraphics(sprite, anim, (u8 *)gSpriteAnimDataTable + work->kind * 12);
    part = allocEffectPart();
    work->part1 = part;
    if (part == 0) goto fail;
    ((u8 *)part)[1] = 0;
    ((u8 *)part)[2] = 8;
    ((u8 *)part)[3] = 1;
    *(u16 *)((u8 *)part + 4) = *(u16 *)(0x080CBDD0 + work->kind * 40 + 4);
    *(u16 *)((u8 *)part + 6) = gEffectAnimTable[0];
    *(u16 *)((u8 *)part + 8) = gEffectAnimTable[1];
    *(u16 *)((u8 *)part + 10) = gEffectAnimTable[2];
    *(u16 *)((u8 *)part + 12) = gEffectAnimTable[3];
    *(u16 *)((u8 *)part + 14) = *(u16 *)(0x080CBDD0 + work->kind * 40 + 6);
    *(u32 *)((u8 *)part + 16) = (u32)sprite;
    part = allocEffectPart();
    work->part2 = part;
    if (part == 0) goto fail;
    ((u8 *)part)[1] = 0;
    ((u8 *)part)[2] = 8;
    ((u8 *)part)[3] = 1;
    *(u16 *)((u8 *)part + 4) = *(u16 *)(0x080CBDD0 + work->kind * 40 + 4);
    *(u16 *)((u8 *)part + 6) = gEffectAnimTable[4];
    *(u16 *)((u8 *)part + 8) = gEffectAnimTable[5];
    *(u16 *)((u8 *)part + 10) = gEffectAnimTable[6];
    *(u16 *)((u8 *)part + 12) = gEffectAnimTable[7];
    *(u16 *)((u8 *)part + 14) = *(u16 *)(0x080CBDD0 + work->kind * 40 + 6);
    *(u32 *)((u8 *)part + 16) = (u32)sprite;
    cam = gCameraState;
    ws = gMainWorkspace + 0x18A8;
    idx = ((u32)*ws + 1) * 0x40;
    base = cam + 0x1278;
    sprite->worldX = *(u32 *)((u8 *)work + 8) - ((*(u32 *)(base + idx) + 0x8000) & 0xFFFF0000);
    idx = ((u32)*ws + 1) * 0x40;
    base = cam + 0x127C;
    sprite->worldY = *(u32 *)((u8 *)work + 12) - ((*(u32 *)(base + idx) + 0xFFFF8000) & 0xFFFF0000);
    registerScriptObject(arg0, 0);
    U16(arg0, 2) |= 0x1000;
    U8(arg0, 0x19 + (s16)U16(arg0, 0x22) * 2) = 0;
    audioCmd = &gMainObjTimerCallbacks;
    scriptData = (u8 *)arg0 + 0x18;
    _call_via_r2(scriptData, (s16 *)((u8 *)arg0 + 0x22), *audioCmd);
    {
        u8 *stepSlot = (u8 *)((s16)U16(arg0, 0x22) * 2 + (u32)arg0);
        stepSlot[0x19]++;
        _call_via_r1(arg0, *(u32 *)(U32(arg0, 0x14) + scriptData[(s16)U16(arg0, 0x22) * 2] * 4));
    }
    return;
fail:
    _call_via_r1(arg0, U32(arg0, 0x24));
}
