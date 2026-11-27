/* Spawns the sprite object owned by a fresh child state: allocates the sprite
 * and a 0x28-byte child state, initialises the animation from the shared gfx
 * template, picks the frame for the entity's variant, copies its coordinates and
 * parameters, converts them to screen space, then advances the parent's state. */
struct Entity {
    u8 _00[2]; u16 flags; u8 _04[0x10]; u32 unk14; u8 _18[4]; u32 unk1C;
    u8 _20[2]; s16 stateIndex; void *updateFn; u8 _28[0x10];
    void *sprite; void *childState;
    u8 _40[0xC]; u32 x; u8 _50[0xC]; u32 y; u8 _60[0xC];
    u16 spawnFlags; u8 _6E[6]; s16 variant; u8 _76[6]; u32 paramA; u8 _80[0xC]; u32 paramB; u8 _90[0xC]; u32 paramC;
};
struct SpriteObj { u16 attr0; u16 attr1; u8 _04[0x10]; u32 x; u32 y; u32 param; };
struct GlobalData { u8 _0[0x18a8]; u8 frameIndex; u8 _a9[0x19]; u16 spriteBits; };
extern struct GlobalData gMainWorkspace;
extern u8 gCameraState[];      /* shared video state (BG scroll buffers) */
extern u32 gVariantSpriteGfxDesc[];     /* shared gfx template descriptor */
extern s16 gVariantSpriteFrames[];     /* animation frame per variant */
extern void *gScriptStepCallbackTable;
void *allocSpriteObject(void);                             /* alloc sprite */
void allocWorkSlot(void *, int, int, int);             /* alloc + clear slot */
void initSpriteGraphics(void *, void *, void *);            /* init sprite gfx */
void setAnimationFrame(void *, void *, s16, int);          /* set animation frame */
void sub_080C31E0(void *, void *);                    /* indirect call */
void sub_080C31E4(void *, void *, s32);               /* indirect call */

/* Create the sprite object and 0x28-byte child state for a variant-selected entity animation, convert its world position to screen space against the camera scroll, then advance the parent's script. */ void initVariantSpriteObject(struct Entity *entity) {
    void *sprite;
    void *childState;
    void **cmdTable;
    u8 *script;
    u8 *cmdPtr;
    s16 variant;
    u8 *statePtr;

    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    entity->sprite = sprite;
    allocWorkSlot(entity, 0, 0x28, 0);
    childState = entity->childState;
    if (childState == NULL) {
fail:
        sub_080C31E0(entity, entity->updateFn);
        return;
    }
    initSpriteGraphics(sprite, childState, gVariantSpriteGfxDesc);
    variant = entity->variant;
    setAnimationFrame(sprite, childState, gVariantSpriteFrames[variant], 0);
    if (entity->spawnFlags & 0x10) ((struct SpriteObj *)sprite)->attr1 |= 0x10;
    if (entity->spawnFlags & 0x20) ((struct SpriteObj *)sprite)->attr1 |= 0x20;
    ((struct SpriteObj *)sprite)->param = (entity->spawnFlags & 0x0F) | 0x80000000;
    ((struct SpriteObj *)sprite)->attr0 |= gMainWorkspace.spriteBits;
    statePtr = (u8 *)childState + 0x14;
    *(u32 *)((u8 *)childState + 0x14) = entity->x;
    *(u32 *)(statePtr + 4) = entity->y;
    *(u32 *)(statePtr + 8) = entity->paramA;
    *(u32 *)(statePtr + 0xC) = entity->paramB;
    *(u32 *)(statePtr + 0x10) = entity->paramC;
    {
        u8 *scroll = gCameraState;
        u8 *workspace = (u8 *)&gMainWorkspace;
        u8 *scrollX;
        u8 *scrollY;
        u32 coordIdx;

        workspace += 0x18A8;

        coordIdx = ((u32)*workspace + 1) * 0x40;
        scrollX = scroll + 0x1278;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)(statePtr) - ((*(u32 *)(scrollX + coordIdx) + 0x8000) & 0xFFFF0000);

        coordIdx = ((u32)*workspace + 1) * 0x40;
        scrollY = scroll + 0x127C;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)(statePtr + 4) - ((*(u32 *)(scrollY + coordIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
    *(u16 *)((u8 *)entity + 2) |= 0x1000;
    *(u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity + 0x19) = 0;
    cmdTable = &gScriptStepCallbackTable;
    script = (u8 *)entity;
    script += 0x18;
    sub_080C31E4(script, (u8 *)entity + 0x22, (s32)*cmdTable);
    *(u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity + 0x19) += 1;
    cmdPtr = script + (u32)(*(s16 *)((u8 *)entity + 0x22)) * 2;
    sub_080C31E0((u8 *)entity, *(void **)(*(u8 **)((u8 *)entity + 0x14) + *(u8 *)cmdPtr * 4));
}
