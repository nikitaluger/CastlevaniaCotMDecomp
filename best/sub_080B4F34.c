struct S_0807B12C
{
  u8 _0x00[0x14];
  u32 field_0x14;
  u8 _0x18[0x0A];
  s16 field_0x22;
  u32 field_0x24;
  u8 _0x28[0x10];
  u32 field_0x38;
  u32 field_0x3C;
};

s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);

void sub_080B4F34(struct S_0807B12C *arg0) {
    int new_var;
    int new_var2;
    void *r5 = (void *) arg0->field_0x38;
    if (sub_08013B5C(r5, (void *) arg0->field_0x3C) == 0)
    {
        arg0->field_0x14 = 0x086703FC;
        arg0->field_0x22 += 1;
        *((u8 *) ((((u8 *) arg0) + (arg0->field_0x22 * 2)) + 0x19)) += 1;
        new_var = 0x18;
        new_var2 = arg0->field_0x22 * 2;
        sub_080C31E0(arg0, *((void **) ((((u32) (*((u8 *) ((((u8 *) arg0) + new_var) + new_var2)))) * 4) + arg0->field_0x14)));
        arg0->field_0x22 -= 1;
    }
    sub_08013C8C(arg0, r5);
}
