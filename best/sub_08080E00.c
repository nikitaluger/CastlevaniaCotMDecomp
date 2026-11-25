struct S_02025FF0
{
  u8 _[0x18C2];
  u16 w;
};
extern struct S_02025FF0 D_02025FF0;
extern u16 D_03000830[];
s32 sub_0800168C(void *, s32, s32, s32);
void *sub_0800355C(void);
void sub_0806D2D0(void *);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
void sub_08080E00(void *arg0)
{
  void *temp;
  u8 zero;
  u8 *new_var;
  void *new_var2;
  u16 mv;
 do { if (sub_0800168C(arg0, 0, 0x68, 3) == 0) { sub_080C31E0(arg0, *((s32 *) (((u8 *) arg0) + 0x24))); return; } temp = sub_0800355C(); if (temp == NULL) { sub_0806D2D0(arg0); return; } *((void **) (((u8 *) arg0) + 0x38)) = temp; new_var2 = arg0; *((s32 *) (((u8 *) temp) + 0x1C)) = 0x80000004; mv = 0x0400 | (*((u16 *) (((u8 *) temp) + 2))); zero = 0; *((u16 *) (((u8 *) temp) + 2)) = mv; *((u16 *) temp) = D_02025FF0.w; new_var = (u8 *) new_var2; } while (0);
  D_03000830[3] = 0x1000;
  *((u8 *) ((new_var + ((*((s16 *) (new_var + 0x22))) * 2)) + 0x19)) = zero;
  {
    s32 *nv = (s32 *) 0x08671BB0;
    sub_080C31E4(new_var2 + 0x18, new_var2 + 0x22, *nv);
  }
  {
    u8 *p2 = (u8 *) ((((u32) (*((s16 *) (new_var + 0x22)))) * 2) + ((u32) new_var2));
    p2[0x19] = (u8) (p2[0x19] + 1);
  }
  {
    s32 idx2 = (*((s16 *) (new_var + 0x22))) * 2;
    u8 *base = new_var + 0x18;
    u8 b = *(base + idx2);
    u8 **tbl = *((u8 **) (new_var + 0x14));
    sub_080C31E0(new_var2, (s32) tbl[b]);
  }
}
