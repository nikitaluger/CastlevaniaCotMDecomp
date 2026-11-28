extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 divInt32(s32, s32);
extern s32 signedRemainder(s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern u8 gMainWorkspace[];
void sub_0803157C(u8 *self)
{
  void *parent;
  void *ref;
  u8 *obj;
  u8 *anim;
  u8 *state;
  s32 x;
  s32 t;
  s32 kind;
  s32 __repair_phase_kind;
  u8 *__repair_phase_slot;
  s32 *__repair_phase_callbackTable;
  u8 *__base_gMainWorkspace;
  __base_gMainWorkspace = gMainWorkspace;
  parent = *((void **) (self + 0x38));
  ref = *((void **) (self + 0xAC));
  do
  {
    obj = *((u8 **) (self + 0x3C));
    anim = obj + 0x34;
    state = obj + 0x48;
    setAnimationFrame(parent, anim, 0, 0);
    x = *((s32 *) (obj + 8));
    t = (x * 9) + (*((s32 *) (obj + 0xC)));
    if (t < 0)
    {
      s32 a;
      s32 q;
      s32 first;
      s32 second;
      do { do { do { q = divInt32((float) t, 0x280000); } while (0); } while (0); } while (0);
      first = signedRemainder(a - (q * 30), 0x14A);
      second = signedRemainder(*((s32 *) (__base_gMainWorkspace + 0x189C)), 0x14A);
      a = (t + 0xFFFF) >> 16;
      if (second != first)
      {
        return;
      }
    }
    if (((*((s16 *) (state + 8))) == 1) || (((*((u16 *) ((*((void **) (((u8 *) ref) + 4))) + 6))) & 2) != 0))
    {
      s32 *callbackTable;
      u8 *slot;
      *((u16 *) state) = 1;
      slot = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
      *((u8 *) (slot + 0x19)) = 0;
      callbackTable = (s32 *) 0x08671BD0;
      sub_080C31E8(self + 0x18, self + 0x22, 2, *callbackTable);
      return;
    }
    if ((absXFromFocus(x) > 0x600000) || (absYFromFocus(*((s32 *) (obj + 0xC))) > 0x400000))
    {
      s32 *callbackTable;
      u8 *slot;
      kind = *((s16 *) (obj + 0x1C));
      if ((kind == 0xD) || (kind == 0x77))
      {
        *((u16 *) (state + 6)) = 3;
      }
      else
      {
        *((u16 *) state) = 1;
      }
      slot = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
      *((u8 *) (slot + 0x19)) = 0;
      callbackTable = (s32 *) 0x08671BD0;
      sub_080C31E8(self + 0x18, self + 0x22, 2, *callbackTable);
      return;
    }
    __repair_phase_kind = *((s16 *) (obj + 0x1C));
  }
  while (0);
  if ((__repair_phase_kind == 0xD) || (__repair_phase_kind == 0x77))
  {
    *((u16 *) (state + 6)) = 3;
  }
  else
  {
    *((u16 *) state) = 1;
  }
  __repair_phase_slot = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
  *((u8 *) (__repair_phase_slot + 0x19)) = 0;
  __repair_phase_callbackTable = (s32 *) 0x08671BD0;
  sub_080C31E8(self + 0x18, self + 0x22, 1, *__repair_phase_callbackTable);
}

