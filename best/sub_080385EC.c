#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
struct SpawnSprite { u16 flags0; u8 pad2[0x12]; u32 worldX, worldY, typeId; u8 pad20[0x60]; };
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *arg0, int a, int b, int c);
extern void installUpdateHandler(void *a, void *b, void (*c)(void));
extern void sub_08014290(void);
extern s16 findKindIndex(s16 kind);
extern void initSpriteGraphics(void *a, void *b, void *c);
extern void setAnimationFrame(void *a, void *b, s16 c, int d);
extern void *allocEffectPart(void);
extern void _call_via_r1(void *a, u32 b);
extern void _call_via_r2(u8 *a, s16 *b, u32 c);
extern void registerScriptObject(void *a, u32 b);
extern u8 gSpriteAnimDataTable[]; extern u8 gCameraState[]; extern u8 gMainWorkspace[]; extern u32 gMainObjTimerCallbacks;

void sub_080385EC(void *arg0) {
    struct SpawnSprite *sprite;
    u8 *work;
    u8 *anim;
    u32 tbl[2];
    /* rough skeleton - incomplete */
    *(u32 *)&tbl[0] = *(u32 *)0x080CF000; /* placeholder */
    sprite = allocSpriteObject();
    if (sprite == 0) goto fail;
    U32(arg0, 0x38) = (u32)sprite;
    allocWorkSlot(arg0, 0, 0x48, 0);
    if (U32(arg0, 0x3c) == 0) goto fail;
    sprite->typeId = 0x8000000A;
    work = (u8 *)U32(arg0, 0x3c);
    anim = work + 0x34;
    installUpdateHandler(arg0, work, sub_08014290);
    *(s16 *)(work + 0x1c) = *(s16 *)(0x080CD400 + U8(arg0, 0x4c) * 4);
    *(u32 *)(work + 8) = U32(arg0, 0x5c);
    *(u32 *)(work + 0xc) = U32(arg0, 0x6c);
    *(u32 *)(work + 0x10) = U32(arg0, 0x7c);
    *(u32 *)(work + 0x14) = U32(arg0, 0x8c);
    *(s16 *)(work + 0x22) = findKindIndex(*(s16 *)(work + 0x1c));
    if (*(s16 *)(work + 0x22) < 0) goto fail;
    initSpriteGraphics(sprite, anim, (u8 *)gSpriteAnimDataTable + *(s16 *)(work + 0x1c) * 12);
    /* ... incomplete ... */
    return;
fail:
    _call_via_r1(arg0, U32(arg0, 0x24));
}
