s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, s32, void *);
void sub_080A5418(void *);
void sub_080A543C(void *);
s32 sub_080C2F24(s16, s32);
void sub_080A5714(void *, s32, s32);
extern u16 D_03000830[4];

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
void sub_080A51F4(struct S_0807B12C *arg0)
{
  int new_var;
  int new_var2;
  void *r5 = (void *) arg0->field_0x38;
  if (sub_08013B5C(r5, (void *) arg0->field_0x3C) == 0)
  {
    arg0->field_0x14 = 0x0866FF58;
    arg0->field_0x22 += 1;
    *((u8 *) ((((u8 *) arg0) + (arg0->field_0x22 * 2)) + 0x19)) += 1;
    new_var = 0x18;
    new_var2 = arg0->field_0x22 * 2;
    sub_080C31E0(arg0, *((void **) ((((u32) (*((u8 *) ((((u8 *) arg0) + new_var) + new_var2)))) * 4) + arg0->field_0x14)));
    arg0->field_0x22 -= 1;
  }
  sub_08013C8C(arg0, r5);
}

void sub_080A53EC(void *arg0) {
    *(u8 *)((u8 *)arg0 + 0x6C) = 0;
    *(u16 *)((u8 *)arg0 + 2) |= 0x800;
    *(void **)((u8 *)arg0 + 0x14) = (void *)sub_080A5418;
    *(u16 *)((u8 *)arg0 + 0x22) = 1;
    sub_080C31E4(arg0, 1, (void *)sub_080A5418);
}

void sub_080A5418(void *arg0) {
    u8 *self = arg0;
    if (*(u8 *)(self + 0x6C) != 0) {
        *(void **)(self + 0x14) = (void *)sub_080A543C;
        *(u16 *)(self + 0x22) = 1;
        sub_080C31E0(arg0, (void *)sub_080A543C);
    }
}

void sub_080A543C(void *arg0) {
    u8 *self = arg0;
    s16 t;
    s32 v;
    if (sub_080C2F24(*(s16 *)(self + 0x22), 2) == 0) {
        sub_080A5714(arg0, *(s32 *)(self + 0x4C), *(s32 *)(self + 0x5C));
    }
    D_03000830[2] = 0xFD << 6;
    t = *(s16 *)(self + 0x22);
    v = (t > 0x3C) ? ((s32)(t - 0x3C) >> 1) : 0;
    D_03000830[3] = (u16)((v << 8) | (0x10 - v));
    if (v == 0x10) {
        sub_080C31E0(arg0, *(void **)(self + 0x24));
    }
}
