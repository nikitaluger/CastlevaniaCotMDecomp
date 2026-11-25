inline static u16 z16(void)
{
  u16 v = 0;
  return v;
}

void sub_08005AF8(void *arg0)
{
  int new_var;
  void *r6;
  u8 *r8;
  u16 r2h;
  u32 r0;
  u32 r9;
  u32 r5;
  u32 off;
  u8 *r2;
  u8 *r4;
  u8 *r1;
  s16 tmp;
  u8 *p;
  u8 *new_var2;
  r6 = arg0;
  r4 = (u8 *) 0x02021E90;
  *((u32 *) (r4 + 0x125C)) = 0;
  r8 = (u8 *) 0x03000830;
  r2h = *((u16 *) r8);
  r0 = 0xF0FF;
  r0 = r0 & r2h;
  r9 = z16();
  *((u16 *) r8) = (u16) r0;
  r5 = 0x93 << 5;
  r2 = r4 + r5;
  r0 = 0xD8;
  r0 = r0 << 8;
  *((u16 *) r2) = (u16) r0;
  r0 = 0x95 << 5;
  r2 = r4 + r0;
  r0 = 0xF8 << 8;
  *((u16 *) r2) = (u16) r0;
  off = 0x99 << 5;
  r0 = (u32) (r4 + off);
  *((u16 *) r0) = 0;
  r5 += 0x80;
  r0 = (u32) (r4 + r5);
  *((u16 *) r0) = 0;
  r0 = 0x1262;
  r2 = r4 + r0;
  r0 = 0x84;
  *((u16 *) r2) = (u16) r0;
  r5 -= 0x3E;
  r2 = r4 + r5;
  r0 = 0x484;
  *((u16 *) r2) = (u16) r0;
  r4 = r4 + 0x1278;
  r5 -= 0x26;
  r2 = r4 + r5;
  r5 += 0x3C;
  r0 = (u32) (r4 + r5);
  r5 += 0x04;
  r1 = r4 + r5;
  *((u32 *) r1) = 0;
  *((u32 *) r0) = 0;
  *((u32 *) r2) = 0;
  *((u32 *) r4) = 0;
  sub_08000E98((void *) 1, (void *) 0x080C4866, (void *) 0x06004000, 0x4640, 0x10);
  sub_08000E98((void *) 1, (void *) 0x080C4694, (void *) 0x05000000, 0x1D2, 0x10);
  sub_08000E98((void *) 1, (void *) 0x080C8EA6, (void *) 0x06000000, 0x500, 0x10);
  sub_08000E98((void *) 1, (void *) 0x080C93A6, (void *) 0x06002000, 0x500, 0x10);
  *((volatile u16 *) (r8 + 4)) = 0xBF;
  *((volatile u16 *) (r8 + 8)) = 0x10;
  sub_080C0574();
  tmp = *((s16 *) (((u8 *) r6) + 0x22));
  p = (u8 *) ((tmp * 2) + ((u32) r6));
  new_var = 0x22;
  new_var2 = ((u8 *) r6) + 0x18;
  p[0x19] = (u8) r9;
  sub_080C31E4(new_var2, ((u8 *) r6) + new_var, *((void **) 0x08671BB0));
}

