extern u8 gGameStatus[];
extern void playSound(u16, u32);
extern void sub_08062394(u8, u8, u8, u16);
extern void sub_080C31E0(void *, void *);
void sub_0805E608(u8 *arg0)
{
  u8 *base = gGameStatus;
  u8 *p = arg0 + 0x4C;
  u32 idx = *((u16 *) (p + 0x08));
  u8 *q = (base + 0x384) + idx;
  u32 v = *q;
  u8 c = v;
  do { if (idx == base[0x306])
  {
    c = v + 1;
  }
  if (idx == base[0x307])
  {
    c = c + 1;
  }
  if (idx == base[0x308])
  {
    c = c + 1;
  }
 do { if (c <= 0x62) { *((u8 *) q) = v + 1; } } while (0);
  sub_08062394(1, *((u8 *) (p + 0x08)), c, idx);
  playSound(0x77, v);
  sub_080C31E0(arg0, *((void **) (arg0 + 0x24))); } while (0);
}
