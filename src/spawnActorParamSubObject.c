#define SUBPTR ( *(u8 * volatile *)((u8 *)state + 0x2C) )
void *allocEffectPart(void *);
void sub_0806D2D0(void *);
s16 scalePercentSaturate16(u16, s32);
void sub_08003A6C(void *, s32, void *);
void setDirectionVector(void *, u8);
void sub_0808449C(void);
void sub_080C31E4(void *, void *, void *);
void sub_080C31E0(void *, void *);
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u8 D_080E4D84[];
extern u8 D_080E4DE4[];
extern u32 gScriptStepCallbackTable[];

/*
 * Spawn a sub-object using the actor's 12-byte spawn parameter entry: allocate
 * it from the pool, initialise it and its velocity, then advance the script.
 */
void spawnActorParamSubObject(void *arg0)
{
  u8 *actor = *((u8 **) (((u8 *) arg0) + 0x6C));
  u8 *state = 4 + actor;
  u8 *sprite = *((u8 **) (((u8 *) arg0) + 0x38));
  u8 *config = gGameStatus;
  u8 *params;
  u8 *newObj;
  s32 scaled;
  {
    u8 *tableOffset = (u8 *)(*(u32 *)((u8 *)arg0 + 0x9C) * 12);
    params = D_080E4D84 + (u32)tableOffset;
    newObj = (u8 *) allocEffectPart(tableOffset);
  }
  *((u8 **) (state + 0x2C)) = newObj;
  if (newObj == 0)
  {
    sub_0806D2D0(arg0);
    return;
  }
  {
    u32 z = 0;
    *((u32 *) (state + 0x30)) = z;
    *((u32 *) (state + 0x34)) = z;
    *((u32 *) (state + 0x38)) = z;
    *((u32 *) (state + 0x3C)) = z;
    newObj[1] = gMainWorkspace[0x1510] & 1;
  }
  SUBPTR[2] = 2;
  SUBPTR[3] = 8;
  *((u16 *) (SUBPTR + 4)) = config[0x304];
  *((u16 *) (SUBPTR + 6)) = *((u16 *)(params + 6));
  *((u16 *) (SUBPTR + 8)) = *((u16 *)(params + 8));
  *((u16 *) (SUBPTR + 0x0A)) = 0;
  *((u16 *) (SUBPTR + 0x0C)) = 0;
  *((u16 *) (SUBPTR + 0x0E)) = scalePercentSaturate16(*((u16 *) (config + 0x2E2)), 0x16);
  *((u16 *) (SUBPTR + 0x16)) = 5;
  *((u16 *) (SUBPTR + 0x18)) = 0x5A;
  *((u32 *) (SUBPTR + 0x10)) = (u32) sprite;
  *((u32 *) (state + 0x18)) = *((u32 *) (((u8 *) arg0) + 0x24));
  *((u32 *) (((u8 *) arg0) + 0x24)) = (u32) sub_0808449C;
  *((u32 *) (sprite + 0x24)) = (u32) 0x084DCFBC;
  sub_08003A6C(actor + 0x20, 0, (void *)*((u32 *)(params + 0)));
  *((u32 *) (actor + 4)) = *((u32 *) (((u8 *) arg0) + 0x7C));
  *((u32 *) (state + 4)) = *((u32 *) (((u8 *) arg0) + 0x8C));
  *((u32 *) (state + 0x40)) = 0x8000;
  {
    u8 direction = *(u8 *)(params + 4) + D_080E4DE4[*(u32 *)(gMainWorkspace + 0x14F8) & 7];
    *(u8 *)(actor + 0x48) = direction;
    setDirectionVector(state, *(u8 *)(actor + 0x48));
  }
  {
    s32 scale = (s32)*((u32 *)(state + 0x40)) >> 8;
    scaled = (s32)*((u32 *)(state + 8)) * scale;
    if (scaled < 0) scaled += 0xFF;
    *((u32 *)(state + 8)) = scaled >> 8;
    scaled = (s32)*((u32 *)(state + 0x0C)) * scale;
    if (scaled < 0) scaled += 0xFF;
    *((u32 *)(state + 0x0C)) = scaled >> 8;
  }
  *((u32 *)(state + 0x48)) = 0x80;
  {
    s16 scriptIdx;
    u8 *actorPtr = (u8 *) arg0;
    u8 *scriptPtr;
    u32 *scriptTableArg;
    scriptIdx = *((s16 *) (actorPtr + 0x22));
    *((u8 *) ((actorPtr + (scriptIdx * 2)) + 0x19)) = 0;
    scriptTableArg = gScriptStepCallbackTable;
    scriptPtr = actorPtr + 0x18;
    sub_080C31E4(scriptPtr, actorPtr + 0x22, (void *) (*scriptTableArg));
    scriptIdx = *((s16 *) (actorPtr + 0x22));
    *((u8 *) ((actorPtr + (scriptIdx * 2)) + 0x19)) += 1;
    scriptIdx = *((s16 *) (actorPtr + 0x22));
    scriptPtr += scriptIdx * 2;
    {
      u8 scriptByte = *scriptPtr;
      void **scriptTable = *((void ***) (actorPtr + 0x14));
      sub_080C31E0(arg0, scriptTable[scriptByte]);
    }
  }
}
