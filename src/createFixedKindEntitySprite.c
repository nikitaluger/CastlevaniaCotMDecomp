/* Creates and initializes an entity's sprite and animation with the fixed kind 0x1E,
 * positions it relative to the camera, then dispatches the next behavior. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void sub_08020020(u8 *);
extern void sub_0801FFFC(void);
extern void sub_08020498(u8 *, void *);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

struct SpriteAttribs { u8 _0; u8 kind; u8 subPriority; u8 shape; u16 baseTile; u16 tile0; u16 tile1; u16 tile2; u16 tile3; u16 extra; u32 object; u16 timer; };
struct EntityState { u8 _0[8]; s32 x; s32 y; u32 _10; u32 _14; u32 active; s16 animId; u8 _1E[4]; s16 variant; u32 updateCallback; struct SpriteAttribs *attribs; u8 _2C[0x48-0x2C]; s32 lifetime; s32 counter; };
struct Entity { u8 _0[2]; u16 flags; u8 _4[0x22-4]; s16 index; u8 _24[0x38-0x24]; u8 *object; struct EntityState *state; u8 _40[0x4C-0x40]; s16 spawnX; u8 _4E[6]; s16 spawnY; };
struct GlobalStateA { u8 _0[0x18A8]; u8 cameraIndex; u8 _18A9[0x19]; u16 gfxFlag; };
extern struct GlobalStateA gMainWorkspace;
struct GlobalStateB { u8 _0[0x1278]; u32 coordX; u32 coordY; };
extern struct GlobalStateB gCameraState;
struct AnimTable { u8 _0[4]; u16 baseTile; u16 extra; u8 _8[0x28-8]; };
extern struct AnimTable gEffectGfxTable[];
extern u16 gFixedAttackAffineParams[];
extern u8 gSpriteAnimDataTable[];

void createFixedKindEntitySprite(struct Entity *entity) {
    u8 *obj;
    struct EntityState *state;
    u8 *anim;
    u8 *attribs;
    s32 variantRnd;
    u32 zeroA;
    u32 zeroB;
    u32 one;
    u8 *coordBase;

    obj = allocSpriteObject();
    if (obj == NULL) {
        sub_08020020((u8 *)entity);
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    entity->object = obj;
    allocWorkSlot((u8 *)entity, 0, FIXED_KIND_WORK_SLOT_SIZE, 0);
    state = entity->state;
    if (state == NULL) {
        sub_08020020((u8 *)entity);
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    anim = (u8 *)state + 0x34;
    state->updateCallback = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)sub_0801FFFC;
    state->animId = FIXED_KIND_SPRITE_ANIM_ID;
    one = 1;
    state->active = one;
    state->x = entity->spawnX << 16;
    state->y = entity->spawnY << 16;
    variantRnd = findKindIndex(FIXED_KIND_SPRITE_ANIM_ID);
    state->variant = variantRnd;
    if ((variantRnd << 16) < 0) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    initSpriteGraphics(obj, anim, (s32)gSpriteAnimDataTable + state->animId * 0xC);
    attribs = allocEffectPart();
    state->attribs = (struct SpriteAttribs *)attribs;
    if (attribs == NULL) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    zeroA = 0;
    state->attribs->kind = zeroA;
    state->attribs->subPriority = 8;
    state->attribs->shape = one;
    state->attribs->baseTile = gEffectGfxTable[state->animId].baseTile;
    state->attribs->tile0 = gFixedAttackAffineParams[0];
    state->attribs->tile1 = gFixedAttackAffineParams[1];
    state->attribs->tile2 = gFixedAttackAffineParams[2];
    state->attribs->tile3 = gFixedAttackAffineParams[3];
    state->attribs->extra = gEffectGfxTable[state->animId].extra;
    state->attribs->object = (u32)obj;
    zeroB = 0;
    state->attribs->timer = zeroB;
    {
        u16 *o = (u16 *)obj;
        u32 gfxAttr = (*o & 0xC00) |
                      ((((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
                        ((*(u16 *)((u8 *)state + 0x22) + 8) << 12)));
        *o = gfxAttr;
        *o = gfxAttr | gMainWorkspace.gfxFlag;
    }
    *(u32 *)(obj + 0x1C) = CHILD_SPRITE_GFX_ID;
    coordBase = (u8 *)&gCameraState;
    {
        u32 off = 0x1278;
        *(u32 *)(obj + 0x14) = state->x - ((*(u32 *)(coordBase + off + ((gMainWorkspace.cameraIndex + 1) << 6)) + 0x8000) & 0xFFFF0000);
    }
    {
        u32 off = 0x127C;
        *(u32 *)(obj + 0x18) = state->y - ((*(u32 *)(coordBase + off + ((gMainWorkspace.cameraIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
    }
    {
        u32 *extraState = (u32 *)((u8 *)state + 0x48);
        extraState[0] = 0xB4;
        extraState[1] = zeroB;
    }
    *(u16 *)(obj + 0x28) = CHILD_SPRITE_ANIM_STEP;
    sub_08020498(obj, (void *)state);
    entity->flags |= CHILD_SPRITE_READY;
    *(u8 *)((u8 *)entity + 2 * entity->index + 0x19) = zeroA;
    {
        s32 *callbackPtr = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callbackPtr);
    }
}
