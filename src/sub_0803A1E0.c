s32 sub_08011344(s32, s32, s32, s32);
s32 sub_080113A8(s32, s32);
s32 sub_08011EE8(void *, s32, s32);
s32 sub_08014668(s32, s32);
s32 sub_08014938(s32);
u32 sub_08005820(u32);
s32 sub_0803B0D8(void *, void *, s32);
s32 sub_0803B0F8(void *, s32, void *, s32);
s32 sub_080C31E4(void *, void *, s32);
extern s16 D_080CF1D2[];

/* Set up the entity's sprite state and animation; in AI mode 2, face the
 * target, pick a random animation from a table, play it, and advance the
 * current script step. */
void sub_0803A1E0(void *arg0)
{
  u8 *xPos;
  void *self = arg0;
  s32 parent = *((s32 *) (((u8 *) self) + 0x38));
  int flags;
  void *comp = *((void **) (((u8 *) self) + 0x3C));
  s32 body = (s32) (((u8 *) comp) + 0x34);
  void *tracker = (void *) (((u8 *) comp) + 0x48);
  s32 *lit;
  s32 animId;
  s32 stepOffset;
  u32 randByte;
  s32 zero;
  sub_0803B0D8(comp, tracker, 0x4000);
  sub_0803B0F8(comp, parent, tracker, 0x080CF1C8);
  sub_08011EE8(comp, 0x16C1, 0);
  sub_080113A8(parent, body);
  xPos = ((u8 *) comp) + 8;
  sub_08014668(parent, *((s32 *) (((u8 *) comp) + 0x10)));
  if ((*((u8 *) (((u8 *) tracker) + 4))) == 2)
  {
    if (sub_08014938(*((s32 *) xPos)) == 1)
    {
      *((u16 *) (((u8 *) parent) + 2)) = (flags = 0x10 | (*((u16 *) (((u8 *) parent) + 2))));
    }
    else
    {
      *((u16 *) (((u8 *) parent) + 2)) &= 0xFFEF;
    }
    randByte = sub_08005820(3);
    zero = 0;
    *((u8 *) (((u8 *) tracker) + 0xC)) = (u8) randByte;
    animId = D_080CF1D2[*((u8 *) (((u8 *) tracker) + 0xC))];
    sub_08011344(parent, body, animId, 0);
    stepOffset = ((*((s16 *) (((u8 *) self) + 0x22))) * 2) + ((s32) self);
    *((u8 *) (stepOffset + 0x19)) = zero;
    lit = (s32 *) 0x08671BB0;
    sub_080C31E4((void *) (((u8 *) self) + 0x18), (void *) (((u8 *) self) + 0x22), *lit);
  }
}
