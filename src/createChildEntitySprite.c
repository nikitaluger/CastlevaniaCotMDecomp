extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void initWorkStateForKind(void *, void *, void *, void *, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void registerScriptObject(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_08014290(void);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gSpriteAnimDataTable[];
extern u8 gChildSpriteKindTable[];
extern u8 gChildSpriteLayerAttrs[];
extern u32 gScriptStepCallbackTable[];

/* Effect layer allocated for the child sprite. */
struct Extra {
    u8 mode; u8 kind; u8 layer; u8 priority;                              /* 0x00-0x03 */
    u16 gfxIndex; u16 anim0; u16 anim1; u16 anim2; u16 anim3; u16 palette; /* 0x04-0x0E */
    u32 object;                                                          /* 0x10 */
};
/* Work state held at self+0x3C. */
struct Anim {
    u8 _0[8];
    u32 x; u32 y;                           /* 0x08, 0x0C */
    u8 _10[0x0C];
    s16 kind;                               /* 0x1C: sprite kind selecting the graphics */
    u8 _1E[0x0A];
    struct Extra *layer;                    /* 0x28 */
};
struct Entry { u8 _0[4]; void *info; };
struct GfxDef { u16 gfxIndex; u16 _2; u16 palette; u8 _6[0x0E]; };
extern struct GfxDef gSpriteKindTable[];
struct ObjFlags { u8 pad[2]; u16 flags; };

/* Create and initialise a child entity's sprite, work state and effect layer:
 * select its kind from the variant table, apply the facing flag, place it in
 * screen space from the camera scroll, mark it ready and dispatch its script. */
void createChildEntitySprite(u8 *self) {
    u8 *sprite;
    struct Anim *work;
    u8 *animator;
    struct Extra *layer;
    void *source;
    s32 zeroByte;
    u8 *kindTable;
    u8 *layerAttrs;
    u8 *camera, *frameCounterPtr, *scrollX, *scrollY;
    u32 scrollIdx;

    source = *(void **)(self + 0xAC);
    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    *(void **)(self + 0x38) = sprite;
    allocWorkSlot(self, 0, 0x4C, 0);
    if (*(u32 *)(self + 0x3C) == 0) goto fail;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    work = *(struct Anim **)(self + 0x3C);
    animator = (u8 *)work + 0x34;
    installUpdateHandler(self, (u8 *)work, (void *)sub_08014290);
    kindTable = gChildSpriteKindTable;
    {
        s32 kind = *(s16 *)(kindTable + *(u8 *)(self + 0x4C) * 4);
        initWorkStateForKind(self, sprite, (u8 *)work, source, kind);
    }
    initSpriteGraphics(sprite, animator, (s32)gSpriteAnimDataTable + *(s16 *)((u8 *)work + 0x1C) * 0xC);
    setAnimationFrame(sprite, animator, 0, 0);
    if (*(u16 *)((u8 *)((struct Entry *)source)->info + 6) == 0) {
        *(u16 *)(sprite + 2) &= 0xFFEF;
    } else {
        ((struct ObjFlags *)sprite)->flags |= 0x10;
    }
    layerAttrs = gChildSpriteLayerAttrs;
    layer = allocEffectPart();
    work->layer = layer;
    if (layer == NULL) goto fail;
    goto body;

fail:
    sub_080C31E0(self, *(void **)(self + 0x24));
    return;

body:
    layer->kind = 5;
    work->layer->layer = 8;
    work->layer->priority = 1;
    {
        zeroByte = 0;
        work->layer->gfxIndex = gSpriteKindTable[*(s16 *)((u8 *)work + 0x1C)].gfxIndex;
        work->layer->anim0 = *(u16 *)(layerAttrs + 0);
        work->layer->anim1 = *(u16 *)(layerAttrs + 2);
        work->layer->anim2 = *(u16 *)(layerAttrs + 4);
        work->layer->anim3 = *(u16 *)(layerAttrs + 6);
        work->layer->palette = gSpriteKindTable[*(s16 *)((u8 *)work + 0x1C)].palette;
    }
    work->layer->object = (u32)sprite;
    {
        camera = gCameraState;
        frameCounterPtr = gMainWorkspace;
        frameCounterPtr += 0x18A8;
        scrollIdx = ((u32)*frameCounterPtr + 1) * 0x40;
        scrollX = camera + 0x1278;
        *(u32 *)(sprite + 0x14) = *(u32 *)((u8 *)work + 0x08) - ((*(u32 *)(scrollX + scrollIdx) + 0x8000) & 0xFFFF0000);
        scrollIdx = ((u32)*frameCounterPtr + 1) * 0x40;
        scrollY = camera + 0x127C;
        *(u32 *)(sprite + 0x18) = *(u32 *)((u8 *)work + 0x0C) - ((*(u32 *)(scrollY + scrollIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
    registerScriptObject(self, 0);
    {
        u16 flags = *(u16 *)(self + 2);
        flags |= 0x1000;
        *(u16 *)(self + 2) = flags;
    }
    *(u8 *)((u32)(*(s16 *)(self + 0x22) * 2) + (u32)self + 0x19) = (u8)zeroByte;
    {
        u32 *scriptOps = (u32 *)gScriptStepCallbackTable;
        u8 *scriptSlots = self + 0x18;
        sub_080C31E4(scriptSlots, self + 0x22, *scriptOps);
        {
            u8 *stepTimePtr = (u8 *)((u32)(*(s16 *)(self + 0x22) * 2) + (u32)self + 0x19);
            *stepTimePtr = (u8)(*stepTimePtr + 1);
            stepTimePtr = scriptSlots;
            stepTimePtr += *(s16 *)(self + 0x22) * 2;
            {
                u8 opcode = *stepTimePtr;
                void *nextHandler = ((void **)*(void **)(self + 0x14))[opcode];
                sub_080C31E0(self, nextHandler);
            }
        }
    }
}
