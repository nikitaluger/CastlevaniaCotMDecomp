extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void sub_08019ED4(u8 *, u8 *);
extern void sub_08019E54(void);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

/* Small sub-effect allocated from the effect pool. */
struct SubEffect { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; u16 f14; };
/* Effect part on the entity; fields are named by their byte offset. */
struct Part { u8 _0[8]; s32 x; s32 y; u32 f10; u32 f14; u32 f18; s16 animId; u8 _1E[4]; s16 animSlot; u32 script; struct SubEffect *effect; };
/* Parent entity; fields are named by their byte offset. */
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
    u32 x;                      /* 0x5C */
    u8 _60[0x6C-0x60];
    u32 y;                      /* 0x6C */
};
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 gCameraState;
struct TBL { u8 _0[0x10]; u16 f10; u16 f12; u8 _14[0x28-0x14]; };
extern struct TBL gEffectGfxTable[];
extern u16 D_080CE5E8[];
extern u8 gSpriteAnimDataTable[];

/* Spawn an animated effect sprite for the entity: allocate the sprite and
 * sub-effect, set up the animation from the fixed tables, place it relative to
 * the camera, then advance the entity's animation step. The chained condition
 * keeps the original short-circuit order of the allocation and setup checks. */
void sub_08019A80(struct Entity *entity) {
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
        (entity->sprite = sprite, allocWorkSlot((u8 *)entity, 0, 0x4C, 0), part = entity->part, part == NULL) ||
        (anim = (u8 *)part + 0x34, part->script = *(u32 *)((u8 *)entity + 0x24), *(u32 *)((u8 *)entity + 0x24) = (u32)sub_08019E54,
         part->animId = 0x55, part->f18 = 1,
         part->x = entity->spawnX << 16, part->y = entity->spawnY << 16,
         animSlot = findKindIndex(0x55), part->animSlot = animSlot, ((s32)(animSlot << 16) < 0)) ||
        (initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + part->animId * 0xC), effectBytes = allocEffectPart(), part->effect = (struct SubEffect *)effectBytes, effectBytes == NULL)) {
        _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    zero = 0;
    part->effect->f1 = zero;
    part->effect->f2 = 8;
    part->effect->f3 = 1;
    part->effect->f4 = gEffectGfxTable[part->animId].f10;
    part->effect->f6 = D_080CE5E8[0];
    part->effect->f8 = D_080CE5E8[1];
    part->effect->fA = D_080CE5E8[2];
    part->effect->fC = D_080CE5E8[3];
    part->effect->fE = gEffectGfxTable[part->animId].f12;
    part->effect->f10 = (u32)sprite;
    part->effect->f14 = zero;
    graphics = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)part + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)part + 0x22) + 8) << 12));
    *(u16 *)sprite = graphics;
    *(u16 *)sprite = graphics | gMainWorkspace.f18C2;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    coordBase = (u8 *)&gCameraState;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = part->x - ((*(u32 *)(coordBase + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = part->y - ((*(u32 *)(coordBase + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    part->f10 = entity->x;
    part->f14 = entity->y;
    setAnimationFrame(sprite, anim, 0x1A, 0);
    sub_08019ED4((u8 *)entity, sprite);
    entity->flags |= 0x1000;
    *(u8 *)((u8 *)entity + 2 * entity->step + 0x19) = zero;
    stepTable = (s32 *)0x08671BB0;
    _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, *stepTable);
}
