struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState gMainWorkspace;
struct SubObject { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; };
struct HostObject { u8 _0[8]; u32 f8; u32 fC; u8 _10[0xC]; u16 f1C; u8 _1E[4]; u16 f22; u8 _24[4]; struct SubObject *f28; u8 _2C[0x1C]; u32 f48; };
struct SpawnParams { u8 _0[4]; u16 f4; u16 f6; u8 _8[0x20]; };
extern struct SpawnParams gEffectGfxTable[];
extern u16 D_08101CC4[];
extern void *gMainObjTimerCallbacks;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void updateActorEffectSubObject(void);
inline int addOffset(s32 ptr, int off) { return ptr + off; }

/*
 * Build the graphics/sub-object pair for an actor, set up its animation and
 * palette, copy the spawn defaults in, then advance the actor's script index.
 */
/* Build the kind-0x59 actor's sprite and effect sub-object, set its animation and palette from shared defaults, install the per-frame update handler, then advance the script. */ void spawnKind59ScriptEffect(u8 *actor) {
  s32 sprite; struct HostObject *work; u8 *animState; u16 *layerAttrs; u32 kindIndex; u8 *scriptPtr; void **timerCallbacks; u8 *scriptStep; u32 zero;
  struct SubObject *subObj;
  sprite = (s32)allocSpriteObject();
  if (sprite == 0) goto fail;
  *(u32 *)(actor + 0x38) = sprite;
  allocWorkSlot(actor, 0, 0x48, 0);
  if (*(u32 *)(actor + 0x3C) == 0) goto fail;
  *(u32 *)addOffset(sprite, 0x1C) = 0x80000009;
  work = (struct HostObject *)*(u8 **)(actor + 0x3C);
  animState = (u8 *)work + 0x34;
  installUpdateHandler(actor, (u8 *)work, updateActorEffectSubObject);
  zero = 0;
  work->f1C = 0x59;
  work->f8 = *(u32 *)(actor + 0x4C);
  work->fC = *(u32 *)(actor + 0x5C);
  kindIndex = findKindIndex(0x59);
  work->f22 = kindIndex;
  if ((s16)kindIndex < 0) goto fail;
  kindIndex = *(s16 *)((u8 *)work + 0x22);
  kindIndex = kindIndex << 6;
  kindIndex = kindIndex + 0x200;
  kindIndex &= 0xFC0;
  *(u16 *)sprite = kindIndex;
  *(u16 *)sprite = gMainWorkspace.gfxFlags | *(u16 *)sprite;
  initSpriteGraphics((void *)sprite, animState, addOffset((*(s16 *)((u8 *)work + 0x1C)) * 0xC, 0x080CD400));
  setAnimationFrame((void *)sprite, animState, 0xA, 0);
  *(u16 *)addOffset(sprite, 2) |= 0x400;
  *(u32 *)(actor + 0x8C) = 0x1E0;
  layerAttrs = D_08101CC4;
  subObj = allocEffectPart();
  work->f28 = subObj;
  if (subObj != NULL) goto cont;
fail:
  sub_080C31E0(actor, *(void **)(actor + 0x24));
  return;
cont:
  subObj->f1 = zero;
  work->f28->f2 = 8;
  work->f28->f3 = 1;
  work->f28->f4 = gEffectGfxTable[*(s16 *)((u8 *)work + 0x1C)].f4;
  work->f28->f6 = layerAttrs[0];
  work->f28->f8 = layerAttrs[1];
  work->f28->fA = layerAttrs[2];
  work->f28->fC = layerAttrs[3];
  work->f28->fE = gEffectGfxTable[*(s16 *)((u8 *)work + 0x1C)].f6;
  work->f28->f10 = sprite;
  *(u16 *)(actor + 2) |= 0x1000;
  *(u8 *)((u32)(*(s16 *)(actor + 0x22)) * 2 + (u32)actor + 0x19) = zero;
  timerCallbacks = &gMainObjTimerCallbacks;
  scriptPtr = actor + 0x18;
  sub_080C31E4(scriptPtr, actor + 0x22, (s32)(*timerCallbacks));
  *(u8 *)((u32)(*(s16 *)(actor + 0x22)) * 2 + (u32)actor + 0x19) += 1;
  scriptStep = scriptPtr + ((u32)(*(s16 *)(actor + 0x22)) * 2);
  sub_080C31E0(actor, *(void **)(*(u8 **)(actor + 0x14) + *(u8 *)scriptStep * 4));
}
