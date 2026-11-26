extern void sub_080C2E68(void *, s32, s32);
extern void postDisplaySprite(s32, s32, s32, s32, s32);
struct S_02021E90
{
  u8 _0[0x1262];
  u16 field;
};
extern struct S_02021E90 gCameraState;
struct DmaRegs
{
  u32 src;
  u32 dst;
  u32 ctrl;
};
extern volatile struct DmaRegs D_040000D4;
struct Arrays
{
  u16 a[0x20];
  u16 b[0x20];
  u16 c[0x20];
};
void sub_08062484(void)
{
  u8 stk[4];
  struct Arrays *arr;
  u32 count;
  u16 val;
  s32 i;
  s32 idx;
  u8 temp;
  sub_080C2E68(stk, (void *) 0x080DBE22, 4);
  D_040000D4.src = 0x08442570;
  D_040000D4.dst = (u32) ((struct Arrays *) 0x02027A18);
  arr = (struct Arrays *) 0x02027A18;
  D_040000D4.ctrl = 0x84000030;
  (void) D_040000D4.ctrl;
  temp = *((u8 *) (((u8 *) arr) + 0xC3));
  count = temp;
  val = *((u16 *) (stk + (((u32) (*((u8 *) (((u8 *) arr) + 0xC4)))) * 2)));
  idx = 0x1A;
  do
  {
    idx = idx - count;
  }
  while (0);
  ((struct Arrays *) 0x02027A18)->a[idx] |= 0x83;
  ((struct Arrays *) 0x02027A18)->b[idx] |= 0x82;
  ((struct Arrays *) 0x02027A18)->c[idx] |= 0x85;
  idx++;
  ((struct Arrays *) 0x02027A18)->a[idx] |= 0x84;
  ((struct Arrays *) 0x02027A18)->b[idx] |= val;
  ((struct Arrays *) 0x02027A18)->c[idx] |= 0x86;
  idx++;
  for (i = 0; i < count; i++)
  {
    u16 *temp2;
    arr->a[idx] |= 0x87;
    arr->b[idx] |= 0x89 + i;
    temp2 = arr->c;
    temp2[idx] |= 0x88;
    idx++;
  }

  ((struct Arrays *) 0x02027A18)->a[idx] |= 0x484;
  ((struct Arrays *) 0x02027A18)->b[idx] |= val;
  ((struct Arrays *) 0x02027A18)->c[idx] |= 0x486;
  idx++;
  ((struct Arrays *) 0x02027A18)->a[idx] |= 0x483;
  ((struct Arrays *) 0x02027A18)->b[idx] |= 0x482;
  ((struct Arrays *) 0x02027A18)->c[idx] |= 0x485;
  postDisplaySprite(1, (s32) ((struct Arrays *) 0x02027A18), ((gCameraState.field & 0x1F00) << 3) + 0x06000440, 0xC0, 0x10);
}

