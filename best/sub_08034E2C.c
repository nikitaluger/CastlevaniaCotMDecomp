#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
struct Big
{
  u8 pad[0x7C];
  u8 flag;
};
struct FFO
{
  u8 pad[0x18A8];
  u8 cam;
  u8 pad2[0x18C2 - 0x18A9];
  u16 val;
};
struct Unk7
{
  u16 unk0;
  u8 pad2[0x12];
  u32 unk14;
  u32 unk18;
  u32 unk1C;
  u8 pad20[0x60];
};
struct Unk9
{
  u8 unk0;
  u8 unk1;
  u8 unk2;
  u8 unk3;
  u16 unk4;
  u16 unk6;
  u16 unk8;
  u16 unkA;
  u16 unkC;
  u16 unkE;
  u32 unk10;
};
struct Unk6
{
  u8 pad0[8];
  u32 unk8;
  u32 unkC;
  u8 pad10[0xC];
  s16 unk1C;
  u8 pad1E[4];
  s16 unk22;
  u8 pad24[4];
  struct Unk9 *unk28;
  u8 pad2C[8];
  u8 unk34[1];
};
struct Unk5FAEC
{
  u8 pad0[0x7C];
  u8 unk7C;
};
struct BdEntry
{
  u16 a;
  u16 b;
  u16 c;
  u16 d;
};
extern struct Unk7 *sub_0800355C(void);
extern void sub_0800168C(void *arg0, int a, int b, int c);
extern struct Unk5FAEC *sub_0805FAEC(void *arg0, int a);
extern void sub_08014288(void *a, struct Unk6 *b, void (*c)(void));
extern void sub_08014290(void);
extern s32 sub_08013C2C(int a);
extern void sub_0801131C(struct Unk7 *a, u8 *b, void *c);
extern void sub_08011368(struct Unk7 *a, u8 *b, int c, int d);
extern struct Unk9 *sub_08016190(void);
extern void sub_080C31E0(void *a, u32 b);
extern void sub_080C31E4(u8 *a, s16 *b, u32 c);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_080CBDD0[];
extern u8 D_080CD400[];
extern u16 D_080CEE08[];
extern u32 D_08671BB0;
void sub_08034E2C(struct Big *arg0)
{
  struct Unk6 *p6;
  struct Unk7 *p7;
  s32 v;
  s32 bits;
  u8 zero;
  u8 *p34;
  struct Unk5FAEC *p;
  u16 *ee;
  u8 *tbl;
  int new_var;
  u32 *gp;
  u8 *entries;
  p7 = sub_0800355C();
  if (p7 == NULL)
  {
    goto fail;
  }
  U32(arg0, 0x38) = (u32) p7;
  if (arg0->flag == 0)
  {
    sub_0800168C(arg0, 0, 0x54, 0);
    if (U32(arg0, 0x3C) == 0)
    {
      goto fail;
    }
    p7->unk1C = 0x80000009;
    p = sub_0805FAEC(arg0, 0xE5);
    if (p != NULL)
    {
      p->unk7C = 1;
    }
  }
  else
  {
    sub_0800168C(arg0, 0, 0x6C, 0);
    if (U32(arg0, 0x3C) == 0)
    {
      goto fail;
    }
    p7->unk1C = 0x8000000A;
  }
  p6 = (struct Unk6 *) U32(arg0, 0x3C);
  p34 = ((u8 *) p6) + 0x34;
  sub_08014288(arg0, p6, sub_08014290);
  p6->unk1C = 0x18;
  p6->unk8 = U32(arg0, 0x4C);
  p6->unkC = U32(arg0, 0x5C);
  v = sub_08013C2C(0x18);
  p6->unk22 = v;
  if ((v << 16) < 0)
  {
    goto fail;
  }
  bits = ((p6->unk22 << 6) + 0x200) | ((v + 8) << 12);
  p7->unk0 = bits;
  p7->unk0 = bits | ((struct FFO *) D_02025FF0)->val;
  sub_0801131C(p7, p34, ((u8 *) D_080CD400) + (p6->unk1C * 12));
  sub_08011368(p7, p34, 0x19, 1);
  if (arg0->flag == 0)
  {
    ee = D_080CEE08;
    p6->unk28 = sub_08016190();
    if (p6->unk28 == NULL)
    {
      goto fail;
    }
    goto fields;
  }
  else
  {
    goto common;
  }
  fail:
  sub_080C31E0(arg0, U32(arg0, 0x24));

  return;
  fields:
  p6->unk28->unk1 = 1;

  p6->unk28->unk2 = 8;
  p6->unk28->unk3 = 1;
  tbl = D_080CBDD0;
  p6->unk28->unk4 = ((struct BdEntry *)(tbl + (p6->unk1C * 40)))->c;
  p6->unk28->unk6 = ee[0];
  p6->unk28->unk8 = ee[1];
  p6->unk28->unkA = ee[2];
  p6->unk28->unkC = ee[3];
  p6->unk28->unkE = ((struct BdEntry *)(tbl + (p6->unk1C * 40)))->d;
  p6->unk28->unk10 = (u32) p7;
  common:
  {
    u8 *pt = D_02021E90;
    u8 *pb = D_02025FF0;
    u8 *base1;
    u8 *base2;
    u32 idx;
    pb += 0x18A8;
    idx = ((u32)*pb + 1) * 0x40;
    base1 = pt + 0x1278;
    p7->unk14 = p6->unk8 - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);
    idx = ((u32)*pb + 1) * 0x40;
    base2 = pt + 0x127C;
    p7->unk18 = p6->unkC - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
  }
  zero = 0;
  U16(arg0, 0x02) = 0x1000 | U16(arg0, 0x02);
  U8(arg0, 0x19 + (((s16) U16(arg0, 0x22)) * 2)) = zero;
  gp = &D_08671BB0;
  entries = ((u8 *) arg0) + 0x18;
  sub_080C31E4(entries, (s16 *) (((u8 *) arg0) + 0x22), *gp);
  U8(arg0, 0x19 + (((s16) U16(arg0, 0x22)) * 2)) = U8(arg0, 0x19 + (((s16) U16(arg0, 0x22)) * 2)) + 1;
  new_var = ((s16) U16(arg0, 0x22)) * 2;
  sub_080C31E0(arg0, *((u32 *) (((u8 *) U32(arg0, 0x14)) + (entries[new_var] * 4))));
}
