/* Allocate an entity's sprite and work state, fill them from the global
 * tuning tables, install the update callback and advance the script pointer. */
struct GlobalFlags { u8 _0[0x18C2]; u16 flags; };
extern struct GlobalFlags gMainWorkspace;
struct SpriteDesc { u8 _0, active, kind, layer; u16 gfx0, gfx1, gfx2, gfx3, gfx4; s16 frame; u32 owner; };
struct MoverState {
    u8 _0[8]; u32 x, y, velX, velY; u8 _18[4]; u16 anim; u8 _1E[4]; u16 state; u8 _24[4];
    struct SpriteDesc *desc;
};
struct FrameDef { u8 _0[0x18]; u16 data0; u16 data1; u8 _18[0x0C]; };
struct MoveParam { s32 velX; s32 velY; };
extern struct FrameDef gEffectGfxTable[];
extern struct MoveParam gKind66Velocities[];
extern u16 gKind66GfxParams[];
extern u32 gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void setSpriteFlipForDirection(void *, s32);
extern void initSharedSpriteGraphics(void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void _call_via_r1(u8 *, u32);
extern void _call_via_r2(u8 *, u8 *, u32);
extern void updateActorEffectSubObject(void);

void spawnKind66Effect(u8 *entity) {
    u8 *sprite;
    struct MoverState *mover;
    u8 *animState;
    u16 *gfxParams;
    u8 *scriptPtr;
    s32 *callbackTable;
    u8 *stepPtr;

    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    *(u32 *)(entity + 0x38) = (u32)sprite;
    allocWorkSlot(entity, 0, 0x48, 0);
    if (*(u32 *)(entity + 0x3C) == 0) goto fail;
    *(u32 *)(sprite + 0x1C) = 0x8000000B;
    mover = (struct MoverState *)*(u32 *)(entity + 0x3C);
    animState = (u8 *)mover + 0x34;
    installUpdateHandler(entity, mover, updateActorEffectSubObject);
    mover->anim = 0x66;
    *(u16 *)sprite |= gMainWorkspace.flags;
    mover->x = *(u32 *)(entity + 0x4C);
    mover->y = *(u32 *)(entity + 0x5C);
    mover->velX = gKind66Velocities[*(u8 *)(entity + 0x70)].velX * (s8)*(u8 *)(entity + 0x6C);
    mover->velY = gKind66Velocities[*(u8 *)(entity + 0x70)].velY;
    setSpriteFlipForDirection(sprite, -mover->velX);
    initSharedSpriteGraphics(sprite, animState);
    setAnimationFrame(sprite, animState, 0, 1);
    gfxParams = gKind66GfxParams;
    mover->desc = allocEffectPart();
    if (mover->desc == NULL) goto fail;
    goto cont;
fail:
    _call_via_r1(entity, *(u32 *)(entity + 0x24));
    return;
cont:
    mover->desc->active = 1;
    mover->desc->kind = 8;
    mover->desc->layer = 1;
    mover->desc->gfx0 = gEffectGfxTable[*(s16 *)((u8 *)mover + 0x1C)].data0;
    mover->desc->gfx1 = gfxParams[0];
    mover->desc->gfx2 = gfxParams[1];
    mover->desc->gfx3 = gfxParams[2];
    mover->desc->gfx4 = gfxParams[3];
    mover->desc->frame = gEffectGfxTable[*(s16 *)((u8 *)mover + 0x1C)].data1;
    mover->desc->owner = (u32)sprite;
    *(u16 *)(entity + 2) |= 0x1000;
    *(u8 *)(entity + (u32)(*(s16 *)(entity + 0x22)) * 2 + 0x19) = 0;
    callbackTable = &gScriptStepCallbackTable;
    scriptPtr = entity + 0x18;
    _call_via_r2(scriptPtr, entity + 0x22, *callbackTable);
    *(u8 *)(entity + (u32)(*(s16 *)(entity + 0x22)) * 2 + 0x19) += 1;
    stepPtr = scriptPtr + (u32)(*(s16 *)(entity + 0x22)) * 2;
    _call_via_r1(entity, *(u32 *)(*(u32 *)(entity + 0x14) + *(u8 *)stepPtr * 4));
}
