struct S_25FF0 { u8 pad[0x24]; u32 f24; u16 f28; };
extern struct S_25FF0 D_02025FF0;
extern u16 D_02025368[];
extern u16 D_02021E90[];
extern u32 D_08671BD0;
extern s32 sub_08084500(void *, void *, void *);
extern void sub_08085440(void *, void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
struct P130 { u8 pad[0x0E]; u16 f0E; u8 pad2[6]; u16 f16; };

s32 sub_0806B5B0(u8 *ent, u8 *s38, u8 *a5, u8 *a3)
{
  u32 *new_var;
  u16 *tbl = D_02025368;
  u8 *new_var3;
  u8 *new_var2;
  u8 z8;
  u32 z32;
  if ((*((s32 *) (a5 + 0x9C))) == 4) { goto ret0; }
  if (D_02025FF0.f24 != 0)
  {
    if ((D_02025FF0.f28 & tbl[0xEF * 2]) != 0) { goto ok; }
    goto ret0;
  }
  else
  {
    do { if ((D_02021E90[0x146C / 2] & tbl[0xEF * 2]) == 0) { goto ret0; } } while (0);
  }
  ok:
  sub_08084500(ent, s38, a5);
  *((s32 *) (a5 + 0x70)) = 1;
  sub_08085440(new_var2 = ent, s38, a5, 10);
  ((struct P130 *)*((struct P130 **)(a5 + 0x130)))->f0E = tbl[0xB8 * 2];
  z8 = 0;
  z32 = 0;
  ((struct P130 *)*((struct P130 **)(a5 + 0x130)))->f16 = 30;
  *((s32 *) (a5 + 0x48)) = z32;
  *((u8 *) ((new_var2 + ((*((s16 *) (new_var2 + 0x22))) * 2)) + 0x19)) = z8;
  new_var = &D_08671BD0;
  new_var3 = new_var2 + 0x18;
  {
    u32 *pd = new_var;
    sub_080C31E8(new_var3, new_var2 + 0x22, 10, *pd);
  }
  return 1;
  ret0:
  return 0;
}
