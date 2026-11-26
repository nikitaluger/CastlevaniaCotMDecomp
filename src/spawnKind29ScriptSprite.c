/* Render part allocated by allocEffectPart, shared by the fixed-effect spawners. */
extern struct FixedEffectWorkspace gMainWorkspace;
extern struct FixedEffectScroll gCameraState;
extern u8 gSpriteKindTable[];
extern u16 gKind29LayerAttrs[];
extern u8 gSpriteAnimDataTable[];
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void sub_08011408(u8 *, u8 *, s32, s32, s32);
extern s32 signOf(s32);
extern void registerScriptObject(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
extern s32 _call_via_r1(u8 *, s32);
extern void sub_0802E8EC(void);
extern u32 gMainObjTimerCallback;

/* Kind-table records: a 4-byte pair holding a signed motion value, and a
 * 14-byte per-kind record holding tile/palette ids. */
struct KindMotion { u16 f0; s16 motion; };
struct KindRecord { u16 gfxIndex; u16 f2; u16 palette; u8 _6[0xE]; };

struct Kind29State {
    u8 _0[8];
    s32 worldX;      /* 0x08: 16.16 coordinate from the spawn parameters */
    s32 worldY;      /* 0x0C */
    u8 _10[8];
    u32 speed;       /* 0x18: motion from the kind table */
    s16 kind;        /* 0x1C: 0x29 here */
    u8 _1E[4];
    s16 animSlot;    /* 0x22 */
    u32 savedHandler;/* 0x24 */
    struct FixedEffectSpriteLayer *spriteLayer; /* 0x28 */
    u8 _2C[0x1C];
    s32 extra;       /* 0x48 */
};

struct Kind29Entity {
    u8 _0[2];
    u16 flags;       /* 0x02 */
    u8 _4[0x10];
    u32 x;           /* 0x14 */
    u8 _18[0xA];
    s16 scriptStep;  /* 0x22 */
    u32 callback;    /* 0x24 */
    u8 _28[0x10];
    u8 *sprite;      /* 0x38 */
    struct Kind29State *state; /* 0x3C */
    u8 _40[0x6C];
    void *spawnParams; /* 0xAC */
};

/* Builds a script-spawned kind-0x29 sprite: allocates its sprite and work state,
 * fills a render part from the kind tables, places it against the camera scroll,
 * flips it for negative X, starts its animation, then advances the script. */
void spawnKind29ScriptSprite(struct Kind29Entity *entity) {
    void *spawnParams;
    u8 *sprite;
    struct Kind29State *state;
    u8 *gfxInit;
    u8 *kindTable;
    struct FixedEffectSpriteLayer *layer;
    struct FixedEffectSpriteLayer *layer3;
    s16 *coords;
    u32 one;
    u32 animSlot;
    u32 spriteAttr;
    u8 *camera;
    u8 *scriptEntry;
    u8 *scriptEntry2;
    u8 *scriptPtr;
    u32 *callbackPtr;
    s32 **dispatchTable;
    u32 command;

    spawnParams = entity->spawnParams;
    sprite = allocSpriteObject();
    state = NULL;
    layer = NULL;
    if ((sprite == NULL) ||
        (entity->sprite = sprite, allocWorkSlot((u8 *)entity, 0, 0x50, 0), state = entity->state, state == NULL) ||
        (gfxInit = (u8 *)state + 0x34, state->savedHandler = *(u32 *)((u8 *)entity + 0x24), *(u32 *)((u8 *)entity + 0x24) = (u32)sub_0802E8EC,
         state->kind = 0x29, kindTable = (u8 *)gSpriteKindTable, state->speed = ((struct KindMotion *)kindTable)[0xCD].motion,
         coords = *(s16 **)((u8 *)spawnParams + 4),
         state->worldX = coords[0] << 16, state->worldY = coords[1] << 16,
         animSlot = findKindIndex(0x29), state->animSlot = (s16)animSlot, ((s32)(animSlot << 16) < 0)) ||
        (initSpriteGraphics(sprite, gfxInit, (s32)gSpriteAnimDataTable + state->kind * 0xC), layer = (struct FixedEffectSpriteLayer *)allocEffectPart(), state->spriteLayer = layer, layer == NULL)) {
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    state->spriteLayer->active = 0;
    state->spriteLayer->param2 = 8;
    layer3 = state->spriteLayer;
    one = 1;
    layer3->param3 = one;
    state->spriteLayer->gfxIndex = ((struct KindRecord *)kindTable)[state->kind].gfxIndex;
    state->spriteLayer->anim0 = gKind29LayerAttrs[0];
    state->spriteLayer->anim1 = gKind29LayerAttrs[1];
    state->spriteLayer->anim2 = gKind29LayerAttrs[2];
    state->spriteLayer->anim3 = gKind29LayerAttrs[3];
    state->spriteLayer->palette = ((struct KindRecord *)kindTable)[state->kind].palette;
    state->spriteLayer->object = (u32)sprite;
    state->spriteLayer->timer = 0;
    spriteAttr = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = spriteAttr;
    *(u16 *)sprite = spriteAttr | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    camera = (u8 *)&gCameraState;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = state->worldX - ((*(u32 *)(camera + k + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = state->worldY - ((*(u32 *)(camera + k + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    state->extra = 0;
    if (signOf(state->worldX) > 0)
        *(u16 *)(sprite + 2) = (u16)(*(u16 *)(sprite + 2) | 0x10);
    sub_08011408(sprite, gfxInit, 0, state->extra, one);
    registerScriptObject((u8 *)entity, 0);
    entity->flags |= 0x1000;
    scriptEntry = (u8 *)(entity->scriptStep * 2 + (u32)entity);
    scriptEntry[0x19] = 0;
    callbackPtr = &gMainObjTimerCallback;
    scriptPtr = (u8 *)entity + 0x18;
    sub_080C31E4(scriptPtr, (u8 *)entity + 0x22, *callbackPtr);
    scriptEntry2 = (u8 *)(entity->scriptStep * 2 + (u32)entity);
    scriptEntry2[0x19] = (u8)(scriptEntry2[0x19] + 1);
    scriptPtr += entity->scriptStep * 2;
    command = scriptPtr[0];
    dispatchTable = *(s32 **)((u8 *)entity + 0x14);
    _call_via_r1((u8 *)entity, dispatchTable[command]);
}
