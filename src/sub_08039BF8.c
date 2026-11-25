extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern void *sub_0805FAEC(s32, s32);
extern s32 sub_080C31E0(void *, s32);
struct S_02025FF0_1870
{
  u8 _0[0x1870];
  void *mgr;
};
extern struct S_02025FF0_1870 D_02025FF0;

/* For a matching sprite type, spawn a linked effect object that copies this
 * entity's state, link it into the global manager list, then despawn when the
 * state flag is set. */
void sub_08039BF8(u8 *obj)
{
  u8 *sprite = *((u8 **) (obj + 0x38));
  u8 *scriptState = *((u8 **) (obj + 0x3C));
  u8 *stateArg = scriptState + 0x34;
  u8 *control = scriptState + 0x48;
  sub_0801165C(scriptState, 0);
  sub_080113A8(sprite, stateArg);
  if ((*((u8 *) (obj + 0x84))) != 0)
  {
    return;
  }
  if ((*((u8 *) control)) == 0)
  {
    u16 spriteId = *((u16 *) (sprite + 0x28));
    if (((spriteId == 0x49) || (spriteId == 0x52)) || (spriteId == 0x5A))
    {
      void *spawned;
      u8 zero = 0;
      s32 one;
      u8 *p;
      s8 *p80;
      int value;
      one = 1;
      *((u8 *) control) = one;
      spawned = sub_0805FAEC((s32) D_02025FF0.mgr, 0xF1);
      if (spawned != 0)
      {
        value = *((u8 *) (obj + 0x4C));
        *((u8 *) (((u8 *) spawned) + 0x4C)) = value;
        *((s32 *) (((u8 *) spawned) + 0x5C)) = *((s32 *) (scriptState + 8));
        *((s32 *) (((u8 *) spawned) + 0x6C)) = *((s32 *) (scriptState + 0x0C));
        value = *((u8 *) (obj + 0x7C));
        p = ((u8 *) spawned) + 0x7C;
        *p = value;
        p += 8;
        *p = one;
        value = *((u8 *) (obj + 0x80));
        p80 = (s8 *) spawned;
        p80 += 0x80;
        *p80 = value;
      }
      *((u8 *) ((*((u8 **) (scriptState + 0x28))) + 1)) = zero;
      *((u8 *) ((*((u8 **) ((*((u8 **) (obj + 0x28))) + 0x30))) + 0x84)) = zero;
      *((u32 *) ((*((u8 **) ((*((u8 **) (obj + 0x28))) + 0x30))) + 0x2C)) = 0;
      {
        u8 *unused;
        *((u32 *) (obj + 0x2C)) = *((u32 *) (((u8 *) D_02025FF0.mgr) + 0x30));
        *((u32 *) (((u8 *) D_02025FF0.mgr) + 0x30)) = (u32) obj;
      }
      *((u32 *) (obj + 0x28)) = (u32) D_02025FF0.mgr;
      *((u32 *) (obj + 0x30)) = 0;
    }
  }
  if ((*((u8 *) (obj + 0x84))) == 0)
  {
    if ((*((u8 *) stateArg)) & 2)
    {
      sub_080C31E0(obj, *((s32 *) (obj + 0x24)));
    }
  }
}
