extern u8 D_08102040[];
extern u16 D_0810205C[];
void sub_080A88C0(void *);
void sub_080A860C(void *, void *);
void sub_080A88EC(void *, void *, void *);
u32 sub_080A89A4(void *);
s32 sub_08005820(u8);
void sub_080C31E8(void *, void *, u32, u32);
void sub_080A6140(void *arg0)
{
  u32 *u38 = *((u32 **) (((u8 *) arg0) + 0x38));
  u8 *s = *((u8 **) (((u8 *) arg0) + 0x3C));
  u8 *q = s + 0x48;
  u32 idx = 0x88;
  u8 t2;
  u32 ret;
  u8 *p2;
  u8 *p4;
  u8 *tbl;
  u32 *g1;
  u32 *g2;
  u32 *g3;
  sub_080A88C0(q);
  sub_080A860C(arg0, q);
  sub_080A88EC(arg0, u38, q);
  if ((*((u8 *) (s + 0x120))) == 0)
  {
    return;
  }
  if ((*((u32 *) (((u8 *) s) - (-(idx * 2))))) != 0)
  {
    return;
  }
  t2 = *((u8 *) (s + 0x122));
  if ((t2 == 0) && ((*(((u8 *) arg0) + 0x7C)) != 0))
  {
    *((u8 *) (s + 0x122)) = 1;
    *((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x17) = t2;
    g1 = (u32 *) 0x08671BD8;
    sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 4, *g1);
    return;
  }
  q[0xD9]--;
  if (q[0xD9] != 0)
  {
    *((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19) = 0;
    g2 = (u32 *) 0x08671BD0;
    sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 1, *g2);
    return;
  }
  ret = sub_080A89A4(arg0);
  switch (ret)
  {
    default:
      p2 = q + 0xDC;
      p4 = q + 0xDD;
      break;

    case 0:
      *(q + 0xDC) = 1;
      p2 = q + 0xDC;
      p4 = q + 0xDD;
      break;

    case 1:
      tbl = D_08102040;
      p4 = q + 0xDD;
    {
      u32 base = sub_08005820(tbl[(*p4) * 4]);
      u32 off = ((*p4) * 4) + 1;
      u32 address = base + off;
      u8 v = *((u8 *) (address + ((u32) tbl)));
      *(q + 0xDC) = v;
      p2 = (q + 0xDC) + (((u32) v) * 0);
    }
      break;

    case 2:
      *(q + 0xDC) = (u8) ret;
      p2 = q + 0xDC;
      p4 = q + 0xDD;
      break;

  }

  {
    u32 value = (1 << (*p2)) | (*p4);
    u8 zero = 0;
    *p4 = value;
    if ((*p4) == 7)
    {
      *p4 = zero;
    }
    *((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x17) = zero;
  }
  g3 = (u32 *) 0x08671BD8;
  sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, D_0810205C[*p2], *g3);
}

