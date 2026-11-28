extern s32 isOutsideCameraBounds(s32, s32);
extern s32 sub_08014090(s32);
extern s32 scaleByRandom(s32);
extern s32 sub_08016830(s32);
extern s32 absXFromFocus(s32);
extern void *spawnBudgetedEffect(s32);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern s32 sub_0805F9B4(s32, s32);
extern void *sub_0805FAEC(void *, s32);
void sub_0802A974(void *entity)
{
  u8 *self = (u8 *) entity;
  void *source = *((void **) (self + 0xAC));
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *srcObj = *((u8 **) (((u8 *) source) + 4));
  s32 x;
  s32 y;
  s32 kind;
  s32 r8;
  x = (*((s16 *) srcObj)) << 16;
  y = (*(((s16 *) srcObj) + 1)) << 16;
  if (isOutsideCameraBounds(x, y) == ((long) 1))
  {
    (*((void (**)(void *)) (self + 0x24)))(entity);
    return;
  }
  if (sub_08014090(*((s16 *) work)) == 1)
  {
    return;
  }
  *((s16 *) ((*((u8 **) (self + 0x3C))) + 2)) = (*((s16 *) (work + 2))) - 1;
  do
  {
    if ((*((s16 *) (work + 2))) > 0)
    {
      return;
    }
  }
  while (0);
  *((s16 *) (work + 2)) = (s16) (scaleByRandom(0x3D) + 0xB4);
  kind = *((s16 *) (srcObj + 4));
  switch (kind)
  {
    case 0xBE:
      r8 = 0xBB;
      break;

    case 0xBF:
      r8 = 0xBC;
      break;

    case 0xC0:
      r8 = 0xBD;
      break;

    default:
      r8 = 0;
      break;

  }

  if (sub_08016830((s16) r8) > 6)
  {
    return;
  }
  {
    s32 ax = (*((s16 *) srcObj)) << 16;
    s32 dist = absXFromFocus(ax);
    if (((u32) (dist + 0xFFC40000)) > 0x003C0000)
    {
      s16 t = *((s16 *) (work + 2));
      if (t < 0)
      {
        r8 = t + 7;
        *((s16 *) (work + 2)) = r8 >> 3;
      }
      return;
    }
  }
  {
    void *spawned;
    u8 *sp;
    u8 *sp_b1;
    s32 sb = 0;
    s32 kind2 = *((s16 *) (srcObj + 4));
    switch (kind2)
    {
      case 0xBE:
        spawned = spawnBudgetedEffect(0xBB);
        do
      {
        sb = 0;
        break;
      }
      while (0);

      case 0xBF:
        spawned = spawnBudgetedEffect(0xBC);
        sb = 1;
        break;

      case 0xC0:
        spawned = spawnBudgetedEffect(0xBD);
        sb = 2;
        break;

      default:
        spawned = 0;
        break;

    }

    if (spawned == 0)
    {
      return;
    }
    allocWorkSlot(spawned, 0, 8, 7);
    sp = *((u8 **) (((u8 *) spawned) + 0xAC));
    if (sp == 0)
    {
      sub_080C31E0(spawned, *((void **) (((u8 *) spawned) + 0x24)));
      return;
    }
    *((s16 *) sp_b1) = 0;
    *((u32 *) (sp_b1 + 4)) = (u32) (0x08671BB0 + (sb * 12));
    do
    {
      {
        s32 sx = (*((s16 *) srcObj)) << 16;
        u32 *cam = (u32 *) 0x02025FF0;
        if (sx <= (cam[0x1728 / 4] - 1))
        {
          u8 frame = *((u8 *) (((u8 *) 0x02025FF0) + 0x18A8));
          u32 *scroll = (u32 *) ((((u8 *) 0x02021E90) + 0x1278) + ((frame + 1) << 6));
          *((u32 *) (((u8 *) spawned) + 0x4C)) = scroll[0] + 0x1E8000;
        }
        else
        {
          u8 frame = *((u8 *) (((u8 *) 0x02025FF0) + 0x18A8));
          u32 *scroll = (u32 *) ((((u8 *) 0x02021E90) + 0x1278) + ((frame + 1) << 6));
          *((u32 *) (((u8 *) spawned) + 0x4C)) = scroll[0] - 0x8000;
        }
        *((u32 *) (((u8 *) spawned) + 0x54)) = scaleByRandom(0x5B) + ((u8 *) 0x02021E90)[0x127C];
      }
    }
    while (0);
  }
}

