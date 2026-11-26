extern u16 gScriptedSpriteAffineParams[];
/* Creates an entity's scripted attack sprite: allocates the object and its work
 * slot, fills a render layer from the graphics/tile tables, places the sprite
 * relative to the scrolling camera, installs the per-frame update handler and
 * dispatches the follow-up setup through the script callback table. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void sub_08021690(void);
extern void setAttackHitbox(u8 *, void *);
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
extern u8 gSpriteAnimDataTable[];

void initScriptedAttackSprite(struct Entity *entity) {
    u8 *obj;
    struct EntityState *state;
    u8 *anim;
    u8 *attribs;
    s32 kindIndex;
    u32 zero;
    u32 one;
    u8 *cameraBase;

    obj = allocSpriteObject();
    if (obj == NULL) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    entity->object = obj;
    allocWorkSlot((u8 *)entity, 0, SCRIPTED_ATTACK_WORK_SLOT_SIZE, 0);
    state = entity->state;
    if (state == NULL) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    anim = (u8 *)state + 0x34;
    state->updateCallback = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)sub_08021690;
    zero = 0;
    state->animId = SCRIPTED_ATTACK_ANIM_ID;
    one = 1;
    state->active = one;
    state->x = entity->spawnX << 16;
    state->y = entity->spawnY << 16;
    kindIndex = findKindIndex(SCRIPTED_ATTACK_ANIM_ID);
    state->variant = kindIndex;
    if ((kindIndex << 16) < 0) {
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
    state->attribs->kind = zero;
    state->attribs->subPriority = 8;
    state->attribs->shape = one;
    state->attribs->baseTile = gEffectGfxTable[state->animId].baseTile;
    state->attribs->tile0 = gScriptedSpriteAffineParams[0];
    state->attribs->tile1 = gScriptedSpriteAffineParams[1];
    state->attribs->tile2 = gScriptedSpriteAffineParams[2];
    state->attribs->tile3 = gScriptedSpriteAffineParams[3];
    state->attribs->extra = gEffectGfxTable[state->animId].extra;
    state->attribs->object = (u32)obj;
    state->attribs->timer = 0;
    {
        u16 *oam = (u16 *)obj;
        u32 oamAttr = (*oam & 0xC00) |
                      ((((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
                        ((*(u16 *)((u8 *)state + 0x22) + 8) << 12)));
        *oam = oamAttr;
        *oam = oamAttr | gMainWorkspace.gfxFlag;
    }
    *(u32 *)(obj + 0x1C) = SCRIPTED_ATTACK_GFX_ID;
    cameraBase = (u8 *)&gCameraState;
    {
        u32 scrollOffset = 0x1278;
        *(u32 *)(obj + 0x14) = state->x - ((*(u32 *)(cameraBase + scrollOffset + ((gMainWorkspace.cameraIndex + 1) << 6)) + 0x8000) & 0xFFFF0000);
    }
    {
        u32 scrollOffset = 0x127C;
        *(u32 *)(obj + 0x18) = state->y - ((*(u32 *)(cameraBase + scrollOffset + ((gMainWorkspace.cameraIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
    }
    *(u16 *)(obj + 0x28) = SCRIPTED_ATTACK_ANIM_STEP;
    state->attribs->kind |= 1;
    setAttackHitbox(obj, (void *)state);
    entity->flags |= SCRIPTED_ATTACK_READY;
    *(u8 *)((u8 *)entity + 2 * entity->index + 0x19) = zero;
    {
        s32 *callbackEntry = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callbackEntry);
    }
}
