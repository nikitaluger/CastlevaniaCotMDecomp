extern s32 sub_08007EA8(s32);
extern void sub_080014D0(u32 *, s32);
extern u8 D_02025358[];
extern u8 D_02025FF0[];
void sub_08087970(void)
{
  unsigned long new_var;
  u8 *q = D_02025358;
  u8 *p = D_02025FF0;
  int new_var3;
  u8 *p2 = p;
  s32 val;
  u32 *new_var5;
  u8 t;
  u8 *new_var2;
  u8 *new_var4;
  new_var4 = p;
  switch ((new_var4[0x50] << 8) + new_var4[0x51])
  {
    case 0x0E0B:

    case 0x0E0E:

    case 0x0E0F:

    case 0x0E12:
      new_var5 = (u32 *) (&p[0x10]);

    case 0x0E05:

    case 0x0E08:

    case 0x0E14:

    case 0x0E17:
      *((u32 *) (&p[0x10])) = 0x14;
      break;

    case 0x0E01:

    case 0x0E02:

    case 0x0E03:

    case 0x0E07:

    case 0x0E09:

    case 0x0E0D:

    case 0x0E11:

    case 0x0E13:
      new_var = 0;
      new_var = (sub_08007EA8(0xB6) != new_var) && (sub_08007EA8(0xBD) == 0);

    case 0x0E16:
      *((u32 *) (&p2[0x10])) = 0x12;
      break;

    case 3:
      *new_var5 = 0x0F;
      break;

    case 0:
      if (1)
    {
      if ((q[0x0C] == 0) && (sub_08007EA8(0x31) == 0))
      {
        *new_var5 = 1;
      }
    }
      break;

    case 0x0715:
      if (new_var)
    {
      new_var3 = 0x7B;
      *new_var5 = 6;
      sub_080014D0((u32 *) (&p[0x1864]), new_var3);
    }
      break;

    case 0x0E04:
      t = new_var4[0x53];
      if ((t == 3) || (t == 7))
    {
      *new_var5 = 0x11;
    }
      break;

    case 0x0E0A:
      t = p[0x53];
      if ((t == 9) || (t == 0x0D))
    {
      *new_var5 = 0x11;
    }
      break;

    case 0x0E0C:
      t = p[0x53];
      if ((t == 0x0B) || (t == 0x0E))
    {
      *new_var5 = 0x13;
    }
      t = new_var2[0x53];
      if (t == 0x11)
    {
      *new_var5 = t;
    }
      break;

    case 0x0E06:
      t = new_var2[0x53];
      if ((t == 5) || (t == 8))
    {
      *new_var5 = 0x13;
    }
      t = new_var2[0x53];
      if ((t == 0x13) || (t == 0x16))
    {
      *new_var5 = 0x11;
    }
      break;

    case 0x0E10:
      t = new_var2[0x53];
      if ((t == 0x0F) || (t == 0x12))
    {
      *new_var5 = 0x13;
    }
      break;

    case 0x0E15:
      if (p[0x53] == 0x14)
    {
      *((u32 *) ((0, &p[0x10]))) = 0x13;
    }
      break;

    case 0x0E18:
      *new_var5 = 0x13;
      break;

  }

}

