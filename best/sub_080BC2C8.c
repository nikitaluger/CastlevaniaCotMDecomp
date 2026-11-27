struct S_02025FF0
{
  u8 _0[0x18C2];
  u16 w;
};
extern struct S_02025FF0 gMainWorkspace;
struct E
{
  u8 _0;
  u8 f1;
  u8 f2;
  u8 f3;
  u16 f4;
  u16 f6;
  u16 f8;
  u16 fA;
  u16 fC;
  s16 fE;
  u32 f10;
};
struct P
{
  u8 _0[8];
  u32 f8;
  u32 fC;
  u32 f10;
  u32 f14;
  u8 _18[4];
  s16 f1C;
  u8 _1E[4];
  s16 f22;
  u8 _24[4];
  struct E *f28;
};
struct Actor
{
  u16 f0;
  u16 f2;
  u8 _4[0x14 - 4];
  void *f14;
  u8 _18[0x22 - 0x18];
  s16 f22;
  void *f24;
  u8 _28[0x38 - 0x28];
  void *f38;
  void * volatile f3C;
  u8 _40[0x5C - 0x40];
  u32 f5C;
  u8 _60[0x6C - 0x60];
  s32 f6C;
  u8 _70[0x7C - 0x70];
  u32 f7C;
  u8 _80[0x8C - 0x80];
  s32 f8C;
};
struct BD
{
  u8 _0[4];
  u16 f4;
  u16 f6;
  u8 _8[0x20];
};
extern struct BD gEffectGfxTable[];
extern u16 D_08102F10[];
extern u16 D_08102F1C[];
extern void *gMainObjTimerCallbacks;
void *allocSpriteObject(void);
void allocWorkSlot(void *, s32, s32, s32);
s32 sub_080057F8(void);
s32 scaleByRandom(s32);
s32 sub_0800583C(s32);
void initSpriteGraphics(void *, void *, s32);
void setAnimationFrame(void *, void *, s32, s32);
s32 findKindIndex(s16);
void installUpdateHandler(void *, void *, void *);
void *allocEffectPart(void);
void sub_080BC73C(void *, void *, void *);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, void *);
void updateActorEffectSubObject(void);
void sub_080BC2C8(struct Actor *actor)
{
  s32 sprite;
  struct P *work;
  u8 *animState;
  u16 *defaults;
  s32 value;
  s32 heading;
  u8 *scriptPtr;
  void **scriptTablePtr;
  u8 *scriptEntry;

  sprite = (s32)allocSpriteObject();
  if (sprite == 0) goto fail;
  actor->f38 = (void *)sprite;
  allocWorkSlot(actor, 0, 0x48, 0);
  if (actor->f3C == NULL) goto fail;
  *((u32 *)(sprite + 0x1C)) = 0x80000009;
  work = (struct P *)actor->f3C;
  animState = ((u8 *)work) + 0x34;
  installUpdateHandler(actor, (u8 *)work, updateActorEffectSubObject);
  work->f1C = 0x68;
  value = findKindIndex(0x68);
  work->f22 = value;
  if ((s16)value < 0) goto fail;
  heading = work->f22;
  heading = heading << 6;
  heading = heading + 0x200;
  heading &= 0xFC0;
  *((u16 *)sprite) = heading;
  *((u16 *)sprite) |= gMainWorkspace.w;
  initSpriteGraphics((void *)sprite, animState, (s32)D_08102F10);
  setAnimationFrame((void *)sprite, animState, 0, 1);
  defaults = D_08102F1C;
  work->f28 = allocEffectPart();
  if (work->f28 == NULL) goto fail;
  goto ok;
fail:
  sub_080C31E0(actor, actor->f24);
  return;
ok:
  work->f28->f1 = 5;
  work->f28->f2 = 8;
  work->f28->f3 = 1;
  work->f28->f4 = gEffectGfxTable[work->f1C].f4;
  work->f28->f6 = defaults[0];
  work->f28->f8 = defaults[1];
  work->f28->fA = defaults[2];
  work->f28->fC = defaults[3];
  work->f28->fE = gEffectGfxTable[work->f1C].f6;
  work->f28->f10 = (u32)sprite;
  *((u32 *)((u8 *)actor + 0x6C)) = scaleByRandom(0x200000) - (-0x100000);
  *((u32 *)((u8 *)actor + 0x7C)) = 0xFFFF & sub_080057F8();
  value = sub_0800583C(0x180);
  *((s32 *)((u8 *)actor + 0x8C)) = value;
  if (value < 0)
  {
    value = value - 0x80;
  }
  else
  {
    value = value + 0x80;
  }
  *((s32 *)((u8 *)actor + 0x8C)) = value;
  *((u32 *)((u8 *)actor + 0x5C)) = 1;
  *((u32 *)((u8 *)actor + 0x9C)) = 0;
  sub_080BC73C(actor, (void *)sprite, work);
  actor->f2 |= 0x1000;
  {
    s16 idx = actor->f22;
    *((u8 *)(((u32)idx * 2) + (u32)actor + 0x19)) = 0;
  }
  scriptTablePtr = &gMainObjTimerCallbacks;
  scriptPtr = ((u8 *)actor) + 0x18;
  sub_080C31E4(scriptPtr, ((u8 *)actor) + 0x22, *scriptTablePtr);
  {
    s16 idx = actor->f22;
    *((u8 *)(((u32)idx * 2) + (u32)actor + 0x19)) += 1;
    idx = actor->f22;
    scriptEntry = scriptPtr + ((u32)idx * 2);
    sub_080C31E0(actor, *((void **)((u8 *)actor->f14 + ((*scriptEntry) * 4))));
  }
}
