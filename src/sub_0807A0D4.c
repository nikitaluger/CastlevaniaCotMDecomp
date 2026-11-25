#define SUBPTR ( *(u8 * volatile *)((u8 *)state + 0x2C) )
void *sub_08016190(void *);
void sub_0806D2D0(void *);
u16 sub_0806D62C(u16, s32);
void sub_08003A6C(void *, s32, void *);
void sub_0808449C(void);
void sub_080C31E4(void *, void *, void *);
void sub_080C31E0(void *, void *);
extern u8 D_02025368[];
extern u8 D_02025FF0[];
extern u32 D_0202771C;
extern u8 D_084DFB30[];
extern u8 D_084DFBC0[];
extern u32 D_08671BB0[];
inline u8 inline_fn()
{
  return D_02025FF0[0x14EF];
}

/*
 * Spawn a sub-object (a small effect) for an actor: allocate it from the
 * object pool, initialise its sprite and animation script from global game
 * data, swap in its release callback, then advance the actor's script table
 * index and run the new script command.
 */
void sub_0807A0D4(void *arg0)
{
  u8 *actor = *((u8 **) (((u8 *) arg0) + 0x6C));
  u8 *state = 4 + actor;
  u8 *sprite = *((u8 **) (((u8 *) arg0) + 0x38));
  u8 *config = D_02025368;
  u8 *newObj;
  newObj = (u8 *) sub_08016190(actor);
  *((u8 **) (state + 0x2C)) = newObj;
  if (newObj == 0)
  {
    sub_0806D2D0(arg0);
    return;
  }
  *((u32 *) (state + 0x30)) = 0;
  *((u32 *) (state + 0x34)) = 0;
  *((u32 *) (state + 0x38)) = 0;
  *((u32 *) (state + 0x3C)) = 0;
  newObj[1] = D_02025FF0[0x1510] & 1;
  SUBPTR[2] = 2;
  SUBPTR[3] = 8;
  *((u16 *) (SUBPTR + 4)) = config[0x304];
  *((u16 *) (SUBPTR + 6)) = 0x0A;
  *((u16 *) (SUBPTR + 8)) = 0x0A;
  *((u16 *) (SUBPTR + 0x0A)) = 0;
  *((u16 *) (SUBPTR + 0x0C)) = 0;
  *((u16 *) (SUBPTR + 0x0E)) = sub_0806D62C(*((u16 *) (config + 0x2E2)), 0x64);
  *((u16 *) (SUBPTR + 0x16)) = 5;
  *((u16 *) (SUBPTR + 0x18)) = 0x5C;
  *((u32 *) (SUBPTR + 0x10)) = (u32) sprite;
  *((u32 *) (state + 0x18)) = *((u32 *) (((u8 *) arg0) + 0x24));
  *((u32 *) (((u8 *) arg0) + 0x24)) = (u32) sub_0808449C;
  actor[0x55] = inline_fn();
  {
    u32 size = 0x100;
    *((u16 *) (sprite + 4)) = size;
    *((u16 *) (sprite + 6)) = size;
  }
  *((u16 *) (sprite + 8)) = 0;
  *((u32 *) (sprite + 0x24)) = (u32) D_084DFB30;
  sub_08003A6C(actor + 0x20, 0, D_084DFBC0);
  {
    u8 *gGame = D_02025FF0;
    *((u32 *) (actor + 4)) = *((u32 *) (gGame + 0x1728));
    *((u32 *) (state + 4)) = *((u32 *) (gGame + 0x172C)) + 0xFFEC0000;
  }
  {
    u32 val;
    if ((*((u16 *) (sprite + 2))) & 0x10)
    {
      val = 0xFFFC0000;
    }
    else
    {
      val = 0x00040000;
    }
    *((u32 *) (state + 8)) = val;
  }
  *((u32 *) (state + 0x0C)) = 0xFFFC0000;
  *((u32 *) (state + 0x14)) = 1;
  {
    s16 scriptIdx;
    u8 *actorPtr = (u8 *) arg0;
    u8 *scriptPtr;
    u32 *scriptTableArg;
    scriptIdx = *((s16 *) (actorPtr + 0x22));
    *((u8 *) ((actorPtr + (scriptIdx * 2)) + 0x19)) = 0;
    scriptTableArg = D_08671BB0;
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
