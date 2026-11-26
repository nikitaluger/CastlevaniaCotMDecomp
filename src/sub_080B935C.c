s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080113A8(void *, void *);
void sub_0801165C(void *, s32);
void sub_080C31E4(void *, void *, s32);
extern u32 gMainWorkspace[];

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
void sub_080B956C(struct S_0807B12C *arg0)
{
  int new_var;
  int new_var2;
  void *r5 = (void *) arg0->field_0x38;
  if (sub_08013B5C(r5, (void *) arg0->field_0x3C) == 0)
  {
    arg0->field_0x14 = 0x0867058C;
    arg0->field_0x22 += 1;
    *((u8 *) ((((u8 *) arg0) + (arg0->field_0x22 * 2)) + 0x19)) += 1;
    new_var = 0x18;
    new_var2 = arg0->field_0x22 * 2;
    sub_080C31E0(arg0, *((void **) ((((u32) (*((u8 *) ((((u8 *) arg0) + new_var) + new_var2)))) * 4) + arg0->field_0x14)));
    arg0->field_0x22 -= 1;
  }
  sub_08013C8C(arg0, r5);
}

void sub_080B9398(void *arg0) {
    u8 *self = arg0;
    s32 p38 = *(s32 *)(self + 0x38);
    u8 *p3C = *(u8 **)(self + 0x3C);
    sub_080113A8((void *)p38, p3C + 0x34);
    *(s32 *)(p3C + 0x10) += *(s32 *)(self + 0x7C) << 13;
    sub_0801165C(p3C, 0);
}

/* Run one step of the entity's command script; command 0x10 clears the current
 * command byte and reloads the script from the default command table. */
void sub_080B935C(void *arg0) {
    u8 *obj = arg0;
    sub_080113A8(*(s32 *)(obj + 0x38), *(u8 **)(obj + 0x3C) + 0x34);
    if (*(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) == 0x10) {
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(obj + 0x18, obj + 0x22, *lit);
        }
    }
}

void sub_080B97F0(void *arg0) {
    void *p38 = *(void **)((u8 *)arg0 + 0x38);
    if (gMainWorkspace[16] == 7) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }
    sub_08013C8C(arg0, p38);
}
