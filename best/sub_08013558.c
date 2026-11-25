extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_080CB2B8[];
extern u8 D_080CBDD0[];
s32 sub_080C36E4(s16, s32);
void *sub_08016238(void *);
s32 sub_080133EC(u32, u32);
s32 sub_0806D5C4(u16, u16);
s32 sub_0806D5F8(u16, u16);
void sub_0808D7BC(s32, s32, s32, s32);
void sub_080158BC(void *, void *);
struct C13558
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
struct Ent13558
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
u32 sub_08013558(struct Ent13558 *b, struct C13558 *c, struct Ent13558 *d)
{
  struct Ent13558 *e = 0;
  u8 *new_var3;
  s16 idx;
  s32 r12;
  s32 r1;
  s32 r6;
  s32 t;
  u16 cf;
  u8 *p;
  int new_var;
  s32 a2a;
  int new_var2;
  s32 d2a;
  cf = (c->f0 &= 0xFFFD);
  d->f4 &= 0xFDFF;
  if (cf & 1)
  {
    *((u8 *) (((u8 *) d) + 1)) &= 0xFA;
    return 0;
  }
  if (c->f20 > 0)
  {
    idx = c->f20;
    t = (s16) sub_080C36E4(idx, 3);
    switch (t)
    {
      case 0:
        b->f0 = (b->f0 & 0x0FFF) | 0xD000;
        break;

      case 1:
        b->f0 = (b->f0 & 0x0FFF) | 0xC000;
        break;

    }

    c->f20 = c->f20 - 1;
    d->f4 |= 0x200;
    sub_08016238(d);
    return 0;
  }
  if (!((*((u8 *) (((u8 *) d) + 1))) & 4))
  {
    return 0;
  }
  p = D_02025FF0 + 0x18BE;
  if ((*((s16 *) p)) != 0)
  {
    idx = c->f1C;
    p = D_080CBDD0 + (((idx * 4) + idx) * 8);
    if (((*((s16 *) (p + 2))) != 0) && (c->f30 != 0))
    {
      if (!(c->f4 & 0x200))
      {
        if ((*((u16 *) (c->f30 + 2))) & 1)
        {
          if (!(c->f4 & 0x100))
          {
            if (sub_080133EC(c->f8, c->fC + 0x10000) != 1)
            {
              goto skip;
            }
          }
          p = D_080CB2B8 + (((idx * 4) + idx) * 4);
          new_var3 = D_02025FF0 + 0x174C;
          r12 = (u16) sub_0806D5C4(*((u16 *) (D_02025FF0 + 0x18BE)), *((u16 *) (p + 6)));
          do
          {
            if (((double) r12) <= 0)
            {
              r12 = 1;
            }
            c->f18 = c->f18 - r12;
            t = *((s32 *) new_var3);
            idx = d->f30;
            if (t < idx)
            {
              r6 = (((idx << 16) + 0x8000) + (*((u32 *) ((D_02021E90 + 0x1278) + ((((u8) (*(D_02025FF0 + 0x18A8))) + 1) << 6))))) - (d->f26 << 16);
            }
            else
            {
              r6 = (((idx << 16) + 0x8000) + (*((u32 *) ((D_02021E90 + 0x1278) + ((((u8) (*(D_02025FF0 + 0x18A8))) + 1) << 6))))) + (d->f26 << 16);
            }
            r1 = (((d->f32 << 16) + 0xFFFF8000) + (*((u32 *) ((D_02021E90 + 0x127C) + ((((u8) (*(D_02025FF0 + 0x18A8))) + 1) << 6))))) - (d->f28 << 16);
          }
          while (0);
          sub_0808D7BC(r6, r1, r12, 0);
          if (((s32) c->f18) <= 0)
          {
            c->f18 = 0;
 do { c->f0 |= 1; } while (0);
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
  }
  skip:
  e = (struct Ent13558 *) sub_08016238(d);

  if (e == 0)
  {
    return 0;
  }
  if (d->f4 & 0x100)
  {
    c->f0 |= 0x10;
    return (u32) e;
  }
  a2a = e->f2A & 0xF;
  d2a = d->f2A & 0xF;
  new_var = 0xC;
  new_var2 = 6;
  idx = c->f1C;
  p = D_080CB2B8 + (2 * (2 * ((idx * 4) + idx)));
  if ((d2a != 0) && (a2a == d2a))
  {
    r12 = ((u16) sub_0806D5F8(e->f2C, *((u16 *) (p + new_var2)))) >> 1;
  }
  else
  {
    r12 = (u16) sub_0806D5F8(e->f2C, *((u16 *) (p + new_var2)));
  }
  if (r12 <= 0)
  {
    r12 = 1;
  }
  if (r12 > 9999)
  {
    r12 = 9999;
  }
  c->f18 = c->f18 - r12;
  if (e->f30 < d->f30)
  {
    r6 = (((d->f30 << 16) + 0x8000) + (*((u32 *) ((D_02021E90 + 0x1278) + ((((u8) (*(D_02025FF0 + 0x18A8))) + 1) << new_var2))))) - (d->f26 << 16);
  }
  else
  {
    idx = (d->f30 << 16) + 0x8000;
    r6 = (idx + (*((u32 *) ((D_02021E90 + 0x1278) + ((((u8) (*(D_02025FF0 + 0x18A8))) + 1) << new_var2))))) + (d->f26 << 16);
  }
  r1 = (((d->f32 << 16) + 0xFFFF8000) + (*((u32 *) ((D_02021E90 + 0x127C) + ((((u8) (*(D_02025FF0 + 0x18A8))) + 1) << new_var2))))) - (d->f28 << 16);
  sub_0808D7BC(r6, r1, r12, 0);
  if (c->f30 != 0)
  {
    *((u32 *) (c->f30 + 8)) = (u32) e;
  }
  if (((s32) c->f18) <= 0)
  {
    if (a2a == 2)
    {
      if ((!(c->f0 & 0xC)) && (d2a != 2))
      {
        c->f18 = 1;
        c->f0 |= 4;
      }
      else
      {
        c->f18 = 0;
        c->f0 |= 1;
      }
    }
    else
      if (a2a == 5)
    {
      if ((!(c->f0 & new_var)) && (d2a != 5))
      {
        c->f18 = 1;
        c->f0 |= 8;
      }
      else
      {
        c->f18 = 0;
        c->f0 |= 1;
      }
    }
    else
    {
      c->f18 = 0;
      c->f0 |= 1;
    }
  }
  else
  {
    c->f0 |= 2;
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
  return (u32) e;
}
