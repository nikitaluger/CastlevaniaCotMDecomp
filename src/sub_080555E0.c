struct S_02025FF0
{
  u8 _[0x1728];
  u32 f1728;
  u32 f172C;
};
extern struct S_02025FF0 gMainWorkspace;
s32 getAngleFromDelta(s32, s32);
void setPolarOffset(void *, s32, s32);
s32 signOf(s32);
void sub_080C31E4(void *, void *, s32);
void sub_080555E0(void *arg0)
{
  s32 new_var;
s32 __repair_phase_new_var;
  void *r6;
  void *r4;
  u8 *r7;
  s32 v;
  
  r6 = *((void **) (((u8 *) arg0) + 0x38));
  r4 = *((void **) (((u8 *) arg0) + 0x3C));
  r7 = ((u8 *) r4) + 0x48;
  if (signOf(*((s32 *) (((u8 *) r4) + 8))) > 0)
  {
    v = gMainWorkspace.f1728 + 0xFFE00000;
  }
  else
  {
    v = gMainWorkspace.f1728 + (0x80 << 14);
  }
  new_var = getAngleFromDelta(gMainWorkspace.f172C - (*((s32 *) (((u8 *) r4) + 0xC))), v - (*((s32 *) (((u8 *) r4) + 8))));
  setPolarOffset(r4, ((0x80 << 5) + new_var) & (0xF0 << 8), 0x80 << 8);
  *((u16 *) (((u8 *) r7) + 6)) = 0x96;
  new_var = signOf(*((s32 *) (((u8 *) r4) + 8)));
  *((u16 *) (((u8 *) r6) + 2)) = (new_var > 0) ? ((*((u16 *) (((u8 *) r6) + 2))) | 0x10) : ((*((u16 *) (((u8 *) r6) + 2))) & 0xFFEF);
  __repair_phase_new_var = (*((s16 *) (((u8 *) arg0) + 0x22))) * 2;
  *((u8 *) ((__repair_phase_new_var + (int)arg0) + 0x19)) = 0;
  {
    s32 *lit = (s32 *) 0x08671BB0;
    sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *lit);
 do { } while (0);
  }
}
