extern u8 gMainWorkspace[];
s32 sub_0806D35C(void *, void *, void *);
void sub_0806D588(void *, void *);
void sub_080C31E0(void *, void *);
s32 sub_080C364C(s32, s32);
void sub_08003740(void *, void *);
void sub_08005E80(s32);
void sub_08075564(void *arg0)
{
  u32 new_var;
  register void *p6c;
  register void *p4;
  register void *p38;
  register void *alias;
  p6c = *((void **) (((u8 *) arg0) + 0x6C));
  p4 = ((u8 *) p6c) + 4;
  p38 = *((void **) (((u8 *) arg0) + 0x38));
  alias = ((u8 *) p6c) + 4;
  if (sub_0806D35C(arg0, p38, p4) != 0)
  {
    return;
  }
  if (gMainWorkspace[0x14ED] != (*((u8 *) (((u8 *) p6c) + 0x55))))
  {
    sub_080C31E0(arg0, *((void **) (((u8 *) arg0) + 0x24)));
    return;
  }
  switch (*((u8 *) (((u8 *) p6c) + 0x55)))
  {
    case 0x37:
      if (gMainWorkspace[0x173A] != 7)
    {
      sub_080C31E0(arg0, *((void **) (((u8 *) arg0) + 0x24)));
      return;
    }
      if (((s16) (*((u16 *) (((u8 *) p38) + 4)))) > 0x100)
    {
      s32 off;
      s32 value;
      void *r5;
      *((u16 *) (((u8 *) p38) + 4)) = (*((u16 *) (((u8 *) p38) + 4))) - 0x80;
      *((u16 *) (((u8 *) p38) + 6)) = (*((u16 *) (((u8 *) p38) + 6))) + 0x20;
      r5 = *((void **) (((u8 *) p4) + 0x2C));
      off = 4;
      value = *((s16 *) (((u8 *) p38) + off));
      *((u16 *) (((u8 *) r5) + 6)) = sub_080C364C(0x1800, value);
      r5 = *((void **) (((u8 *) p4) + 0x2C));
      off = 6;
      value = *((s16 *) (((u8 *) p38) + off));
      *((u16 *) (((u8 *) r5) + 8)) = sub_080C364C(0x1300, value);
    }
      *((u16 *) (((u8 *) p38) + 2)) = (*((u16 *) (((u8 *) p38) + 2))) & 0xFFEF;
      *((u16 *) (((u8 *) p38) + 2)) = (*((u16 *) (((u8 *) p38) + 2))) | (0x10 & (*((u16 *) ((*((void **) ((*((void **) (((u8 *) arg0) + 0x28))) + 0x38))) + 2))));
      *((s32 *) (((u8 *) p4) + 0x14)) = (*((s32 *) (((u8 *) p4) + 0x14))) - 1;
      if ((*((s32 *) (((u8 *) p4) + 0x14))) == 0)
    {
      sub_08005E80(0xD9);
      *((s32 *) (((u8 *) p4) + 0x14)) = 0xA;
    }
      break;

    case 0x39:
      switch (*((volatile s32 *) (((u8 *) p4) + 0x54)))
    {
      case 0:
      {
        s32 v = (*((u16 *) (((u8 *) p38) + 4))) + 0x40;
        *((u16 *) (((u8 *) p38) + 4)) = v;
        *((u16 *) (((u8 *) p38) + 6)) = (*((u16 *) (((u8 *) p38) + 6))) - 0x40;
        if ((v << 16) > 0x013F0000)
        {
          *((volatile s32 *) (((u8 *) p4) + 0x54)) += 1;
        }
        break;
      }

      case 1:
      {
        s32 v = (*((u16 *) (((u8 *) p38) + 4))) - 0x10;
        *((u16 *) (((u8 *) p38) + 4)) = v;
        *((u16 *) (((u8 *) p38) + 6)) = (*((u16 *) (((u8 *) p38) + 6))) + 0x10;
        if ((v << 16) <= 0x01000000)
        {
          *((volatile s32 *) (((u8 *) p4) + 0x54)) += 1;
        }
        break;
      }

    }

    {
      s32 off;
      s32 value;
      void *r5;
      r5 = *((void **) (((u8 *) p4) + 0x2C));
      off = 4;
      value = *((s16 *) (((u8 *) p38) + off));
      *((u16 *) (((u8 *) r5) + 6)) = sub_080C364C(0x1200, value);
      r5 = *((void **) (((u8 *) p4) + 0x2C));
      off = 6;
      value = *((s16 *) (((u8 *) p38) + off));
      *((u16 *) (((u8 *) r5) + 8)) = sub_080C364C(0x1200, value);
    }
      break;

    case 0x3A:
      if (((s16) (*((u16 *) (((u8 *) p38) + 4)))) > 0x100)
    {
      s32 off;
      s32 value;
      void *r5;
      *((u16 *) (((u8 *) p38) + 4)) = (*((u16 *) (((u8 *) p38) + 4))) - 0x40;
      *((u16 *) (((u8 *) p38) + 6)) = (*((u16 *) (((u8 *) p38) + 6))) - 0x40;
      r5 = *((void **) (((u8 *) p4) + 0x2C));
      off = 4;
      value = *((s16 *) (((u8 *) p38) + off));
      *((u16 *) (((u8 *) r5) + 6)) = sub_080C364C(0x1200, value);
      r5 = *((void **) (((u8 *) p4) + 0x2C));
      off = 6;
      value = *((s16 *) (((u8 *) p38) + off));
      *((u16 *) (((u8 *) r5) + 8)) = sub_080C364C(0x1200, value);
    }
      *((s32 *) (((u8 *) p4) + 0x14)) = (*((s32 *) (((u8 *) p4) + 0x14))) - 1;
      if ((*((s32 *) (((u8 *) p4) + 0x14))) == 0)
    {
      sub_08005E80(0xDC);
      *((s32 *) (((u8 *) p4) + 0x14)) = 0xA;
    }
      break;

    default:
      break;

  }

  {
    u8 *d = gMainWorkspace;
    s32 off = 0x174C;
    u32 v;
    if (p4)
    {
      new_var = *((u32 *) (d + off));
      v = new_var;
      *((u32 *) (((u8 *) alias) + 0)) = v;
      off += 4;
      v = *((u32 *) (d + off));
      *((u32 *) (((u8 *) alias) + 4)) = v;
      sub_0806D588(p38, alias);
      *((u16 *) (((u8 *) p38) + 0)) = *((u16 *) (d + 0x18C2));
    }
    else
    {
      new_var = *((u32 *) (d + off));
      v = new_var;
      *((u32 *) (((u8 *) alias) + 0)) = v;
      off += 4;
      v = *((u32 *) (d + off));
      *((u32 *) (((u8 *) alias) + 4)) = v;
      sub_0806D588(p38, alias);
      *((u16 *) (((u8 *) p38) + 0)) = *((u16 *) (d + 0x18C2));
    }
  }
  sub_08003740(((u8 *) p4) + 0x1C, p38);
}

