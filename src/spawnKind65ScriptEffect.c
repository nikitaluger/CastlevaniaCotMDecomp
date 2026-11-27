struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState gMainWorkspace;
struct SubObject { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; };
struct HostObject { u8 _0[8]; u32 f8; u32 fC; u8 _10[0xC]; u16 f1C; u8 _1E[4]; u16 f22; u8 _24[4]; struct SubObject *f28; u8 _2C[0x1C]; u32 f48; };
struct SpawnParams { u8 _0[0xC]; u16 fC; u16 fE; u8 _10[0x18]; };
extern struct SpawnParams gEffectGfxTable[];
extern u16 gKind65LayerAttrs[];
extern void *gScriptStepCallbackTable;
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
 * palette from the spawn defaults, then advance the actor's script index.
 */
/* Build the kind-0x65 scripted effect: allocate a sprite and render layer, set its heading and animation from the actor's parameters and shared defaults, install the per-frame update handler, then advance the actor's script step. */ void spawnKind65ScriptEffect(u8 *actor) {
  s32 sprite; struct HostObject *work; u8 *animTrack; u16 *layerAttrs; u32 heading; u8 *scriptStream; void **timerCallbacks; u8 *scriptStep; u32 zero;
  sprite = (s32) allocSpriteObject();
  if (sprite == 0) goto fail;
  *((u32 *) (actor + 0x38)) = sprite;
  allocWorkSlot(actor, 0, 0x48, 0);
  if ((*((u32 *) (actor + 0x3C))) == 0) goto fail;
  *((u32 *) addOffset(sprite, 0x1C)) = 0x80000009;
  work = (struct HostObject *) (*((u8 **) (actor + 0x3C)));
  animTrack = ((u8 *) work) + 0x34;
  installUpdateHandler(actor, (u8 *) work, updateActorEffectSubObject);
  zero = 0;
  work->f1C = 0x65;
  work->f8 = *((u32 *) (actor + 0x4C));
  work->fC = *((u32 *) (actor + 0x5C));
  heading = findKindIndex(0x65);
  work->f22 = heading;
  if ((s16)heading < 0) goto fail;
  heading = *((s16 *) (((u8 *) work) + 0x22));
  heading = heading << 6;
  heading = heading + 0x200;
  heading &= 0xFC0;
  *((u16 *) sprite) = heading;
  *((u16 *) sprite) |= gMainWorkspace.gfxFlags;
  initSpriteGraphics((void *) sprite, animTrack, addOffset((*((s16 *) (((u8 *) work) + 0x1C))) * 0xC, 0x080CD400));
  setAnimationFrame((void *) sprite, animTrack, 0x45, 1);
  layerAttrs = gKind65LayerAttrs;
  work->f28 = allocEffectPart();
  if (work->f28 != NULL) goto cont;
  fail:
  sub_080C31E0(actor, *((void **) (actor + 0x24)));
  return;
  cont:
  work->f28->f1 = 5;
  work->f28->f2 = 8;
  work->f28->f3 = 1;
  work->f28->f4 = gEffectGfxTable[*((s16 *) (((u8 *) work) + 0x1C))].fC;
  work->f28->f6 = layerAttrs[0];
  work->f28->f8 = layerAttrs[1];
  work->f28->fA = layerAttrs[2];
  work->f28->fC = layerAttrs[3];
  work->f28->fE = gEffectGfxTable[*((s16 *) (((u8 *) work) + 0x1C))].fE;
  work->f28->f10 = sprite;
  *((u16 *) addOffset(sprite, 2)) |= 0x400;
  *((u8 *) (actor + 0x8C)) = zero;
  *((u16 *) (actor + 2)) |= 0x1000;
  *((u8 *) addOffset(addOffset(((u32) (*((s16 *) (actor + 0x22)))) * 2, (u32) actor), 0x19)) = zero;
  timerCallbacks = &gScriptStepCallbackTable;
  scriptStream = actor; scriptStream += 0x18;
  sub_080C31E4(scriptStream, actor + 0x22, (s32) (*timerCallbacks));
  *((u8 *) addOffset(addOffset(((u32) (*((s16 *) (actor + 0x22)))) * 2, (u32) actor), 0x19)) += 1;
  scriptStep = scriptStream + (((u32) (*((s16 *) (actor + 0x22)))) * 2);
  sub_080C31E0(actor, *((void **) ((*((u8 **) (actor + 0x14))) + ((*((u8 *) scriptStep)) * 4))));
}
