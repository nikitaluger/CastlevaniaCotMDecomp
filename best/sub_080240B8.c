extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s16);
extern void initSpriteGraphics(void *, void *, u8 *);
extern void *allocEffectPart(void);
extern void setAnimationFrame(s32, void *, u16, u8);
extern s32 sub_08013B38(void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
extern void sub_08024AD0(void);
extern u16 D_080CE8B4[];
extern volatile unsigned short D_080CE8C4[];
extern u16 D_080CE8CC[];
extern u16 D_080CE8D4[];
extern u16 D_080CE8DC[];
extern u8 gSpriteKindTable[];
extern u8 gSpriteAnimDataTable[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
inline static u8 *inline_fn(u8 *arg0)
{
  return arg0 + 0x18;
}

void sub_080240B8(u8 *entity)
{
  u8 *__base_gMainWorkspace;
  u8 *holder = *((u8 **) (entity + 0xac));
  u8 *kindTable;
  u8 *sprite;
  u8 *state;
  u8 *status;
  u8 *camera;
  u8 *part;
  volatile unsigned int __repair_result_slot;
  u32 attr;
  u32 *paramTable;
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    do
    {
      do
      {
        sub_080C31E0(entity, *((s32 *) (entity + 0x24)));
      }
      while (0);
    }
    while (0);
    return;
  }
  *((u8 **) (entity + 0x38)) = sprite;
  do
  {
    do
    {
      allocWorkSlot(entity, 0, 0x54, 0);
    }
    while (0);
  }
  while (0);
  state = *((u8 **) (entity + 0x3c));
  if (state == NULL)
  {
    do
    {
      do
      {
        sub_080C31E0(entity, *((s32 *) (entity + 0x24)));
      }
      while (0);
    }
    while (0);
    return;
  }
  status = state + 0x34;
  *((u32 *) (state + 0x24)) = *((u32 *) (entity + 0x24));
  *((u32 *) (entity + 0x24)) = (u32) sub_08024AD0;
  switch (*((s16 *) ((*((u8 **) (holder + 4))) + 4)))
  {
    case 0xA4:
      *((u16 *) (state + 0x1c)) = 0x45;
      break;

    case 0xA5:
      *((u16 *) (state + 0x1c)) = 0x46;
      break;

    case 0xA6:
      *((u16 *) (state + 0x1c)) = 0x47;
      break;

    case 0xA7:
      *((u16 *) (state + 0x1c)) = 0x81;
      break;

    default:
      break;

  }

  *((u32 *) inline_fn(state)) = *((s16 *) ((kindTable + ((*((s16 *) (state + 0x1c))) * 0x14)) + 2));
  *((u32 *) (state + 8)) = ((s32) (*((s16 *) ((*((u8 **) (holder + 4))) + 0)))) << 16;
  *((u32 *) (state + 0xc)) = ((s32) (*((s16 *) ((*((u8 **) (holder + 4))) + 2)))) << 16;
  __repair_result_slot = findKindIndex(*((s16 *) (state + 0x1c)));
  *((s16 *) (state + 0x22)) = __repair_result_slot;
  if (((s32) ((*((s16 *) (state + 0x22))) << 16)) < ((float) 0))
  {
    do
    {
      do
      {
        sub_080C31E0(entity, *((s32 *) (entity + 0x24)));
      }
      while (0);
    }
    while (0);
    return;
  }
  initSpriteGraphics(sprite, status, ((u8 *) gSpriteAnimDataTable) + ((*((s16 *) (state + 0x1c))) * 0xC));
  part = allocEffectPart();
  *((u8 **) (state + 0x28)) = part;
  if (part == NULL)
  {
    do
    {
      do
      {
        sub_080C31E0(entity, *((s32 *) (entity + 0x24)));
      }
      while (0);
    }
    while (0);
    return;
  }
  *((u8 *) ((*((u8 **) (state + 0x28))) + 1)) = 0;
  *((u8 *) ((*((u8 **) (state + 0x28))) + 2)) = 8;
  *((u8 *) ((*((u8 **) (state + 0x28))) + 3)) = 1;
  *((u16 *) ((*((u8 **) (state + 0x28))) + 4)) = *((u16 *) (kindTable + ((*((s16 *) (state + 0x1c))) * 0x14)));
  *((u16 *) ((*((u8 **) (state + 0x28))) + 6)) = D_080CE8B4[0];
  *((u16 *) ((*((u8 **) (state + 0x28))) + 8)) = D_080CE8B4[1];
  *((u16 *) ((*((u8 **) (state + 0x28))) + 0xa)) = D_080CE8B4[2];
  *((u16 *) ((*((u8 **) (state + 0x28))) + 0xc)) = D_080CE8B4[3];
  *((u16 *) ((*((u8 **) (state + 0x28))) + 0xe)) = *((u16 *) ((kindTable + ((*((s16 *) (state + 0x1c))) * 0x14)) + 4));
  *((u32 *) ((*((u8 **) (state + 0x28))) + 0x10)) = (u32) sprite;
  *((u16 *) ((*((u8 **) (state + 0x28))) + 0x14)) = 0;
  attr = ((*((u16 *) sprite)) & 0xC00) | ((((*((s16 *) (state + 0x22))) << 6) + 0x200) | (((*((u16 *) (state + 0x22))) + 8) << 12));
  __base_gMainWorkspace = gMainWorkspace;
  attr |= *((u16 *) (__base_gMainWorkspace + 0x18c2));
  *((u16 *) sprite) = attr;
  *((u32 *) inline_fn(state)) = 0x8000000A;
  camera = gCameraState;
  {
    u32 off = ((u32) ((*((u8 *) (__base_gMainWorkspace + 0x18a8))) + 1)) << 6;
    *((u32 *) (sprite + 0x14)) = (*((u32 *) (state + 8))) - (((*((u32 *) ((camera + 0x1278) + off))) + 0x8000) & 0xFFFF0000);
    *((u32 *) (sprite + 0x18)) = (*((u32 *) (state + 0xc))) - (((*((u32 *) ((camera + 0x127c) + (((u32) ((*((u8 *) (__base_gMainWorkspace + 0x18a8))) + 1)) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  *((u16 *) (state + 0x4a)) = 1;
  switch (*((s16 *) (state + 0x1c)))
  {
    case 0x45:
      *((u32 **) (state + 8)) = (u32 *) D_080CE8C4;
      break;

    case 0x46:
      *((u32 **) (state + 8)) = (u32 *) D_080CE8CC;
      break;

    case 0x47:
      *((u32 **) (state + 8)) = (u32 *) D_080CE8D4;
      break;

    case 0x81:
      *((u32 **) (state + 8)) = (u32 *) D_080CE8DC;
      break;

    default:
      break;

  }

  paramTable = (u32 *) (state + 8);
  attr = *((s16 *) paramTable);
  *((s16 *) (state + 0x4c)) = attr / 4;
  do
  {
    do
    {
      setAnimationFrame(entity, status, 0, 1);
    }
    while (0);
  }
  while (0);
  if (((sub_08013B38(paramTable) + 1) - 1) <= (0 - 1))
  {
    *((u16 *) (sprite + 2)) |= 0x10;
  }
  else
  {
    *((u16 *) (sprite + 2)) &= 0xFFEF;
  }
  do
  {
    do
    {
      sub_080C31E0(entity, 0);
    }
    while (0);
  }
  while (0);
  {
    u16 __repair_narrow = *((u32 *) (__base_gMainWorkspace + 0x18c2));
    *((u16 *) sprite) = __repair_narrow;
  }
  {
    unsigned int idx = *((s16 *) (entity + 0x22));
    *((u8 *) ((entity + (2 * idx)) + 0x19)) = 0;
    {
      u32 *cb = (u32 *) 0x08671BB0;
      do
      {
        do
        {
          sub_080C31E4(inline_fn(entity), entity + 0x22, *cb);
        }
        while (0);
      }
      while (0);
    }
    idx = *((s16 *) (entity + 0x22));
    *((u8 *) ((entity + (2 * idx)) + 0x19)) += 1;
    {
      u8 cmd = *(inline_fn(entity) + (2 * idx));
      ((void (**)(u8 *)) (*((u32 *) (entity + 0x14))))[cmd](entity);
    }
  }
}

