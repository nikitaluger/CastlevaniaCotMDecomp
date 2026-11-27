extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern s32 findKindIndex(void);
extern void installUpdateHandler(void *, void *, void *);
extern void initSpriteGfx(void *, void *, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void releaseActorEffectSubObject(void);

struct S_02025FF0
{
  u8 _0[0x18C2];
  u16 f18C2;
};
extern struct S_02025FF0 gMainWorkspace;
extern u32 gMainObjTimerCallbacks;

struct Entity
{
  u8 _0[2];
  u16 flags;
  u8 _1[0x14 - 4];
  u32 funcTable;
  u8 _2[0x22 - 0x18];
  s16 animIdx;
  u32 handlerArg;
  u8 _3[0x38 - 0x28];
  u32 gfx;
  u32 child;
};
struct GfxObj
{
  u16 flags;
  u8 _0[0x1C - 2];
  u32 kind;
  u8 _1[0x2A - 0x20];
  u8 f2A;
};
struct Child
{
  u8 _0[0x1C];
  u16 param;
  u8 _1[0x22 - 0x1E];
  u16 result;
};

/* Sets up an entity's graphics object and child, flags it as active, and dispatches
 * the function selected by its per-animation state byte. */
void sub_080BBE14(struct Entity *arg)
{
  struct GfxObj *gfx;
  struct Child *child;
  u8 *childSub;
  s32 value;
  u8 *statePtr;
  s16 i;
  u16 *arr;

  gfx = allocSpriteObject();
  if (gfx == NULL)
  {
    goto Lend;
  }
  arg->gfx = (u32) gfx;
  allocWorkSlot(arg, 0, 0x48, 0);
  if (arg->child == 0)
  {
    goto Lend;
  }
  gfx->kind = 0x8000000B;
  gfx->f2A &= 0xBF;
  child = (struct Child *) arg->child;
  childSub = (u8 *)child + 0x34;
  installUpdateHandler(arg, child, &releaseActorEffectSubObject);
  child->param = 0x68;
  value = findKindIndex();
  child->result = value;
  if ((value << 16) >= 0)
  {
    goto Lcont;
  }
Lend:
  sub_080C31E0(arg, arg->handlerArg);
  return;
Lcont:
  gfx->flags |= gMainWorkspace.f18C2;
  initSpriteGfx(gfx, childSub, 0xAD, 2);
  arg->flags |= 0x1000;
  i = arg->animIdx;
  arr = (u16 *) arg;
  ((u8 *)(&arr[i]))[0x19] = 0;
  {
    u32 *handlerSlot = &gMainObjTimerCallbacks;
    statePtr = (u8 *)arg + 0x18;
    sub_080C31E4(statePtr, (u8 *)arg + 0x22, *handlerSlot);
  }
  i = arg->animIdx;
  arr = (u16 *) arg;
  ((u8 *)(&arr[i]))[0x19]++;
  i = arg->animIdx;
  arr = (u16 *)statePtr;
  statePtr = (u8 *)&arr[i];
  {
    u8 funcIndex = *statePtr;
    u32 func = *(u32 *)((u8 *)arg->funcTable + funcIndex * 4);
    sub_080C31E0(arg, func);
  }
}
