extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_080CB2B8[];
extern u8 D_080CBDD0[];
s32 sub_080C2F24(s16, s32);
void *sub_08016238(void *);
s32 sub_080133EC(u32, u32);
s32 sub_0806D5C4(u16, u16);
void sub_0808D7BC(s32, s32, s32, s32);
void sub_080158BC(void *, void *);
struct C
{
  u16 f0;
  u8 pad02[2];
  u16 f4;
  u8 pad06[2];
  u32 f8;
  u32 fC;
  u8 pad10[8];
  u32 f18;
  s16 f1C;
  u8 pad1E[2];
  s16 f20;
  u8 pad22[14];
  u32 f30;
};
struct Ent
{
  u16 f0;
  u8 pad02[2];
  u16 f4;
  u8 pad06[0x20];
  s16 f26;
  s16 f28;
  u16 f2A;
  u16 f2C;
  s16 f2E;
  s16 f30;
  s16 f32;
};
inline int inline_fn(u32 arg0, int arg1)
{
  return arg0 + arg1;
}

u32 sub_08097F88(s32 a, struct Ent *b, struct C *c, struct Ent *d)
{
  u8 *new_var6;
  u8 *new_var;
  struct Ent *e;
  s16 idx;
  u8 *new_var3;
  s32 r12;
  s32 r6;
  u8 *new_var2;
  u8 *new_var4;
  u8 *new_var5;
  s32 r1;
  u16 cf;
  u8 *p;
  if ((a == 0) || (a == 3))
  {
    c->f0 &= 0xFFFD;
  }
  d->f4 &= 0xFDFF;
  ;
  if (c->f0 & 1)
  {
    *((u8 *) (((u8 *) d) + 1)) &= 0xFA;
    return 0;
  }
  if (c->f20 > 0)
  {
    if (((u32) (a - 2)) <= 1)
    {
      idx = c->f20;
      r1 = sub_080C2F24(idx, 3);
      switch (r1)
      {
        case 0:
          b->f0 = (b->f0 & 0x0FFF) | 0xD000;
          break;

        case 1:
          b->f0 = (b->f0 & 0x0FFF) | 0xC000;
          break;

      }

      c->f20 = c->f20 - 1;
    }
    d->f4 |= 0x200;
    sub_08016238(d);
    return 0;
  }
  if (c->f0 & 2)
  {
    return 0;
  }
  if (!((*((u8 *) (((u8 *) d) + 1))) & 4))
  {
    return 0;
  }
  p = D_02025FF0 + 0x18BE;
  if ((*((s16 *) p)) != 0)
  {
    new_var2 = D_080CBDD0;
    idx = c->f1C;
    p = new_var2 + (2 * ((2 * inline_fn(idx * 4, idx)) * 2));
    new_var6 = D_02025FF0;
    new_var3 = p;
    if (((*((s16 *) (new_var3 + 2))) != 0) && (c->f30 != 0))
    {
      if (!(c->f4 & 0x200))
      {
        if (!(c->f4 & 0x100))
        {
          if (sub_080133EC(c->f8, inline_fn(c->fC, 0x10000)) != 1)
          {
            goto skip;
          }
        }
        idx = c->f1C;
        r1 = 0x18BE;
        p = D_080CB2B8 + (inline_fn(idx * 4, idx) * 4);
        r12 = (u16) sub_0806D5C4(*((u16 *) (D_02025FF0 + r1)), *((u16 *) (p + 6)));
        if (r12 <= 0)
        {
          r12 = 1;
        }
        c->f18 = c->f18 - r12;
        r1 = *((s32 *) (D_02025FF0 + 0x174C));
        idx = d->f30;
        if (r1 < idx)
        {
          new_var4 = (D_02021E90 + 0x1278) + (inline_fn((u8) (*(D_02025FF0 + 0x18A8)), 1) << 6);
          r6 = inline_fn(inline_fn(idx << 16, 0x80 << 8), *((u32 *) new_var4)) - (d->f26 << 16);
        }
        else
        {
          new_var = D_02021E90;
          r6 = inline_fn(inline_fn(inline_fn(idx << 16, 0x80 << 8), *((u32 *) ((new_var + 0x1278) + (inline_fn((u8) (*(new_var6 + 0x18A8)), 1) << 6)))), d->f26 << 16);
        }
        r1 = inline_fn(inline_fn(d->f32 << 16, 0xFFFF8000), *((u32 *) ((D_02021E90 + 0x127C) + (inline_fn((u8) (*(D_02025FF0 + 0x18A8)), 1) << 6)))) - (d->f28 << 16);
        sub_0808D7BC(r6, r1, r12, 0);
        if (((s32) c->f18) <= 0)
        {
          c->f18 = 0;
          c->f0 |= 1;
        }
        else
        {
          c->f0 |= 2;
        }
        c->f20 = 0x1E;
        return 0;
      }
    }
  }
  skip:
  e = (struct Ent *) sub_08016238(d);

  if (e == 0)
  {
    return 0;
  }
  if (d->f4 & 0x100)
  {
    c->f0 |= 0x10;
    return (u32) e;
  }
  {
    s32 a2a = e->f2A & 0xF;
    short d2a = d->f2A & 0xF;
    new_var5 = D_02021E90;
    idx = c->f1C;
    new_var2 = D_080CB2B8;
    p = new_var2 + (inline_fn(idx * 4, idx) * 4);
    r12 = (u16) sub_0806D5C4(e->f2C, *((u16 *) (p + 6)));
    if ((d2a != 0) && (a2a == d2a))
    {
      r12 >>= 1;
    }
    if (r12 <= 0)
    {
      r12 = 1;
    }
    c->f18 = c->f18 - r12;
    if (e->f30 < d->f30)
    {
      r6 = inline_fn(inline_fn(d->f30 << 16, 0x80 << 8), *((u32 *) ((new_var5 + 0x1278) + (inline_fn((u8) (*(D_02025FF0 + 0x18A8)), 1) << 6)))) - (d->f26 << 16);
    }
    else
    {
      r6 = inline_fn(inline_fn(inline_fn(d->f30 << 16, 0x80 << 8), *((u32 *) ((new_var5 + 0x1278) + (inline_fn((u8) (*(D_02025FF0 + 0x18A8)), 1) << 6)))), d->f26 << 16);
    }
    r1 = inline_fn(inline_fn(d->f32 << 16, 0xFFFF8000), *((u32 *) ((new_var5 + 0x127C) + (inline_fn((u8) (*(D_02025FF0 + 0x18A8)), 1) << 6)))) - (d->f28 << 16);
    sub_0808D7BC(r6, r1, r12, 0);
    if (c->f30 != 0)
    {
      do
      {
        *((u32 *) inline_fn(c->f30, 8)) = (u32) e;
      }
      while (0);
    }
    if (!(((s32) c->f18) <= 0))
    {
      c->f0 |= 2;
    }
    else
    {
      c->f18 = 0;
      c->f0 |= 1;
    }
    if (e->f2E != 0)
    {
      c->f20 = e->f2E;
    }
    else
    {
      c->f20 = 0x1E;
    }
    sub_080158BC(c, e);
  }
  return (u32) e;
}

