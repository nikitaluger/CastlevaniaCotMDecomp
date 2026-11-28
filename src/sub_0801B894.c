/* twin of sub_080180F0 (both matched) */
void setAnimationFrame(void *, void *, s32, s32);
s32 getSpriteFacingSign(s32);
void sub_0801D618(s32, s32, s32, s32);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, s32);
s32 signedRemainder(s16, s32);

/* Every six ticks spawns projectile 0x92 on either side of the parent,
 * aiming it by a counter, then advances the counters and dispatches. */
void sub_0801B894(u8 *entity)
{
  s32 parent;
  u8 *obj;
  u8 *animObj;
  u8 *spawnState;
  s16 angleIndex;
  s32 *dispatchPtr;
  int zero;
  u32 *divisor;
  u8 *spawnX;
  u8 *spawnY;
  u32 spawnZ;
  u32 t;
  parent = *((s32 *) (entity + 0x38));
  obj = *((u8 **) (entity + 0x3C));
  animObj = obj + 0x34;
  spawnState = obj + 0x48;
  setAnimationFrame((void *) parent, animObj, 9, 0);
  if ((signedRemainder((s16) (*((s16 *) (spawnState + 0x16))), 6) << 16) == 0)
  {
    zero = 0;
    if (getSpriteFacingSign(parent) < zero)
    {
      spawnX = (*((u8 **) (obj + 0x08))) + 0xFFE00000;
      spawnY = (*((u8 **) (obj + 0x0C))) + 0xFFD80000;
      spawnZ = 0xFFFE4000;
    }
    else
    {
      spawnX = (*((u8 **) (obj + 0x08))) + 0x200000;
      spawnY = (*((u8 **) (obj + 0x0C))) + 0xFFD80000;
      spawnZ = 0x1C000;
    }
    divisor = (u32 *) 0x08671BFC;
    if (spawnState)
    {
      angleIndex = *((s16 *) (spawnState + 0x18));
      t = sub_080C31E0(((s32) angleIndex) << 12, *divisor) * 3;
      t += t >> 31;
      sub_0801D618((s32) spawnX, (s32) spawnY, spawnZ, (s32) t >> 1);
      *((u16 *) (spawnState + 0x18)) = (u16) ((*((u16 *) (spawnState + 0x18))) + 1);
    }
    else
    {
      angleIndex = *((s16 *) (spawnState + 0x18));
      t = sub_080C31E0(((s32) angleIndex) << 12, *divisor) * 3;
      t += t >> 31;
      sub_0801D618((s32) spawnX, (s32) spawnY, spawnZ, (s32) t >> 1);
      *((u16 *) (spawnState + 0x18)) = (u16) ((*((u16 *) (spawnState + 0x18))) + 1);
    }
  }
  *((u16 *) (spawnState + 0x16)) = (u16) ((*((u16 *) (spawnState + 0x16))) + 1);
  if (((s32) (*((s16 *) (spawnState + 0x18)))) > 0x13)
  {
    u8 *p2 = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
    *((u8 *) (p2 + 0x19)) = zero;
    dispatchPtr = (s32 *) 0x08671BB0;
    {
      s32 *nv = dispatchPtr;
      sub_080C31E4(entity + 0x18, entity + 0x22, *nv);
    }
  }
}
