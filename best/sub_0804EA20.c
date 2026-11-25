extern s32 sub_08005820(s32);
extern s32 sub_0800583C(s32);
extern s16 sub_080C389C(s32, s32);
void sub_0804EA20(void *arg0)
{
  u8 *self = (u8 *)arg0;
  u8 *r6 = *(u8 **)(self + 0x3C);
  u8 *r4 = r6;
  s32 r5;
  s32 r1;
  s32 val;
  r4 += 0x48;

  *(s16 *)(r4 + 0x10) = sub_080C389C(sub_08005820(2) + *(s16 *)(r4 + 0x10) + 1, 3);
  r5 = sub_0800583C(0x80 << 14);
  r1 = sub_0800583C(0x80 << 13);

  switch (*(s16 *)(r4 + 0x10)) {
    case 0:
      val = *(s32 *)(r6 + 0x48);
      val = val + r5;
      break;
    case 1:
      val = *(s32 *)(r6 + 0x48) + 0xFFB00000;
      val = val - r5;
      break;
    case 2:
      val = *(s32 *)(r6 + 0x48) + (0xA0 << 15);
      val = val + r5;
      break;
    default:
      goto done;
  }
  *(s32 *)(r4 + 0x08) = val;
done:
  *(s32 *)(r4 + 0x0C) = *(s32 *)(r4 + 0x04) + r1;
}
