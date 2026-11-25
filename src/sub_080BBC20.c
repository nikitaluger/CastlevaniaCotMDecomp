extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern s32 sub_08013C2C(void);
extern void sub_08014288(void *, void *, void *);
extern void sub_080BE528(void *, void *, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097D90(void);
struct S_02025FF0 { u8 _0[0x18C2]; u16 f18C2; };
extern struct S_02025FF0 D_02025FF0;
extern u32 D_08671BB0;
extern u8 D_08102F08[];
struct Entity {
  u8 _0[2]; u16 flags; u8 _1[0x14 - 4]; u32 funcTable; u8 _2[0x22 - 0x18];
  s16 animIdx; u32 handlerArg; u8 _3[0x38 - 0x28]; u32 gfx; u32 child;
  u8 _4[0x5C - 0x40]; u32 tableIdx;
};
struct GfxObj { u16 flags; u8 _0[0x1C - 2]; u32 kind; u8 _1[0x2A - 0x20]; u8 f2A; };
struct Child { u8 _0[0x1C]; u16 param; u8 _1[0x22 - 0x1E]; u16 result; };

/* Sets up an entity's graphics object and child, flags it as active, and dispatches
 * the function selected by its per-animation state byte. */
void sub_080BBC20(struct Entity *arg)
{
  struct GfxObj *gfx;
  struct Child *child;
  u8 *childSub;
  s32 value;
  u8 *arg18;
  u32 v;
  u32 func;
  s16 i;
  u16 *arr;
  u16 *entry;
  gfx = sub_0800355C();
  if (gfx == NULL) goto Lend;
  arg->gfx = (u32)gfx;
  sub_0800168C(arg, 0, 0x48, 0);
  if (arg->child == 0) goto Lend;
  gfx->kind = 0x8000000B;
  child = (struct Child *)arg->child;
  childSub = ((u8 *)child) + 0x34;
  sub_08014288(arg, child, &sub_08097D90);
  child->param = 0x68;
  value = sub_08013C2C();
  child->result = value;
  if ((value << 16) >= 0) goto Lcont;
Lend:
  sub_080C31E0(arg, arg->handlerArg);
  return;
Lcont:
  gfx->flags = gfx->flags | D_02025FF0.f18C2;
  sub_080BE528(gfx, childSub, D_08102F08[arg->tableIdx], 3);
  arg->flags = arg->flags | 0x1000;
  i = arg->animIdx;
  arr = (u16 *)arg;
  ((u8 *)(&arr[i]))[0x19] = 0;
  {
    u32 *handlerSlot = &D_08671BB0;
    arg18 = ((u8 *)arg) + 0x18;
    sub_080C31E4(arg18, ((u8 *)arg) + 0x22, *handlerSlot);
  }
  i = arg->animIdx;
  arr = (u16 *)arg;
  ((u8 *)(&arr[i]))[0x19] = ((u8 *)(&arr[i]))[0x19] + 1;
  i = arg->animIdx;
  arr = (u16 *)arg18;
  entry = &arr[i];
  v = ((u8 *)entry)[0];
  func = *((u32 *)(((u8 *)arg->funcTable) + (v * 4)));
  sub_080C31E0(arg, func);
}
