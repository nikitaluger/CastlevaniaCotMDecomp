extern void *sub_0800355C(void);
extern void sub_080168C(void *, s32, s32, s32);
extern s16 sub_08013C2C(s32);
extern void sub_0801131C(void *, void *, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_080428B8(void);
extern u16 gSpriteAnimDataTable[];
extern u16 gEffectGfxTable[];
extern u16 gSpriteKindTable[];
extern u16 gMainWorkspace[];
extern u8 gCameraState[];
extern u32 gMainObjTimerCallbacks[];
extern u32 D_080CF4FC[];
extern u32 D_080CF52C[];
extern u32 D_080CF538[];
void sub_0804225C(u8 *entity)
{
  u8 *__base_gSpriteKindTable;
  s32 sum;
  s32 sum_arm;
  u8 *params = *((u8 **) (entity + 0xAC));
  u8 *coord;
  u8 *sprite = sub_0800355C();
  u8 *work;
  u8 *gfxInit;
  u8 *layer;
  u32 attrs;
  u32 zero;
  u32 one;
  u8 *camera;
  u32 idx;
  if (sprite == NULL)
  {
    goto fail;
  }
  *((u8 **) (entity + 0x38)) = sprite;
  sub_080168C(entity, 0, 0x5C, 0);
  work = *((u8 **) (entity + 0x3C));
  if (work == NULL)
  {
    goto fail;
  }
  gfxInit = work + 0x34;
  sum = work + 0x24;
  *((u8 **) sum) = *((u8 **) (entity + 0x24));
  *((u32 *) (entity + 0x24)) = (u32) sub_080428B8;
  coord = *((u8 **) (params + 4));
  switch (*((s16 *) (coord + 4)))
  {
    sum_arm = work + 0x1C;
    case 0x10F:
      *((s16 *) sum_arm) = 0x42;
      break;

    case 0x115:
      *((s16 *) (work + 0x1C)) = 0x43;
      break;

  }

  __base_gSpriteKindTable = gSpriteKindTable;
  *((s32 *) (work + 0x18)) = *((s16 *) ((__base_gSpriteKindTable + ((*((s16 *) (work + 0x1C))) * 20)) + 2));
  *((s32 *) (work + 8)) = ((s32) (*((s16 *) (coord + 0)))) << 16;
  *((s32 *) (work + 0xC)) = ((s32) (*((s16 *) (coord + 2)))) << 16;
  *((s16 *) (work + 0x22)) = sub_08013C2C(*((s16 *) (work + 0x1C)));
  if ((sub_08013C2C(*((s16 *) (work + 0x1C))) << 16) < 0)
  {
    goto fail;
  }
  sub_0801131C(sprite, gfxInit, 0x080CF4FC + ((*((s16 *) (work + 0x1C))) * 12));
  layer = sub_08016190();
  *((u8 **) (work + 0x28)) = layer;
  if (layer == NULL)
  {
    goto fail;
  }
  zero = 0;
  layer[1] = zero;
  layer[2] = 8;
  one = 1;
  layer[3] = one;
  __base_gSpriteKindTable = gEffectGfxTable;
  *((u16 *) (layer + 4)) = *((u16 *) ((__base_gSpriteKindTable + ((*((s16 *) (work + 0x1C))) * 20)) + 4));
  *((u16 *) (layer + 6)) = gSpriteAnimDataTable[0];
  *((u16 *) (layer + 8)) = gSpriteAnimDataTable[1];
  *((u16 *) (layer + 0xA)) = gSpriteAnimDataTable[2];
  *((u16 *) (layer + 0xC)) = gSpriteAnimDataTable[3];
  *((u16 *) (layer + 0xE)) = *((u16 *) ((__base_gSpriteKindTable + ((*((s16 *) (work + 0x1C))) * 20)) + 6));
  *((u8 **) (layer + 0x10)) = sprite;
  *((u16 *) (layer + 0x14)) = 0;
  attrs = ((*((u16 *) sprite)) & 0xC00) | ((((*((s16 *) (work + 0x22))) << 6) + 0x200) | (((*((u16 *) (work + 0x22))) + 8) << 12));
  *((u16 *) sprite) = attrs;
  *((u16 *) sprite) = attrs | gMainWorkspace[0x18C2 / 2];
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  camera = gCameraState;
  idx = ((u32) ((*((u8 *) (gMainWorkspace + 0x18A8))) + 1)) << 6;
  *((u32 *) (sprite + 0x14)) = (*((s32 *) (work + 8))) - (((*((u32 *) ((camera + 0x1278) + idx))) + 0x8000) & 0xFFFF0000);
  idx = ((u32) ((*((u8 *) (gMainWorkspace + 0x18A8))) + 1)) << 6;
  *((u32 *) (sprite + 0x18)) = (*((s32 *) (work + 0xC))) - (((*((u32 *) ((camera + 0x127C) + idx))) + 0xFFFF8000) & 0xFFFF0000);
  coord = work + 0x48;
  if ((*((s16 *) (work + 0x1C))) == 0x42)
  {
    *((u32 *) (coord + 0x10)) = (u32) D_080CF52C;
  }
  else
  {
    *((u32 *) D_080CF538) = (u32) D_080CF538;
  }
  *((u16 *) (coord + 0)) = 0;
  *((u16 *) (coord + 4)) = one;
  *((u8 **) (coord + 8)) = sub_08016190();
  if ((*((u8 **) (coord + 8))) == NULL)
  {
    goto fail;
  }
  layer = *((u8 **) (coord + 8));
  layer[1] = 0;
  layer[3] = one;
  layer[2] = 8;
  *((u16 *) (layer + 4)) = *((u16 *) ((__base_gSpriteKindTable + ((*((s16 *) (work + 0x1C))) * 20)) + 4));
  *((u16 *) (layer + 6)) = gSpriteAnimDataTable[0];
  *((u16 *) (layer + 8)) = gSpriteAnimDataTable[1];
  *((u16 *) (layer + 0xA)) = gSpriteAnimDataTable[2];
  *((u16 *) (layer + 0xC)) = gSpriteAnimDataTable[3];
  *((u16 *) (layer + 0xE)) = *((u16 *) ((__base_gSpriteKindTable + ((*((s16 *) (work + 0x1C))) * 20)) + 6));
  *((u8 **) (layer + 0x10)) = sprite;
  *((u16 *) (layer + 0x14)) = 0;
  sub_08011368(entity, gfxInit, 0, 1);
  sub_08042900(entity, work);
  sub_080145A4(entity, work, coord, 0xB4);
  sub_08016664(entity, 0);
  *((u16 *) (entity + 2)) = (*((u16 *) (entity + 2))) | 0x1000;
  {
    u8 *p = entity + ((*((s16 *) (entity + 0x22))) * 2);
    *((u8 *) (p + 0x19)) = zero;
  }
  sub_080C31E4(entity + 0x18, entity + 0x22, D_080CF538[0]);
  {
    u8 *p = entity + ((*((s16 *) (entity + 0x22))) * 2);
    *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19)) = (*((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19))) + 1;
  }
  {
    u8 *p = (entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x18;
    u32 off = *((u8 *) p);
    sub_080C31E0(entity, *((u32 *) (((u8 *) (*((u32 *) (entity + 0x14)))) + (off * 4))));
  }
  return;
  fail:
  sub_080C31E0(entity, *((u32 *) (entity + 0x24)));

}
