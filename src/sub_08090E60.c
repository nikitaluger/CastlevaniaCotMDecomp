extern s32 sub_08005820(s32);
extern s32 sub_0800583C(s32);
extern s32 sub_080C36E4(u32, s32);
extern void sub_0808E05C(s32, s32, s16, s32);
extern void sub_0808E348(s32, s32, s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 gMainWorkspace[];

/*
 * Spawns a projectile from the entity's stored coordinates, choosing between
 * two spawner helpers according to a flag, then advances the step counter and
 * fires the script callback once it passes its limit.
 */
void sub_08090E60(void *arg0)
{
  u8 *state = (u8 *) arg0;
  u32 *coords = *((u32 **) (state + 0x3C));
  s32 scaleConst = 0xC0000;
  s32 originX;
  s32 originY;
  s32 speed;
  s32 angle;
  u32 worldFlags;
  s32 r0;
  s32 r1;

  r0 = sub_0800583C(scaleConst);
  r0 += 0x100000;
  r1 = coords[2];
  originX = r1 + r0;
  r0 = sub_0800583C(scaleConst);
  r0 += 0x100000;
  r1 = coords[3];
  originY = r1 + r0;
  r0 = gMainWorkspace[0x1898 / 4];
  r0 = sub_080C36E4(r0, 5) - 2;
  speed = r0 << 15;
  angle = 0x8000 - sub_08005820(0x20000);
  worldFlags = gMainWorkspace[0x1898 / 4];
  if (worldFlags & 1)
  {
    s32 spawnKind = 0x16C1;
    sub_0808E348(originX, originY, speed, angle, spawnKind,
      (s16)(((((s32)(worldFlags + (worldFlags >> 31))) >> 1)) - ((((((s32)(worldFlags + (worldFlags >> 31))) >> 1)) + ((s32)((worldFlags + (worldFlags >> 31)) >> 31))) >> 1 << 1)),
      0xD);
  }
  else
  {
    u32 sum;
    s32 half;
    s32 biased;
    s32 halfOfBiased;
    s16 variant;

    sum = worldFlags + (worldFlags >> 31);
    half = ((s32) sum) >> 1;
    biased = half + ((s32) (sum >> 31));
    halfOfBiased = biased >> 1;
    variant = (s16) ((half - (halfOfBiased << 1)) + 5);
    sub_0808E05C(originX, originY, variant, 0xD);
  }
  {
    u8 counter = (state + ((*((s16 *) (state + 0x22))) * 2))[0x19];
    if (counter > 0xA)
    {
      s32 *callback;
      (state + ((*((s16 *) (state + 0x22))) * 2))[0x19] = 0;
      callback = (s32 *) 0x08671BB0;
      sub_080C31E4(state + 0x18, state + 0x22, *callback);
    }
  }
}
