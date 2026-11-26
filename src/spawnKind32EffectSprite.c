extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void registerScriptObject(u8 *, s32);
extern void sub_08058978(u8 *, struct Part *);
extern void updateKind32Effect(void);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

/* Render layer allocated from the effect pool. */
struct SubEffect {
    u8 mode; u8 kind; u8 layer; u8 priority;
    u16 gfxIndex; u16 anim0; u16 anim1; u16 anim2; u16 anim3; u16 palette;
    u32 object; u16 timer;
};
/* Effect work state carried on the entity at +0x3C. */
struct Part {
    u8 _0[8]; s32 worldX; s32 worldY; u32 radiusA; u32 radiusB; u32 state;
    s16 kind; u8 _1E[4]; s16 slot; u32 updateCb; struct SubEffect *effect;
};
/* Parent entity that requested the effect. */
struct Entity {
    u8 _0[2];
    u16 flags;                  /* 0x02 */
    u8 _4[0x22-4];
    s16 step;                   /* 0x22 */
    u8 _24[0x38-0x24];
    u8 *sprite;                 /* 0x38 */
    struct Part *part;          /* 0x3C */
    u8 _40[0x4C-0x40];
    s16 spawnX;                 /* 0x4C */
    u8 _4E[6];
    s16 spawnY;                 /* 0x54 */
    u8 _56[0x5C-0x56];
    u32 radiusA;                /* 0x5C */
    u8 _60[0x6C-0x60];
    u32 radiusB;                /* 0x6C */
};
struct GameState { u8 _0[0x18A8]; u8 frameCounter; u8 _18A9[0x19]; u16 renderFlags; };
extern struct GameState gMainWorkspace;
struct CameraState { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct CameraState gCameraState;
struct EffectGfxEntry { u8 _0[4]; u16 gfxIndex; u16 palette; u8 _8[0x28-8]; };
extern struct EffectGfxEntry gEffectGfxTable[];
extern u16 gKind32LayerAttrs[];
extern u8 gSpriteAnimDataTable[];

/* Spawn an animated kind-0x32 effect sprite for the entity: allocate the sprite
 * and render layer, set up the animation from fixed tables, place it relative to
 * the camera scroll, then advance the entity's script step. The chained
 * condition keeps the original short-circuit order of the allocation checks. */
void spawnKind32EffectSprite(struct Entity *entity) {
    u8 *sprite;
    struct Part *part;
    u8 *anim;
    u8 *effectData;
    s32 animSlot;
    u32 oamFlags;
    u32 zeroByte;
    u8 *camera;
    s32 *scriptOps;

    sprite = allocSpriteObject();
    part = NULL;
    anim = NULL;
    animSlot = 0;
    if ((sprite == NULL) ||
        (entity->sprite = sprite, allocWorkSlot((u8 *)entity, 0, 0x48, 0), part = entity->part, part == NULL) ||
        (anim = (u8 *)part + 0x34, part->updateCb = *(u32 *)((u8 *)entity + 0x24), *(u32 *)((u8 *)entity + 0x24) = (u32)updateKind32Effect,
         part->kind = 0x32, part->state = 1,
         part->worldX = entity->spawnX << 16, part->worldY = entity->spawnY << 16,
         animSlot = findKindIndex(0x32), part->slot = animSlot, ((s32)(animSlot << 16) < 0)) ||
        (initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + part->kind * 0xC), effectData = allocEffectPart(), part->effect = (struct SubEffect *)effectData, effectData == NULL)) {
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    zeroByte = 0;
    part->effect->kind = zeroByte;
    part->effect->layer = 8;
    part->effect->priority = 1;
    part->effect->gfxIndex = gEffectGfxTable[part->kind].gfxIndex;
    part->effect->anim0 = gKind32LayerAttrs[0];
    part->effect->anim1 = gKind32LayerAttrs[1];
    part->effect->anim2 = gKind32LayerAttrs[2];
    part->effect->anim3 = gKind32LayerAttrs[3];
    part->effect->palette = gEffectGfxTable[part->kind].palette;
    part->effect->object = (u32)sprite;
    part->effect->timer = zeroByte;
    oamFlags = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)part + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)part + 0x22) + 8) << 12));
    *(u16 *)sprite = oamFlags;
    *(u16 *)sprite = oamFlags | gMainWorkspace.renderFlags;
    *(u32 *)(sprite + 0x1C) = 0x8000000B;
    camera = (u8 *)&gCameraState;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = part->worldX - ((*(u32 *)(camera + k + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = part->worldY - ((*(u32 *)(camera + k + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    part->radiusA = entity->radiusA;
    part->radiusB = entity->radiusB;
    setAnimationFrame(sprite, anim, 0x05, 0x01);
    sub_08058978(sprite, part);
    registerScriptObject((u8 *)entity, 0);
    entity->flags |= 0x1000;
    *(u8 *)((u8 *)entity + 2 * entity->step + 0x19) = zeroByte;
    scriptOps = (s32 *)0x08671BB0;
    _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, *scriptOps);
}
