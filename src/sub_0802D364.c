extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_0802D658(void);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

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
    s16 extraFlag;              /* 0x5C */
    u8 _5E[0x6C-0x5E];
    u16 animId;                 /* 0x6C */
};
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 D_02025FF0;
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 D_02021E90;
struct TBL { u8 _0[4]; u16 f4; u16 f6; u8 _8[0x28-8]; };
extern struct TBL D_080CBDD0[];
extern u16 D_080CEA70[];
extern u8 D_080CD400[];
extern u32 D_08671BB0;

/* Spawn an animated effect sprite for the entity: allocate the sprite and
 * sub-effect, set up the animation from the fixed tables, place it relative to
 * the camera, then advance the entity's animation step. */
void sub_0802D364(struct Entity *entity) {
    u8 *sprite;
    struct Part *part;
    u8 *anim;
    u8 *effectBytes;
    s32 animSlot;
    u32 graphics;
    u32 zero;
    u32 one;
    u8 *coordBase;
    s32 *stepTable;

    sprite = sub_0800355C();
    if (sprite == NULL) goto fail;
    entity->sprite = sprite;
    sub_0800168C((u8 *)entity, 0, 0x48, 0);
    part = entity->part;
    if (part == NULL) goto fail;
    anim = (u8 *)part + 0x34;
    part->script = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)sub_0802D658;
    part->animId = entity->animId;
    zero = 0;
    one = 1;
    part->f18 = one;
    part->x = entity->spawnX << 16;
    part->y = entity->spawnY << 16;
    animSlot = sub_08013C2C(part->animId);
    part->animSlot = animSlot;
    if ((animSlot << 16) < 0) goto fail;
    sub_0801131C(sprite, anim, (s32)D_080CD400 + part->animId * 0xC);
    effectBytes = sub_08016190();
    part->effect = (struct SubEffect *)effectBytes;
    if (effectBytes == NULL) goto fail;
    goto body;
fail:
    sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
    return;
body:
    part->effect->f1 = zero;
    part->effect->f2 = 8;
    part->effect->f3 = one;
    part->effect->f4 = D_080CBDD0[part->animId].f4;
    part->effect->f6 = D_080CEA70[0];
    part->effect->f8 = D_080CEA70[1];
    part->effect->fA = D_080CEA70[2];
    part->effect->fC = D_080CEA70[3];
    part->effect->fE = D_080CBDD0[part->animId].f6;
    part->effect->f10 = (u32)sprite;
    part->effect->f14 = zero;
    graphics = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)part + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)part + 0x22) + 8) << 12));
    *(u16 *)sprite = graphics;
    *(u16 *)sprite = graphics | D_02025FF0.f18C2;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    coordBase = (u8 *)&D_02021E90;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = part->x - ((*(u32 *)(coordBase + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = part->y - ((*(u32 *)(coordBase + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    if (entity->extraFlag > 0) *(u16 *)(sprite + 2) |= 0x10;
    *(u16 *)(sprite + 0x28) = 0x2C;
    entity->flags |= 0x1000;
    *(u8 *)((u8 *)entity + 2 * entity->step + 0x19) = zero;
    stepTable = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *stepTable);
}
