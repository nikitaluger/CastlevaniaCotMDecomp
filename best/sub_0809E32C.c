extern void sub_08011528(void *a, void *b, void *c, void *d);
struct Pair9E { u16 a; u16 b; };
void sub_0809E32C(void *a0, void *a1, void *a2, void *a3)
{
  u8 *r1p;
  s32 idx;
  u32 p;
  s32 v;
  s32 old;
  sub_08011528(a0, a1, a2, a3);
  r1p = *((u8 **) (((u8 *) a1) + 8));
  idx = *((s16 *) (((u8 *) a1) + 0x0E));
  idx = idx + (*((u8 *) (((u8 *) a1) + 1)));
  r1p = *((u8 **) r1p);
  p = (u32)(idx * 4) + (u32)r1p;
  v = ((struct Pair9E *)(p - 4))->b;
  old = *((u16 *) (((u8 *) a3) + 0x3E));
  if (v != old)
  {
    switch (v)
    {
      case 0x24:
        *((s32 *) (((u8 *) a2) + 0x0C)) += 0x20000;
        break;
      case 0x2A:
        *((s32 *) (((u8 *) a2) + 0x0C)) += (s32)0xFFFE0000;
        break;
      case 0x27:
        if (old == 0x24)
          *((s32 *) (((u8 *) a2) + 0x0C)) += (s32)0xFFFE0000;
        else
          *((s32 *) (((u8 *) a2) + 0x0C)) += 0x20000;
        break;
    }
    r1p = *((u8 **) (((u8 *) a1) + 8));
    idx = *((s16 *) (((u8 *) a1) + 0x0E));
    idx = idx + (*((u8 *) (((u8 *) a1) + 1)));
    r1p = *((u8 **) r1p);
    p = (u32)(idx * 4) + (u32)r1p;
    *((u16 *) (((u8 *) a3) + 0x3E)) = ((struct Pair9E *)(p - 4))->b;
  }
}
