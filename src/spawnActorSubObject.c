#define SUBPTR ( *(u8 * volatile *)((u8 *)state + 0x2C) )
void *allocEffectPart(void *);
void cleanupFailedEffectSpawn(void *);
u16 scalePercentSaturate16(u16, s32);
void startEffectTimer(void *, s32, void *);
void releaseActorEffectParts(void);
void sub_080C31E4(void *, void *, void *);
void sub_080C31E0(void *, void *);
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern s32 *D_080E4CE8[];
extern s32 *D_080E4D2C[];
extern u32 gMainObjTimerCallbacks[];

/*
 * Spawn a sub-object for an actor: allocate it from the object pool, initialise
 * its fields from global game data, swap in its update callback, then advance
 * the actor's script table index.
 */
/* Spawn an effect sub-object for an actor from its current script step: allocate a render part, copy palette/animation settings, install the release handler, start a timer, pick cyclic spawn parameters, then advance the script and dispatch the next command. */ void spawnActorSubObject(void *owner)
{
  u8 *actor = *((u8 **) (((u8 *) owner) + 0x6C));
  u8 *state = 4 + actor;
  u8 *sprite = *((u8 **) (((u8 *) owner) + 0x38));
  u8 *gameConfig = gGameStatus;
  u8 *newPart;
  newPart = (u8 *) allocEffectPart(actor);
  *((u8 **) (state + 0x2C)) = newPart;
  if (newPart == 0)
  {
    cleanupFailedEffectSpawn(owner);
    return;
  }
  *((u32 *) (state + 0x30)) = 0;
  *((u32 *) (state + 0x34)) = 0;
  *((u32 *) (state + 0x38)) = 0;
  *((u32 *) (state + 0x3C)) = 0;
  newPart[1] = gMainWorkspace[0x1510] & 1;
  SUBPTR[2] = 2;
  SUBPTR[3] = 8;
  *((u16 *) (SUBPTR + 4)) = gameConfig[0x304];
  *((u16 *) (SUBPTR + 6)) = 1;
  *((u16 *) (SUBPTR + 8)) = 1;
  *((u16 *) (SUBPTR + 0x0A)) = 0;
  *((u16 *) (SUBPTR + 0x0C)) = 0;
  *((u16 *) (SUBPTR + 0x0E)) = scalePercentSaturate16(*((u16 *) (gameConfig + 0x2E2)), 0x0E);
  *((u16 *) (SUBPTR + 0x16)) = 5;
  *((u16 *) (SUBPTR + 0x18)) = 0x32;
  *((u32 *) (SUBPTR + 0x10)) = (u32) sprite;
  *((u32 *) (state + 0x18)) = *((u32 *) (((u8 *) owner) + 0x24));
  *((u32 *) (((u8 *) owner) + 0x24)) = (u32) releaseActorEffectParts;
  {
    u32 renderSize = 0x400;
    *((u16 *) (sprite + 4)) = renderSize;
    *((u16 *) (sprite + 6)) = renderSize;
  }
  *((u16 *) (sprite + 8)) = 0;
  *((u32 *) (sprite + 0x24)) = (u32) 0x0849CF38;
  startEffectTimer(actor + 0x20, 0, (void *)0x0849CFA8);
  *((s32 *)(state + 0x54)) = (s32) D_080E4CE8[*((u32 *)(gMainWorkspace + 0x14F4))];
  if (*((s32 *)(state + 0x54)) < 0) {
    *((u32 *)(gMainWorkspace + 0x14F4)) = 0;
    *((s32 *)(state + 0x54)) = (s32) D_080E4CE8[0];
  }
  *((u32 *)(gMainWorkspace + 0x14F4)) = *((u32 *)(gMainWorkspace + 0x14F4)) + 1;
  *((s32 *)(state + 0x58)) = (s32) D_080E4D2C[*((u32 *)(gMainWorkspace + 0x14F8))];
  if (*((s32 *)(state + 0x58)) < 0) {
    *((u32 *)(gMainWorkspace + 0x14F8)) = 0;
    *((s32 *)(state + 0x58)) = (s32) D_080E4D2C[0];
  }
  *((u32 *)(gMainWorkspace + 0x14F8)) = *((u32 *)(gMainWorkspace + 0x14F8)) + 1;
  *((u32 *)(actor + 4)) = *((u32 *)(gMainWorkspace + 0x174C));
  *((u32 *)(state + 4)) = *((u32 *)(gMainWorkspace + 0x1750));
  {
    s16 scriptIdx;
    u8 *actorPtr = (u8 *) owner;
    u8 *scriptPtr;
    u32 *timerCallbacks;
    scriptIdx = *((s16 *) (actorPtr + 0x22));
    *((u8 *) ((actorPtr + (scriptIdx * 2)) + 0x19)) = 0;
    timerCallbacks = gMainObjTimerCallbacks;
    scriptPtr = actorPtr + 0x18;
    sub_080C31E4(scriptPtr, actorPtr + 0x22, (void *) (*timerCallbacks));
    scriptIdx = *((s16 *) (actorPtr + 0x22));
    *((u8 *) ((actorPtr + (scriptIdx * 2)) + 0x19)) += 1;
    scriptIdx = *((s16 *) (actorPtr + 0x22));
    scriptPtr += scriptIdx * 2;
    {
      u8 opcode = *scriptPtr;
      void **commandTable = *((void ***) (actorPtr + 0x14));
      sub_080C31E0(owner, commandTable[opcode]);
    }
  }
}
