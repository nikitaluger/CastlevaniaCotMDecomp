s32 sub_08005820(s32);
s32 sub_0800583C(s32);
s32 sub_08014848(s32, s32, s32, s32, s32, s32);
s32 sub_0808BB54();
s32 sub_0808E61C(s32, s32, s32, s32);
s32 sub_080C31E4(void *, void *, s32);
void sub_0809E0B4(void *arg0)
{
  s32 temp_r4_2;
  s32 temp_r6;
  s32 temp_r8;
  u32 temp_r1;
  void *temp_r0;
  s8 *new_var;
  void *temp_r4;
  s32 v;
  u32 zero;
  u16 vmask;
  s32 *p;
  do
  {
    temp_r0 = *((void **) (((s8 *) arg0) + 0x38));
    temp_r4 = *((void **) (((s8 *) arg0) + 0x3C));
    *((u32 *) (((s8 *) arg0) + 4)) = (u32) ((*((u32 *) (((s8 *) arg0) + 4))) + 1);
    if (!(2 & (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)))))
    {
      *((u16 *) (((s8 *) temp_r0) + 0)) = (u16) ((0xFFF & (*((u16 *) (((s8 *) temp_r0) + 0)))) | 0xE000);
    }
    if (!(7 & (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)))))
    {
      sub_08014848(2, 1, *((s32 *) (((s8 *) temp_r4) + 8)), (*((s32 *) (((s8 *) temp_r4) + 0xC))) + 0xFFF00000, 0x100000, 0x100000);
    }
    if ((7 & (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)))) == 4)
    {
      temp_r8 = *((s32 *) (((s8 *) temp_r4) + 8));
      temp_r4_2 = (*((s32 *) (((s8 *) temp_r4) + 0xC))) + 0xFFF00000;
      temp_r6 = sub_0800583C(0x18000);
      sub_0808E61C(temp_r8, temp_r4_2, temp_r6, 0 - (sub_08005820(0x20000) + 0x18000));
    }
    vmask = 0x400 | (*((u16 *) (((s8 *) temp_r0) + 2)));
    zero = 0;
    *((u16 *) (((s8 *) temp_r0) + 2)) = vmask;
    new_var = (s8 *) ((void *) 0x03000830);
    v = 0x3F40;
    *((s16 *) (new_var + 4)) = (s16)v;
    temp_r1 = (u32) (*((u32 *) (((s8 *) arg0) + 4)));
    temp_r1 = temp_r1 >> 3;
  }
  while (0);
  *((s16 *) (new_var + 6)) = (s16) ((temp_r1 << 8) | (0x10 - temp_r1));
  *((u16 *) (((s8 *) temp_r0) + 4)) = (u16) ((*((u16 *) (((s8 *) temp_r0) + 4))) + 0x10);
  *((u16 *) (((s8 *) temp_r0) + 6)) = (u16) ((*((u16 *) (((s8 *) temp_r0) + 6))) - 1);
  if ((*((u32 *) (((s8 *) arg0) + 4))) == 0x80)
  {
    *((u8 *) (((s8 *) temp_r0) + 0x2A)) = (u8) (0xBF & (*((u8 *) (((s8 *) temp_r0) + 0x2A))));
    sub_0808BB54();
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = (u8)zero;
    p = (s32 *)0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *p);
  }
}
