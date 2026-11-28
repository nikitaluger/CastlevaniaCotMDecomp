extern u8 gMainWorkspace[];
extern void *spawnBudgetedEffect(u32 arg0, s32 effect);
extern s32 getSpriteFacingSign(void *sprite);
extern s32 signOf(s32 value);
extern s32 absXFromFocus(s32 x);
extern s32 absYFromFocus(s32 y);
extern s32 sub_08014964(s32);
extern s32 divInt32(s32 num, s32 den);
extern s32 scaleByRandom(u32 arg);
extern void sub_080C31E8(void *, void *, s32);
extern u8 gMainObjTimerCallbacks[];

void sub_0802B840(u8 *self)
{
  u8 *sprite;
  u8 *actor;
  u8 *base;
  void *effect;
  s32 facing;
  s32 sign;
  s32 x;
  s32 y;
  
  s32 absy;
  s32 r2;
  
  s32 ax;
  s32 ay;
  s16 val;
  u8 *step;
  u8 *kind;

  sprite = *((u8 **) (self + 0x38));
  actor = *((u8 **) (self + 0x3C));
  kind = actor + 0x34;
  if (kind[1] != 3)
  {
    return;
  }
  base = gMainWorkspace;
  effect = spawnBudgetedEffect(*((u32 *) (base + 0x1870)), 0xC5);
  if (effect != 0)
  {
    facing = getSpriteFacingSign(sprite);
    sign = signOf(*((s32 *) (actor + 8)));
    { s32 raw;
      raw = absXFromFocus(*((s32 *) (actor + 8)));
      x = raw < 0 ? (raw + 0xFFFF) >> 16 : raw >> 16;
      raw = absYFromFocus(*((s32 *) (actor + 0xC)));
      y = raw < 0 ? (raw + 0xFFFF) >> 16 : raw >> 16;
    }
    if (x > 0xA0)
    {
      x = 0xA0;
    }
    if (y > 0x78)
    {
      y = 0x78;
    }
    if (sign == facing)
    {
      sign = divInt32(x << 17, 0x60);
    }
    else
    {
      sign = scaleByRandom(0x1001);
      absy = sub_08014964(*((s32 *) (actor + 0xC)));
      if (absy < 0)
      {
        absy = x + y;
        if (absy < 0)
        {
          absy += 0x7F;
        }
        absy >>= 7;
        absy <<= 16;
        r2 = absy + 0x20000;
      }
      else
      {
        r2 = 0x20000;
      }
      if (facing > 0)
      {
        u8 *e = (u8 *) effect;
        ax = (*((s32 *) (actor + 8)) + 0xFFFF) >> 16;
        ax += 0x0E;
        *((s16 *) (e + 0x4C)) = (s16) ax;
        *((s32 *) (e + 0x5C)) = sign;
        ay = *((s32 *) (actor + 0x0C));
        if (ay < 0)
        {
          ay += 0xFFFF;
        }
        ay >>= 16;
        ay -= 0x18;
        *((s16 *) (e + 0x54)) = (s16) ay;
        *((s32 *) (e + 0x6C)) = -r2;
        val = *((s16 *) (actor + 0x1C));
        *((s16 *) (e + 0x7C)) = val;
      }
      else
      {
        u8 *e = (u8 *) effect;
        ax = *((s32 *) (actor + 8));
        if (ax < 0)
        {
          ax += 0xFFFF;
        }
        ax >>= 16;
        ax -= 0x0E;
        *((s16 *) (e + 0x4C)) = (s16) ax;
        *((s32 *) (e + 0x5C)) = -sign;
        ay = *((s32 *) (actor + 0x0C));
        if (ay < 0)
        {
          ay += 0xFFFF;
        }
        ay >>= 16;
        ay -= 0x18;
        *((s16 *) (e + 0x54)) = (s16) ay;
        *((s32 *) (e + 0x6C)) = -r2;
        val = *((s16 *) (actor + 0x1C));
        *((s16 *) (e + 0x7C)) = val;
      }
    }
  }
  step = self + (2 * *((s16 *) (self + 0x22)));
  *((u8 *) (step + 0x19)) = 0;
  { s32 **slot = (s32 **) 0x08671BB0; sub_080C31E8(self + 0x18, self + 0x22, *slot); }
}
