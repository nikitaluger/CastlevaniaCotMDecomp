void sub_0800FEDC(s32, void *);
s32 sub_0800EBDC(s16, s16, void *);
void sub_0806D930(void *);
extern u8 gGameStatus[];
extern u8 gMenuState[];
extern u16 D_080CB052[];
static inline u32 inline_fn(u16 arg0)
{
  return ((u32) arg0) << 1;
}

void sub_0800EDAC(s32 arg0)
{
  s16 new_var;
  s32 vals[4];
  u8 *obj;
  u8 *state;
  u8 *base;
  u16 *g;
  u32 i;
  u32 *p;
  u16 *tbl;
  s32 *vp;
  u16 *dest;
  u16 val;
  u32 x2;
  g = (u16 *) gGameStatus;
  if (arg0 == 0)
  {
    base = gMenuState;
    state = base + 0x6A;
    obj = base;
    if ((*((s8 *) state)) != 3)
    {
      goto body;
    }
  }
  clear:
  sub_0800FEDC(5, (void *) 0x06007178);

  sub_0800FEDC(5, (void *) 0x060071B8);
  sub_0800FEDC(5, (void *) 0x060071F8);
  sub_0800FEDC(5, (void *) 0x06007238);
  return;
  body:
  switch (*((s8 *) state))
  {
    case 0:
    {
      u8 *q;
      s8 idx;
      u8 val;
      idx = obj[0x6B];
      q = obj + 0x73;
      val = q[idx];
      q -= 0x31;
      *q = val;
      break;
    }

    case 1:
    {
      u8 *q = obj - (-((s8) obj[0x6C]));
      u8 val = q[0x93];
      obj[0x43] = val;
      break;
    }

    case 2:
    {
      u8 *q = obj + ((s8) obj[0x6D]);
      u8 val = q[0xB3];
      obj[0x44] = val;
      break;
    }
      do
    {
    }
    while (0);

  }


  sub_0806D930(obj);
  state = (u8 *) g;
  vals[0] = sub_0800EBDC(*((s16 *) (obj + 0x1C)), *((s16 *) (state + 0x2E0)), (void *) 0x06007178);
  vals[1] = sub_0800EBDC(*((s16 *) (obj + 0x24)), *((s16 *) (((u8 *) g) + 0x2E8)), (void *) 0x060071B8);
  vals[2] = sub_0800EBDC(*((s16 *) (obj + 0x2C)), new_var = *((s16 *) (((u8 *) g) + 0x2F0)), state = (void *) 0x060071F8);
  vals[3] = sub_0800EBDC(*((s16 *) (obj + 0x34)), *((s16 *) (((u8 *) g) + 0x2F8)), (void *) 0x06007238);
  i = 0;
  tbl = D_080CB052;
  vp = vals;
  p = (u32 *) tbl;
  for (; i < (3 + 1); i++)
  {
    u32 off;
    u8 *t2;
    u16 y;
    u32 h;
    u16 x;
    u32 h2;
    u16 *dest;
    s32 v;
    u16 *p2;
    off = 2;
    off = i << off;
    t2 = ((u8 *) tbl) + 2;
    off += (u32) t2;
    y = *((u16 *) ((u8 *) off));
    h = ((u32) y) << 6;
    x = *((u16 *) p);
    off = inline_fn(x);
    x2 = off;
    h2 = x2 + 0x7000;
    dest = (u16 *) ((h + h2) + 0x06000000);
    v = *vp;
    switch (v)
    {
      case -1:
        val = 0x712C;
        break;

      default:
        goto skip;

      case 0:
        val = 0x512B;
        break;

      case 1:
        val = 0x612A;
        break;

    }

    *dest = val;
    skip:
    vp++;

    p++;
  }

}

