struct GameState_B8C84 { u8 _0[0x18C2]; u16 w; };
extern struct GameState_B8C84 gMainWorkspace;
struct SubObj { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; s16 fE; u32 f10; };
struct Work { u8 _0[8]; u32 f8; u32 fC; u32 f10; u32 f14; u8 _18[4]; s16 f1C; u8 _1E[4]; s16 f22; u8 _24[4]; struct SubObj *f28; };
struct KindData { u8 _0[8]; u16 f8; u16 fA; u8 _C[0x1C]; };
extern struct KindData gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern u16 D_08102DF0[];
extern u32 D_08102DF8[];
extern void *gMainObjTimerCallback;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_08014668(void *, s32);
extern void sub_080146D0(void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080B98B8(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);
inline int addOffset(s32 ptr, int off) { return ptr + off; }
/* Enemy setup: allocate sprite/work, install the state handler, derive
 * kind-specific animation and placement from lookup tables, attach a
 * sub-object, spawn extras and start the first script step. */
void sub_080B8C84(u8 *self)
{
  s32 sprite;
  u8 *handlerTable;
  struct Work *work;
  u8 *anim;
  s32 kindIndex;
  u8 *scriptState;
  void **scriptTable;
  u8 *stepCmd;
  u16 *paletteData;
  u32 variant;
  u32 base;
  u32 off;
  u32 addr1;
  u32 scale;
  u32 pos;
  sprite = (s32) allocSpriteObject();
  if (sprite == 0) goto fail;
  *(u32 *)(self + 0x38) = sprite;
  allocWorkSlot(self, 0, 0x48, 0);
  if (*(u32 *)(self + 0x3C) == 0) goto fail;
  *(u32 *)(sprite + 0x1C) = 2;
  variant = 0;
  work = (struct Work *) *((u32 *) (self + 0x3C));
  anim = ((u8 *) work) + 0x34;
  installUpdateHandler(self, (u8 *) work, sub_08097DC8);
  work->f1C = 0x67;
  work->f8 = *((u32 *) (self + 0x5C));
  work->fC = *((u32 *) (self + 0x6C));
  kindIndex = findKindIndex(0x67);
  work->f22 = kindIndex;
  if ((kindIndex << 16) < 0) goto fail;
  kindIndex = work->f22;
  kindIndex = kindIndex << 6;
  kindIndex = kindIndex + 0x200;
  kindIndex &= 0xFC0;
  *(u16 *) sprite = kindIndex;
  *(u16 *) sprite |= gMainWorkspace.w;
  initSpriteGraphics((void *) sprite, anim, addOffset((*(s16 *)((u8 *)work + 0x1C)) * 0xC, (s32)gSpriteAnimDataTable));
  setAnimationFrame((void *) sprite, anim, 0x11, 1);
  if (*((u32 *) (self + 0x7C)) == 1) variant = 1;
  base = (u32)D_08102DF8;
  off = variant * 8;
  addr1 = base + off;
  base = base + 4;
  off = off + base;
  off = *(u32 *)off;
  scale = (*(u32 *)(self + 0x4C)) * off;
  pos = *(u32 *)addr1;
  pos += scale;
  sub_080146D0((void *) work, pos, 0x40000);
  sub_08014668((void *) sprite, *((s32 *) (((u8 *) work) + 0x10)));
  paletteData = D_08102DF0;
  work->f28 = allocEffectPart();
  if (work->f28 != NULL) goto setupSubObj;
fail:
  sub_080C31E0(self, *(void **)(self + 0x24));
  return;
setupSubObj:
  work->f28->f1 = 5;
  work->f28->f2 = 8;
  work->f28->f3 = 1;
  work->f28->f4 = gEffectGfxTable[work->f1C].f8;
  work->f28->f6 = paletteData[0];
  work->f28->f8 = paletteData[1];
  work->f28->fA = paletteData[2];
  work->f28->fC = paletteData[3];
  handlerTable = self + 0x14;
  work->f28->fE = gEffectGfxTable[work->f1C].fA;
  work->f28->f10 = (u32) sprite;
  sub_080B98B8(self, 1, 4, *((u32 *) (sprite + 0x1C)));
  *(u16 *) (self + 2) |= 0x1000;
  {
    s16 idx = *((s16 *) (self + 0x22));
    *((u8 *) ((self + (((u32) idx) * 2)) + 0x19)) = 0;
  }
  scriptTable = &gMainObjTimerCallback;
  scriptState = self + 0x18;
  sub_080C31E4(scriptState, self + 0x22, (s32)*scriptTable);
  {
    s16 idx = *((s16 *) (self + 0x22));
    *((u8 *) ((self + (((u32) idx) * 2)) + 0x19)) += 1;
    idx = *((s16 *) (self + 0x22));
    stepCmd = scriptState + (((u32) idx) * 2);
    sub_080C31E0(self, *(void **)(*(u8 **)handlerTable + *stepCmd * 4));
  }
}
