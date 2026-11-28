extern struct FixedEffectWorkspace gMainWorkspace;
extern u8 gCameraState[];
extern u8 gSpriteAnimDataTable[];
extern u8 *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void sub_0801C00C(void *);
extern void _call_via_r1(u8 *, s32);
typedef struct Rec_sub_0801BEA4_sprite
{
  u8 pad0[0x2];
  u16 m2;
  u8 pad4[0x10];
  u32 m14;
  u32 m18;
  u32 m1C;
  u8 pad20[0x4];
  u32 m24;
  u16 m28;
} Rec_sub_0801BEA4_sprite;
inline static u8 *inline_fn(u8 *arg0, struct FixedEffectState *arg1)
{
  return (arg0 + 4) + (arg1->kind * 0xC);
}

void sub_0801BEA4(struct FixedEffectEntity *entity)
{
  struct FixedEffectState *state;
  Rec_sub_0801BEA4_sprite *sprite;
  u8 *cameraState;
  s32 animSlot;
  u32 spriteAttr;
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    _call_via_r1((u8 *) entity, *((s32 *) (((u8 *) entity) + 0x24)));
    return;
  }
  entity->sprite = sprite;
  allocWorkSlot((u8 *) entity, 0, 0x34, 0);
  if (entity->state == NULL)
  {
    _call_via_r1((u8 *) entity, *((s32 *) (((u8 *) entity) + 0x24)));
    return;
  }
  state = entity->state;
  state->kind = SPRITE_KIND_KIND87_EFFECT;
  state->f18 = 1;
  state->worldX = entity->posX << 16;
  state->worldY = entity->posY << 16;
  animSlot = findKindIndex(SPRITE_KIND_KIND87_EFFECT);
  state->animSlot = animSlot;
  if ((animSlot << 16) < 0)
  {
    _call_via_r1((u8 *) entity, *((s32 *) (((u8 *) entity) + 0x24)));
    return;
  }
  spriteAttr = ((*((u16 *) sprite)) & 0xC00) | (((state->animSlot << 6) + 0x200) | ((animSlot + 8) << 12));
  *((u16 *) sprite) = spriteAttr;
  *((u16 *) sprite) = spriteAttr | gMainWorkspace.gfxFlags;
  sprite->m1C = ATTACK_EFFECT_GFX_ID;
  cameraState = (u8 *) (&gCameraState);
  {
    {
      u32 k = 0x1278;
      sprite->m14 = state->worldX - (((*((u32 *) ((cameraState + k) + ((gMainWorkspace.frameCounter + 1) << 6)))) + 0x8000) & 0xFFFF0000);
    }
  }
  {
    {
      u32 k = 0x127C;
      sprite->m18 = state->worldY - (((*((u32 *) ((cameraState + k) + ((gMainWorkspace.frameCounter + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
    }
  }
  if (entity->effectParam < 0)
  {
    sprite->m2 &= 0xFFEF;
  }
  else
  {
    sprite->m2 |= 0x10;
  }
  sprite->m24 = *((u32 *) inline_fn((u8 *) gSpriteAnimDataTable, state));
  sprite->m28 = 7;
  *((u16 *) sprite) = ((*((u16 *) sprite)) & 0xFFF) | 0xD000;
  entity->flags |= 0x1000;
  entity->flags |= 0x800;
  entity->scriptStep = 0;
  *((u32 *) (((u8 *) entity) + 0x14)) = (u32) sub_0801C00C;
}
