extern void *sub_0805FAEC(s32, s32);
extern void sub_080A2D80(void *, s32, s32);
extern void sub_080A2D8C(void *, s32);
void sub_080A2D80(void *arg0, s32 arg1, s32 arg2);
struct S_7C
{
  u8 pad[0x7C];
  u8 b[1];
};
void sub_080A2D8C(void *arg0, s32 arg1)
{
  ((struct S_7C *) arg0)->b[0] = arg1;
  if (arg0 != NULL)
  {
  }
}

struct S_80
{
  u8 pad[0x80];
  u8 b[1];
};
void *sub_080A2D30(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
struct S_02025FF0
{
  u8 _0x000[0x1870];
  u32 v;
};
extern struct S_02025FF0 D_02025FF0;
struct S_E38
{
  u8 pad[0x4C];
  u8 b[9];
};
void *sub_080A2E38(s32 arg0);
