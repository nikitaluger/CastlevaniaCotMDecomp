extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void destroyObject(void);
extern void clearObjectSlot(u8 *);
extern void sub_08023BDC(u8 *, u8 *);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

struct SpriteAttribs { u8 _0; u8 kind; u8 subPriority; u8 shape; u16 baseTile; u16 tile0; u16 tile1; u16 tile2; u16 tile3; u16 extra; u32 object; u16 timer; };
struct SubAttribs { u16 f0; u16 f2; struct SpriteAttribs *attribs; };
struct EntityState { u8 _0[8]; s32 x; s32 y; u32 _10; u32 _14; u32 active; s16 animId; u8 _1E[4]; s16 variant; u32 updateCallback; struct SpriteAttribs *attribs; u8 _2C[0x48-0x2C]; struct SubAttribs sub; };
struct Entity { u8 _0[2]; u16 flags; u8 _4[0x22-4]; s16 index; u8 _24[0x38-0x24]; u8 *object; struct EntityState *state; u8 _40[0x4C-0x40]; s16 spawnX; u8 _4E[6]; s16 spawnY; };
struct GlobalStateA { u8 _0[0x18A8]; u8 cameraIndex; u8 _18A9[0x19]; u16 gfxFlag; };
extern struct GlobalStateA gMainWorkspace;
struct GlobalStateB { u8 _0[0x1278]; u32 coordX; u32 coordY; };
extern struct GlobalStateB gCameraState;
struct AnimTable { u8 _0[4]; u16 baseTile; u16 extra; u8 _8[0x14-8]; };
extern struct AnimTable gEffectGfxTable[];
extern u16 D_080CE84C[];
extern u8 gSpriteAnimDataTable[];

void sub_0803109C(struct Entity *entity) {
    u8 *effectSprite;
    struct EntityState *state;
    u8 *gfxInit;
    struct SpriteAttribs *primaryAttribs;
    s32 kindIndex;
    u32 enabled;
    u8 *cameraBase;

    effectSprite = allocSpriteObject();
    if (effectSprite == NULL) {
        clearObjectSlot((u8 *)entity);
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    entity->object = effectSprite;
    allocWorkSlot((u8 *)entity, 0, 0x54, 0);
    state = entity->state;
    if (state == NULL) {
        clearObjectSlot((u8 *)entity);
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    gfxInit = (u8 *)state + 0x34;
    state->updateCallback = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)destroyObject;
    state->animId = 0x25;
    enabled = 1;
    state->active = enabled;
    state->x = entity->spawnX << 16;
    state->y = entity->spawnY << 16;
    kindIndex = findKindIndex(0x25);
    state->variant = kindIndex;
    if ((kindIndex << 16) < 0) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    initSpriteGraphics(effectSprite, gfxInit, (s32)gSpriteAnimDataTable + state->animId * 0xC);
    primaryAttribs = allocEffectPart();
    state->attribs = primaryAttribs;
    if (primaryAttribs == NULL) {
        sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    primaryAttribs->kind = 0;
    primaryAttribs->subPriority = 8;
    primaryAttribs->shape = enabled;
    primaryAttribs->baseTile = gEffectGfxTable[state->animId].baseTile;
    primaryAttribs->tile0 = D_080CE84C[0];
    primaryAttribs->tile1 = D_080CE84C[1];
    primaryAttribs->tile2 = D_080CE84C[2];
    primaryAttribs->tile3 = D_080CE84C[3];
    primaryAttribs->extra = gEffectGfxTable[state->animId].extra;
    primaryAttribs->object = (u32)effectSprite;
    primaryAttribs->timer = 0;
    {
        u16 *attrWord = (u16 *)effectSprite;
        u32 attrBits = (*attrWord & 0xC00) |
                      ((((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
                        ((*(u16 *)((u8 *)state + 0x22) + 8) << 12)));
        *attrWord = attrBits;
        *attrWord = attrBits | gMainWorkspace.gfxFlag;
    }
    *(u32 *)(effectSprite + 0x1C) = 0x8000000A;
    cameraBase = (u8 *)&gCameraState;
    {
        u32 coordOff = 0x1278;
        *(u32 *)(effectSprite + 0x14) = state->x - ((*(u32 *)(cameraBase + coordOff + ((gMainWorkspace.cameraIndex + 1) << 6)) + 0x8000) & 0xFFFF0000);
    }
    {
        u32 coordOff = 0x127C;
        *(u32 *)(effectSprite + 0x18) = state->y - ((*(u32 *)(cameraBase + coordOff + ((gMainWorkspace.cameraIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
    }
    {
        struct SubAttribs *secondary = &state->sub;
        struct SpriteAttribs *secondaryAttribs;
        secondary->f0 = 0;
        secondary->f2 = 9;
        secondaryAttribs = allocEffectPart();
        secondary->attribs = secondaryAttribs;
        if (secondaryAttribs == NULL) {
            sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
            return;
        }
        secondary->attribs->kind = 0;
        secondary->attribs->subPriority = 8;
        secondary->attribs->shape = enabled;
        secondary->attribs->baseTile = gEffectGfxTable[state->animId].baseTile;
        secondary->attribs->tile0 = D_080CE84C[0];
        secondary->attribs->tile1 = D_080CE84C[1];
        secondary->attribs->tile2 = D_080CE84C[2];
        secondary->attribs->tile3 = D_080CE84C[3];
        secondary->attribs->extra = gEffectGfxTable[state->animId].extra;
        secondary->attribs->object = (u32)effectSprite;
        secondary->attribs->timer = 0;
    }
    if (*(u16 *)((u8 *)entity + 0x6C) & 0x20) {
        *(u16 *)(effectSprite + 2) |= 0x10;
    }
    *(u8 *)(effectSprite + 0x2A) &= 0xBF;
    sub_08023BDC((u8 *)entity, effectSprite);
    entity->flags |= 0x1000;
    *(u8 *)((u8 *)entity + 2 * entity->index + 0x19) = 0;
    {
        s32 *callbackTable = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callbackTable);
    }
}
