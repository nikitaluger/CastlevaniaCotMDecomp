s32 checkActorViewBounds(s32, void *);
s32 updateObjectDisplayState(s32, void *);
void syncSpriteToWorldPosition(void *, s32);
void sub_080C31E0(void *, s32);

/* Script tick for a MainObj: let the per-frame state checks decide whether to
 * bail out, pick the normal or alternate command table, dispatch one handler
 * for the current script slot, then refresh the target entity's coordinates. */
void sub_08035048(void *arg0)
{
  void *obj = arg0;
  void *sprite = *((void **) (((u8 *) obj) + 0x38));
  void *state = *((void **) (((u8 *) obj) + 0x3C));
  u8 *modeFlag = ((u8 *) obj) + 0x7C;
  void * volatile *dst;
  u16 pcTmp;
  u8 *entry;
  s32 *stateY;
  s32 idx;
  u8 *cmdBase;
  u8 opcode;
  void **cmdTable;
  void *handler;
  if ((*modeFlag) == 0)
  {
    if (checkActorViewBounds((s32) sprite, state) == 1)
    {
      sub_080C31E0(obj, *((void **) (((u8 *) obj) + 0x24)));
      return;
    }
    stateY = (s32 *) (((u8 *) state) + 0x0C);
    if ((*modeFlag) == 0)
    {
      dst = (void * volatile *)((u8 *) obj + 0x30);
      *((s32 *) (((u8 *) *dst) + 0x4C)) = *((s32 *) (((u8 *) state) + 0x08));
      *((s32 *) (((u8 *) *dst) + 0x5C)) = *stateY;
      if (updateObjectDisplayState((s32) sprite, state) == 0)
      {
        *((void **) (((u8 *) obj) + 0x14)) = (void *) 0x0866DD90;
        goto dispatch;
      }
      goto refresh;
    }
    goto checkState;
  }
checkState:
  if (updateObjectDisplayState((s32) sprite, state) == 0)
  {
    *((void **) (((u8 *) obj) + 0x14)) = (void *) 0x0866DDA0;
    goto dispatch;
  }
  goto refresh;
  dispatch:
  pcTmp = *((u16 *) (((u8 *) obj) + 0x22));
  pcTmp = pcTmp + 1;
  *((u16 *) (((u8 *) obj) + 0x22)) = pcTmp;
  entry = (u8 *) ((((u32) (*((s16 *) (((u8 *) obj) + 0x22)))) * 2) + ((u32) obj));
  entry[0x19] = (u8) (entry[0x19] + 1);
  idx = (*((s16 *) (((u8 *) obj) + 0x22))) * 2;
  cmdBase = ((u8 *) obj) + 0x18;
  opcode = *(cmdBase + idx);
  cmdTable = *((void **) (((u8 *) obj) + 0x14));
  handler = cmdTable[opcode];
  sub_080C31E0(obj, (s32) handler);
  pcTmp = *((u16 *) (((u8 *) obj) + 0x22));
  pcTmp = pcTmp - 1;
  *((u16 *) (((u8 *) obj) + 0x22)) = pcTmp;
  refresh:
  syncSpriteToWorldPosition(obj, (s32) sprite);
}
