/* Per-frame update of a moving actor: sync the view and shared result flags,
 * advance its timer from the per-type table, run the action and hit handlers,
 * handle the death transition, then dispatch the next script step. */
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806BA20(void *, void *, void *);
extern void sub_0806B104(void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void playSound(u16);
extern void spawnKind2CEntity(void *, s32, s32, s32);
extern void sub_0806A884(void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern void setEntityForm(void *, void *, s32);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);

struct MovActorGlobals
{
  u8 _0[0x14ED];
  u8 gameMode;                 /* 0x14ED */
  u8 _1[0x1754 - 0x14EE];
  s32 level;                   /* 0x1754 */
};
extern struct MovActorGlobals gMainWorkspace;

struct MovActorWork
{
  u8 _0[8];
  s32 worldX;                  /* 0x08 */
  s32 timer;                   /* 0x0C: advanced from the per-type table */
  u8 _10[0x40 - 0x10];
  s32 action;                  /* 0x40: 1 = death transition */
  s32 tableIndex;              /* 0x44: row index into the per-type table */
  u8 _48[4];
  s32 flag4C;
  s32 flag50;
  s32 flag54;
};

void updateMovingActor(u8 *actor)
{
  u8 *stepTimer;
  u8 *work;
  u8 *workState;
  u8 *spriteBase;
  s32 paramTable;
  s32 entryOffset;
  u8 *sprite;
  work = *((u8 **) (actor + 0x6C)) + 4;
  spriteBase = *((u8 **) (actor + 0x38));
  sprite = spriteBase;
  workState = work;
  if (syncViewPosition(workState, workState) != 0)
  {
    return;
  }
  resetActionResultState(actor, sprite, workState, workState);
  sub_0806BA20(sprite, workState, workState);
  paramTable = ENEMY_PARAM_TABLE;
  entryOffset = ((struct MovActorWork *) workState)->tableIndex * ENEMY_PARAM_ENTRY_SIZE;
  ((struct MovActorWork *) workState)->timer = ((struct MovActorWork *) workState)->timer + (*((s32 *) (paramTable + entryOffset)));
  paramTable += 4;
  {
    s32 timerMax = *((s32 *) (paramTable + entryOffset));
    if (((struct MovActorWork *) workState)->timer > timerMax)
    {
      ((struct MovActorWork *) workState)->timer = timerMax;
    }
  }
  sub_0806B104(sprite, workState, workState);
  sub_0806AB04(actor, sprite, workState, workState);
  if (((struct MovActorWork *) workState)->action == 1)
  {
    u8 *stepEntry;
    s32 *scriptOps;
    playSound(0x67);
    ((struct MovActorWork *) workState)->flag4C = 0;
    ((struct MovActorWork *) workState)->flag50 = 0;
    ((struct MovActorWork *) workState)->flag54 = 0;
    if (gMainWorkspace.gameMode == 0x35)
    {
      if (gMainWorkspace.level <= 8)
      {
        gMainWorkspace.level = 9;
      }
    }
    ((struct MovActorWork *) workState)->worldX = 0;
    spawnKind2CEntity(actor, 9, *((s32 *) (workState + 0)), *((s32 *) (workState + 4)));
    stepEntry = (u8 *) ((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor));
    *((u8 *) (stepEntry + 0x19)) = 0;
    scriptOps = (s32 *) SCRIPT_STEP_CALLBACK_TABLE;
    sub_080C31E8(actor + 0x18, actor + 0x22, BOSS_FORM_FALLBACK, *scriptOps);
  }
  sub_0806A884(sprite, workState);
  stepTimer = work + 0x28;
  if (stepDelayTimer(stepTimer, sprite) == 0)
  {
    u8 *stepEntry;
    s32 *scriptOps;
    setEntityForm(sprite, work, BOSS_FORM_FALLBACK);
    stepDelayTimer(stepTimer, sprite);
    stepEntry = (u8 *) ((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor));
    *((u8 *) (stepEntry + 0x19)) = 0;
    scriptOps = (s32 *) SCRIPT_STEP_CALLBACK_TABLE;
    sub_080C31E8(actor + 0x18, actor + 0x22, ENEMY_STEP_FALLBACK, *scriptOps);
  }
  *((s32 *) (work + 0xC4)) = (u16) sub_0806BCD8(actor, sprite, work, workState);
  if ((*((s32 *) (work + 0xC4))) != 0)
  {
    u8 *stepEntry;
    s32 *scriptOps;
    stepDelayTimer(stepTimer, sprite);
    stepEntry = (u8 *) ((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor));
    *((u8 *) (stepEntry + 0x19)) = 0;
    scriptOps = (s32 *) SCRIPT_STEP_CALLBACK_TABLE;
    sub_080C31E8(actor + 0x18, actor + 0x22, *((s32 *) (work + 0xC4)), *scriptOps);
  }
  sub_0806C6B0(actor, sprite, work, workState);
}
