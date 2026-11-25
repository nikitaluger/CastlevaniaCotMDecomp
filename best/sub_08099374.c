extern void sub_080114A8(u32, void *, u16, u8);
extern void sub_0809C4E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
void sub_08099374(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u32 v38 = *((u32 *) (self + 0x38));
  u8 *r6 = *((u8 **) (self + 0x3C));
  u8 *arg1 = r6 + 0x34;
  u8 *r5 = r6 + 0x48;
  sub_080114A8(v38, arg1, 0, 0);
  sub_0809C4E0(*((s32 *) (r5 + 0x08)), 0);
  {
    u8 z;
    z = 0;
    *((u8 *) (r5 + 0x1D)) = 1;
    *((u8 *) (r6 + 0x69)) = z;
    *(arg1 = (u8 *) (r6 + 0x6A)) = z;
    {
      s32 t = 4 | *((u16 *) (r6 + 0x04));
      *((u16 *) (r6 + 0x04)) = (u16)t;
    }
  }
  *((u8 *) ((((*((s16 *) (self + 0x22))) * 2) + self) + 0x19)) = 0;
  {
    u32 *lit = (u32 *) 0x08671BB0;
    r5 = self + 0x18;
    sub_080C31E4(r5, self + 0x22, *lit);
  }
  {
    s16 idx = *((s16 *) (self + 0x22));
    ((self + (idx * 2)) + 0x19)[0] += 1;
  }
  {
    s16 idx = *((s16 *) (self + 0x22));
    u8 b;
    u32 *base;
    u32 val;
    r5 = r5 + (idx * 2);
    b = r5[0];
    base = *((u32 **) (self + 0x14));
    val = base[b];
    sub_080C31E0(self, val);
  }
}
