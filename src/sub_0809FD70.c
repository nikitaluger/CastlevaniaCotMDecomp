struct S_0809FD70
{
  u8 _0x00[0x14];
  u32 field_0x14;
  u8 _0x18[0x0A];
  s16 field_0x22;
  u32 field_0x24;
  u8 _0x28[0x10];
  u32 field_0x38;
  u32 field_0x3C;
  u8 _0x40[0x0C];
  u32 field_0x4C;
  u8 _0x50[0x0C];
  u32 field_0x5C;
  u8 _0x60[0x0C];
  u32 field_0x6C;
};
s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
void sub_08014668(void *);
void sub_080C31E0(void *, void *);
void sub_0809FD70(struct S_0809FD70 *arg0)
{
  int new_var;
  int new_var2;
  struct S_0809FD70 *new_var3;
  void *r6 = (void *) arg0->field_0x38;
  void *r4 = (void *) arg0->field_0x3C;
  *((u32 *) (((u8 *) r4) + 0x08)) = arg0->field_0x4C;
  new_var3 = arg0;
  *((u32 *) (((u8 *) r4) + 0x0C)) = new_var3->field_0x5C;
  new_var2 = new_var3->field_0x6C;
  *((u32 *) (((u8 *) r4) + 0x10)) = new_var2;
  sub_08014668(r6);
  if (sub_08013B5C(r6, r4) == 0)
  {
    new_var3->field_0x14 = 0x0866FDC8;
    new_var3->field_0x22 += 1;
    *((u8 *) ((((u8 *) new_var3) + (new_var3->field_0x22 * 2)) + 0x19)) += 1;
    new_var = 0x18;
    new_var2 = new_var3->field_0x22;
    new_var2 = new_var2 * 2;
    sub_080C31E0(new_var3, *((void **) ((((u32) (*((u8 *) ((((u8 *) new_var3) + new_var) + new_var2)))) * 4) + new_var3->field_0x14)));
    new_var3->field_0x22 -= 1;
  }
  sub_08013C8C(new_var3, r6);
}

