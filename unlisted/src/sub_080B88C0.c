struct GameState { u8 _0[0x18C2]; u16 field18C2; };
extern struct GameState gMainWorkspace;
struct SpawnParams { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u32 f10; };
struct EffectBody { u8 _0[8]; u32 f8, fC; u8 _10[0xC]; s16 f1C; u8 _1E[4]; s16 f22; u8 _24[4]; struct SpawnParams *f28; };
struct SpawnTableEntry { u8 _0[0x04]; u16 f4; u16 f6; u8 _8[0x1E]; };
extern struct SpawnTableEntry gEffectGfxTable[];
extern u16 gScriptEffectAnimDefaults[];
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallback;
extern u32 gScriptEffectParams[];
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_08014668(void *, s32);
extern void sub_080B98B8(void *, s32, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);

/* Spawns a scripted effect: allocates an actor and its 0x48-byte behavior body,
 * initializes body and spawn parameters from script arguments and shared tables,
 * installs animation/callback data, then advances the script to its next command. */
void spawnKind67ScriptEffect(u8 *script) {
  s32 actor;
  struct EffectBody *body;
  u8 *data34;
  u32 entryIndex;
  u8 *scriptPc;
  void **cmdTable;
  u8 *scriptState;
  u16 *initParams;

  actor = (s32)allocSpriteObject();
  if (actor == 0) goto fail;
  *(u32 *)(script + 0x38) = actor;
  allocWorkSlot(script, 0, 0x48, 0);
  if (*(u32 *)(script + 0x3C) == 0) goto fail;
  *(u32 *)(actor + 0x1C) = 2;
  body = (struct EffectBody *)*(u32 *)(script + 0x3C);
  data34 = (u8 *)body + 0x34;
  installUpdateHandler(script, body, sub_08097DC8);
  body->f1C = 0x67;
  body->f8 = *(u32 *)(script + 0x5C);
  body->fC = *(u32 *)(script + 0x6C);
  entryIndex = findKindIndex(0x67);
  body->f22 = entryIndex;
  if (((s16)entryIndex) < 0) goto fail;
  entryIndex = *(s16 *)((u8 *)body + 0x22);
  entryIndex = entryIndex << 6;
  entryIndex = entryIndex + 0x200;
  entryIndex &= 0xFC0;
  *(u16 *)actor = entryIndex;
  *(u16 *)actor |= gMainWorkspace.field18C2;
  initSpriteGraphics((void *)actor, data34, (body->f1C * 0xC) + (u32)gSpriteAnimDataTable);
  setAnimationFrame((void *)actor, data34, 0x0C, 1);
  sub_08014668((void *)actor, *(s32 *)(script + 0x7C));
  initParams = gScriptEffectAnimDefaults;
  body->f28 = allocEffectPart();
  if (body->f28 == NULL) goto fail;
  goto ok;
fail:
  sub_080C31E0(script, *(void **)(script + 0x24));
  return;
ok:
  body->f28->f1 = 5;
  body->f28->f2 = 8;
  body->f28->f3 = 1;
  body->f28->f4 = gEffectGfxTable[body->f1C].f4;
  body->f28->f6 = initParams[0];
  body->f28->f8 = initParams[1];
  body->f28->fA = initParams[2];
  body->f28->fC = initParams[3];
  body->f28->fE = gEffectGfxTable[body->f1C].f6;
  body->f28->f10 = actor;
  sub_080B98B8(script, 1, 5, *(u32 *)(actor + 0x1C));
  *(u32 *)((u8 *)body + 0x10) = *(u32 *)(script + 0x7C) << 17;
  *(u32 *)((u8 *)body + 0x14) = gScriptEffectParams[*(u32 *)(script + 0x4C)];
  *(u16 *)(script + 2) |= 0x1000;
  {
    s16 idx = *(s16 *)(script + 0x22);
    *(u8 *)(script + (u32)idx * 2 + 0x19) = 0;
  }
  cmdTable = &gMainObjTimerCallback;
  scriptPc = script + 0x18;
  sub_080C31E4(scriptPc, script + 0x22, *cmdTable);
  {
    s16 idx = *(s16 *)(script + 0x22);
    *(u8 *)(script + (u32)idx * 2 + 0x19) += 1;
    idx = *(s16 *)(script + 0x22);
    scriptState = scriptPc + (u32)idx * 2;
    sub_080C31E0(script, *(void **)(*(u8 **)(script + 0x14) + *(u8 *)scriptState * 4));
  }
}
