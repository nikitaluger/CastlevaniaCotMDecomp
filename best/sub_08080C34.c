extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_080E596C[];
extern u8 D_080E598C[];
extern s32 sub_0806D450(void *, void *, void *);
extern void sub_080722E0(void *, u8);
extern void *sub_0808DBF8(s32, s32, u16);
extern s32 sub_08003740(void *, s32);
extern s16 sub_080C364C(s32, s16);
extern void _call_via_r1(void *, void *);
volatile int sub_08080C34(void *arg0)
{
  char *__repair_addr;
  u8 *e;
  u8 *q;
  u8 *spr;
  u8 *entry;
  u8 *t;
  u8 *t_1;
  u8 *t_2;
  s32 r1v;
  s32 nr2;
  s16 tmp;
  u32 h;
  s16 sh;
  u8 v;
  u8 v_1;
  u32 g58;
  u32 nr;
u32 __repair_subtotal;
  s32 g54;
  s32 add;
  s32 v54;
  s32 v54_1;
  s32 r0;
  s32 m;
  s32 r4v;
  s32 r3v;
  u16 flags;
  u8 b;
  u32 idx;
  u32 val0;
  u32 val1;
  u32 p10;
  s32 arg0v;
  s32 arg1v;
  u8 idx2;
  u8 v2;
  e = (u8 *) arg0;
  q = (*((u8 **) (e + 0x6C))) + 4;
  spr = *((u8 **) (e + 0x38));
  if (sub_0806D450(e, spr, q) > 0)
  {
    r1v = *((s32 *) (e + 0x24));
    goto L_D4C;
  }
  __repair_addr = (char *) (e + 0x9C);
  idx2 = D_080E596C[*((u32 *) __repair_addr)];
  entry = D_080E598C + (idx2 * 28);
  idx = *((u16 *) (spr + 0x04));
  sh = *((s16 *) (spr + 0x04));
  if (sh > 0x100)
  {
    *((u16 *) (spr + 0x04)) = idx - 0x40;
    *((u16 *) (spr + 0x06)) = (*((u16 *) (spr + 0x06))) - 0x40;
    t_1 = *((u8 **) (q + 0x2C));
    tmp = sub_080C364C(((s32) (*((s16 *) entry))) << 8, *((s16 *) (spr + 0x04)));
    *((s16 *) (t_1 + 0x06)) = tmp;
    t_2 = *((u8 **) (q + 0x2C));
    tmp = sub_080C364C(((s32) (*((s16 *) (entry + 2)))) << 8, *((s16 *) (spr + 0x06)));
    *((s16 *) (t_2 + 0x08)) = tmp;
  }
  v = entry[0x11];
  g58 = *((u32 *) (q + 0x58));
  nr = g58 + v;
  __repair_subtotal = 0xFF;
idx = nr & __repair_subtotal;
  nr2 = (u8) idx;
  *((u32 *) (q + 0x58)) = idx;
  g54 = *((s32 *) (q + 0x54));
  add = *((s32 *) (entry + 0x14));
  g54 += add;
  *((u32 *) (q + 0x54)) = g54;
  if (g54 <= 0x00800000)
  {
    goto L_CONT;
  }
  r1v = *((s32 *) (e + 0x24));
  goto L_D4C;
  L_CONT:
  sub_080722E0(q, nr2);

  v54_1 = *((s32 *) (q + 0x54));
  r0 = v54_1 >> 12;
  m = *((s32 *) (q + 0x08));
  r0 = r0 * m;
  if (r0 < 0)
  {
    r0 += 0x0F;
  }
  r0 >>= 4;
  nr = (0xF0 << 15);  r4v = r0 + nr; 
  v54 = *((s32 *) (q + 0x54));
  *((s32 *) (spr + 0x14)) = r4v;
  r0 = v54 >> 12;
  m = *((s32 *) (q + 0x0C));
  r0 = r0 * m;
  if (r0 < 0)
  {
    r0 += 0x0F;
  }
  r0 >>= 4;
  r3v = r0 + (0xA0 << 15);
  *((s32 *) (spr + 0x18)) = r3v;
  t = *((u8 **) (q + 0x2C));
  flags = *((u16 *) (t + 0x14));
  if ((flags & 1) == 0)
  {
    goto L_D68;
  }
  if ((flags & 2) != 0)
  {
    goto L_D68;
  }
  {
    u8 *pt;
    u8 *pb;
    pt = gCameraState;
    pb = gMainWorkspace;
    pb += 0x18A8;
    arg0v = (((u32) (*pb)) + 1) * 0x40;
    val0 = *((u32 *) ((pt + 0x1278) + arg0v));
    arg0v = r4v + val0;
    r1v = (((u32) (*pb)) + 1) * 0x40;
    val1 = *((u32 *) ((pt + 0x127C) + r1v));
    arg1v = r3v + val1;
    sub_0808DBF8(arg0v, arg1v, 0);
    q = e;
    r1v = *((s32 *) (q + 0x24));
    goto L_D4C;
  }
  L_D68:
  {
    u8 *base2;
    u16 h2;
    base2 = gMainWorkspace;
    h2 = *((u16 *) (base2 + 0x18C2));
    *((u16 *) (spr + 0x00)) = h2;
    sub_08003740(q + 0x1C, (s32) spr);
    v_1 = base2[0x173A];
    if (v_1 != 0x1C)
    {
      v2 = base2[0x14ED];
      if (v2 != 0)
      {
        goto L_D9E;
      }
      p10 = *((u32 *) (base2 + 0x10));
      if (p10 == 0)
      {
        goto L_D9E;
      }
    }
  }

  {
    s32 r1x;
    r1x = *((s32 *) (e + 0x24));
    _call_via_r1(e, (void *) r1x);
  }
  goto L_D9E;
  L_D4C:
  _call_via_r1(e, (void *) r1v);

  L_D9E:
  (void) 0;

}

