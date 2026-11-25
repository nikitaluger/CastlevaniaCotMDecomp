extern void *sub_08016190(void);
extern void sub_080161F0(void *);
extern void sub_0806D2D0(void *);
extern u32 sub_0806D62C(u32, u32);
extern void sub_08003A6C(void *, u32, void *);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_080C31E0(void *, u32);
extern void sub_0808449C(void);
extern u8 D_02025368[];
extern u8 D_084DFF10[];
extern u32 D_08671BB0;
struct Sprite
{
  u8 pad0;
  u8 f1;
  u8 f2;
  u8 f3;
  u16 f4;
  u16 f6;
  u16 f8;
  u16 fA;
  u16 fC;
  u16 fE;
  u32 f10;
  u8 pad1[2];
  u16 f16;
  u16 f18;
};
struct S
{
  u32 f0;
  u32 f4;
  u8 pad[8];
  u32 f10;
  u8 pad2[4];
  u32 f18;
  u8 f1C[0x10];
  struct Sprite *sprite0;
  struct Sprite *sprite1;
  u32 f34;
  u32 f38;
  u32 f3C;
};
struct Obj
{
  u8 pad[0x14];
  u32 table;
  u8 arr[0x0A];
  s16 idx;
  u32 callback;
  u8 pad2[0x38 - 0x28];
  void *ptr38;
  u8 pad3[0x6C - 0x3C];
  void *ptr6C;
  u8 pad4[0x7C - 0x70];
  u32 val7C;
  u8 pad5[0x8C - 0x80];
  u32 val8C;
  u8 pad6[0x9C - 0x90];
  u32 val9C;
};
void sub_0807B1C4(struct Obj *arg0)
{
  int r4;
  struct Obj *r6;
  struct S *r7;
  u8 *r8;
  int new_var;
  void *r9;
  struct S *r10;
  struct Sprite **arr;
  r8 = D_02025368;
  r6 = arg0;
  r7 = (struct S *) (((u8 *) r6->ptr6C) + 4);
  r10 = r7;
  r9 = r6->ptr38;
  arr = &r7->sprite0;
  r4 = 0;
  for (;;)
  {
    arr[r4] = sub_08016190();
    if (arr[r4] == 0)
    {
      if (r7->sprite0 != 0)
      {
        sub_080161F0(r7->sprite0);
      }
      if (r7->sprite1 != 0)
      {
        sub_080161F0(r7->sprite1);
      }
      sub_0806D2D0(r6);
      return;
    }
    r4++;
    if (r4 > 1)
    {
      break;
    }
  }

  r7->sprite0->f1 = 0;
  r7->sprite0->f2 = 2;
  r7->sprite0->f3 = 8;
  r7->sprite0->f4 = *(r8 + 0x304);
  r7->sprite0->f6 = 7;
  r7->sprite0->f8 = 0x15;
  r7->sprite0->fA = 0xFFF8;
  r7->sprite0->fC = 0x1B;
  r8 = r8 + 0x2E2;
  r7->sprite0->fE = sub_0806D62C(*((u16 *) r8), 0x64);
  r7->sprite0->f16 = 5;
  r7->sprite0->f18 = 0x5D;
  r7->sprite0->f10 = (u32) r9;
  r7->sprite1->f1 = 0;
  r7->sprite1->f2 = 2;
  r7->sprite1->f3 = 8;
  r7->sprite1->f4 = *(r8 - 0x22);
  r7->sprite1->f6 = 7;
  r7->sprite1->f8 = 0x15;
  r7->sprite1->fA = 3;
  r7->sprite1->fC = 0xFFF2;
  r7->sprite1->fE = sub_0806D62C(*((u16 *) r8), 0x47);
  r7->sprite1->f16 = 5;
  r7->sprite1->f18 = 0x5D;
  r7->sprite1->f10 = (u32) r9;
  r7->f34 = 0;
  r7->f38 = 0;
  r7->f3C = 0;
  r10->f18 = r6->callback;
  r6->callback = (u32) sub_0808449C;
  *((u32 *) (((u8 *) r9) + 0x24)) = 0x084DFEF8;
  new_var = 0;
  sub_08003A6C(((u8 *) r7) + 0x1C, new_var, D_084DFF10);
  r7->f0 = r6->val7C;
  r10->f4 = r6->val8C;
  r10->f10 = r6->val9C;
  ;
  *((((u8 *) r6) + (r6->idx * 2)) + 0x19) = 0;
  sub_080C31E4(((u8 *) r6) + 0x18, (void *) (&r6->idx), D_08671BB0);
  r4 = r6->idx;
  *((((u8 *) r6) + (r4 * 2)) + 0x19) = (*((((u8 *) r6) + (r4 * 2)) + 0x19)) + 1;
  r4 = r6->idx;
  sub_080C31E0(r6, *((u32 *) (r6->table + (((u32) (*((((u8 *) r6) + 0x18) + (r4 * 2)))) * 4))));
}

