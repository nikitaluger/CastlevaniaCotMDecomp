extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void setSpriteFlipForDirection(u8 *);
extern void sub_0804EE74(void);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

struct SubEffect {
    u8 mode; u8 kind; u8 layer; u8 priority;
    u16 gfxIndex; u16 anim0; u16 anim1; u16 anim2; u16 anim3; u16 palette;
    u32 object; u16 timer;
};
struct Part {
    u8 _0[8]; s32 x; s32 y; u32 f10; u32 f14; u32 state;
    s16 kind; u8 _1E[4]; s16 slot; u32 script; struct SubEffect *effect;
};
struct Entity {
    u8 _0[2]; u16 flags; u8 _4[0x22-4]; s16 step; u8 _24[0x38-0x24];
    u8 *sprite; struct Part *part; u8 _40[0x4C-0x40]; s16 spawnX; u8 _4E[6];
    s16 spawnY; u8 _56[0x5C-0x56]; u32 radiusA; u8 _60[0x6C-0x60]; u32 radiusB;
};
struct GameState { u8 _0[0x18A8]; u8 frameCounter; u8 _18A9[0x19]; u16 renderFlags; };
extern struct GameState gMainWorkspace;
struct CameraState { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct CameraState gCameraState;
struct EffectGfxEntry { u8 _0[4]; u16 gfxIndex; u16 palette; u8 _8[0x28-8]; };
extern struct EffectGfxEntry gEffectGfxTable[];
extern u16 D_080CFA44[];
extern u8 gSpriteAnimDataTable[];

/* Spawn the kind-0x5D effect sprite for an entity, building its render layer
 * from the fixed effect tables and advancing the entity's script step. */
void sub_0804EADC(struct Entity *entity) {
    u8 *sprite;
    struct Part *part;
    u8 *anim;
    u8 *effectBytes;
    s32 animSlot;
    u32 graphics;
    u32 zero;
    u8 *coordBase;
    s32 *stepTable;

    sprite = allocSpriteObject();
    part = NULL;
    anim = NULL;
    animSlot = 0;
    if ((sprite == NULL) ||
        (entity->sprite = sprite, allocWorkSlot((u8 *)entity, 0, 0x48, 0), part = entity->part, part == NULL) ||
        (anim = (u8 *)part + 0x34, part->script = *(u32 *)((u8 *)entity + 0x24), *(u32 *)((u8 *)entity + 0x24) = (u32)sub_0804EE74,
         part->kind = 0x5D, part->state = 1,
         part->x = entity->spawnX << 16, part->y = entity->spawnY << 16,
         animSlot = findKindIndex(0x5D), part->slot = animSlot, ((s32)(animSlot << 16) < 0)) ||
        (initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + part->kind * 0xC), effectBytes = allocEffectPart(), part->effect = (struct SubEffect *)effectBytes, effectBytes == NULL)) {
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    zero = 0;
    part->effect->kind = zero;
    part->effect->layer = 8;
    part->effect->priority = 1;
    part->effect->gfxIndex = gEffectGfxTable[part->kind].gfxIndex;
    part->effect->anim0 = D_080CFA44[0];
    part->effect->anim1 = D_080CFA44[1];
    part->effect->anim2 = D_080CFA44[2];
    part->effect->anim3 = D_080CFA44[3];
    part->effect->palette = gEffectGfxTable[part->kind].palette;
    part->effect->object = (u32)sprite;
    part->effect->timer = zero;
    graphics = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)part + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)part + 0x22) + 8) << 12));
    *(u16 *)sprite = graphics;
    *(u16 *)sprite = graphics | gMainWorkspace.renderFlags;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    coordBase = (u8 *)&gCameraState;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = part->x - ((*(u32 *)(coordBase + k + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = part->y - ((*(u32 *)(coordBase + k + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    part->f10 = entity->radiusA;
    part->f14 = entity->radiusB;
    setSpriteFlipForDirection(sprite);
    setAnimationFrame(sprite, anim, 0x07, 0x01);
    entity->flags |= 0x1000;
    *(u8 *)((u8 *)entity + 2 * entity->step + 0x19) = zero;
    stepTable = (s32 *)0x08671BB0;
    _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, *stepTable);
}
