extern s32 sub_08004740(void *, void *, s32);
struct S_02025FF0_A8
{
  u8 _0[0x18A8];
  u8 v;
};
extern struct S_02025FF0_A8 gMainWorkspace;
extern u8 D_02023130[];
s32 sub_08012C44(u8 *arg0, s32 arg1, s32 count)
{
  s32 cur = arg1;
  s32 status = 0;
  s32 i = status;
  s32 ret;
  u32 addr;
  for (; i <= count; i++)
  {
    ret = sub_08004740((void *) (((u32) D_02023130) + (((u32) gMainWorkspace.v) << 6)), arg0, cur) - 1;
    switch (ret)
    {
      case 1:
        cur &= (s32) 0xFFF80000;
 do { addr = 0xFFF98000; return (cur - (((s32) (((u32) arg0) & (0xE0 << 11))) + ((s32) addr))) - arg1; } while (0);

      case 2:
        cur &= (s32) 0xFFF80000;
        addr = 0xFFFF8000;
        return (cur + (((s32) (((u32) arg0) & (0xE0 << 11))) + ((s32) addr))) - arg1;

      case 3:
        cur &= (s32) 0xFFF80000;
        addr = 0xFFF98000;
        return (cur - (((((s32) arg0) >> 1) & 0x30000) + ((s32) addr))) - arg1;

      case 4:
        cur &= (s32) 0xFFF80000;
        addr = 0xFFFD8000;
        return (cur - (((((s32) arg0) >> 1) & 0x30000) + ((s32) addr))) - arg1;

      case 5:
        cur &= (s32) 0xFFF80000;
        addr = 0xFFFF8000;
        return (cur + (((((s32) arg0) >> 1) & 0x30000) + ((s32) addr))) - arg1;

      case 6:
        cur &= (s32) 0xFFF80000;
        addr = 0xE0 << 10;
        return (cur + (((((s32) arg0) >> 1) & 0x30000) + ((s32) addr))) - arg1;

      case 0:

      case 7:

      case 11:

      case 15:

      case 16:

      case 17:

      case 18:
        if (status == 1)
      {
        goto st1;
      }
        cur += (s32) 0xFFF80000;
        status = 2;
        break;

      default:
        if (status == 2)
      {
        goto st2;
      }
        cur += 0x80000;
        status = 1;
        break;

    }

  }

  if (status == 1)
  {
    goto st1;
  }
  return 0;
  st2:
  cur &= (s32) 0xFFF80000;

  addr = 0xFFF88000;
  {
return cur - (arg1 + ((s32) addr));
}
  st1:
  cur &= (s32) 0xFFF80000;

  addr = 0x8000;

  return cur - (arg1 + ((s32) addr));

}
