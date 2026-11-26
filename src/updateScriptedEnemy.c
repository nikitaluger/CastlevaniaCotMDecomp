struct GameState
{
  u8 unk0[0x24];
  s32 mode;
  u8 unk28[2];
  u16 flags;
  u8 unk2C[0x14ED - 0x2C];
  u8 stage;
  u8 unk14EE[0x1514 - 0x14EE];
  s32 counter;
  u8 unk1518[0x1754 - 0x1518];
  s32 level;
};
extern struct GameState gMainWorkspace;
struct ScrollState
{
  u8 unk0[0x146E];
  u16 flags;
};
extern struct ScrollState gCameraState;
extern u8 gGameStatus[];
extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806BA20(void *, void *, void *);
extern void sub_0806B104(void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_08005E80(s32);
extern void sub_0806E114(void *, s32, s32, s32);
extern void sub_0806A884(void *, void *);
extern s32 sub_08003740(void *, void *);
extern void sub_0806A7AC(void *, void *, s32);
extern void sub_08086648(void *, void *, s32);
extern void sub_08086D58(void *, s32);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_08086744(void *, void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
/* Update a scripted enemy: advance its behaviour and animation timers, handle
 * the death/attack transition and dispatch the resulting script action. */
void updateScriptedEnemy(u8 *arg0)
{
  u8 *work = *((u8 **) (arg0 + 0x6C)) + 4;
  u8 *target = *((u8 **) (arg0 + 0x38));
  u8 *workState = work;
  u8 *gameFlags = (u8 *) 0x02025368;
  u8 *paramTable;
  int scriptOpsAddr;
  s32 entryOffset;
  s32 maxValue;
  u16 condition;
  s32 tableIndex;
  int resultOffset;
  s32 zero;
  u8 *animPtr;
  u32 result;
  u32 zero70 = 0;
  if (sub_0806C4B4(work, work) != 0)
  {
    return;
  }
  sub_0806C5EC(arg0, target, workState, workState);
  sub_0806BA20(target, workState, workState);
  paramTable = (u8 *) 0x080E03A0;
  tableIndex = *((s32 *) (workState + 0x44));
  entryOffset = tableIndex * 0x58;
  *((s32 *) (workState + 0x0C)) = (*((s32 *) (workState + 0x0C))) + (*((s32 *) (entryOffset + paramTable)));
  paramTable += 4;
  maxValue = *((s32 *) (entryOffset + paramTable));
  resultOffset = 0xC4;
  if ((*((s32 *) (workState + 0x0C))) > maxValue)
  {
    *((s32 *) (workState + 0x0C)) = maxValue;
  }
  condition = (gMainWorkspace.mode != 0) ? (gMainWorkspace.flags & (*((u16 *) (gameFlags + 0x3BC)))) : (gCameraState.flags & (*((u16 *) (gameFlags + 0x3BC))));
  if (condition == 0)
  {
    *((s32 *) (work + 0x70)) = zero70;
  }
  sub_08086744(arg0, work, workState, 0xC);
  sub_0806B104(target, work, workState);
  sub_0806AB04(arg0, target, work, workState);
  if ((*((s32 *) (work + 0x40))) == 1)
  {
    sub_08005E80(0x67);
    *((s32 *) (work + 0x4C)) = 0;
    *((s32 *) (work + 0x50)) = 0;
    *((s32 *) (work + 0x54)) = 0;
    if (gMainWorkspace.stage == 0x35)
    {
      if (gMainWorkspace.level <= 8)
      {
        gMainWorkspace.level = 9;
      }
    }
    zero = 0;
    *((s32 *) (workState + 0x08)) = zero;
    sub_0806E114(arg0, 9, *((s32 *) (workState + 0x00)), *((s32 *) (workState + 0x04)));
    (arg0 + ((*((s16 *) (arg0 + 0x22))) * 2))[0x19] = (u8) zero;
    {
      s32 *scriptOps = (s32 *) 0x08671BD0;
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0xA, *scriptOps);
    }
  }
  sub_0806A884(target, workState);
  gameFlags = work;
  gameFlags += 0x28;
  {
    u8 *animScratch = gameFlags;
    s32 moveResult = sub_08003740(animScratch, target);
    animPtr = animScratch;
    if ((moveResult == 0) || (gMainWorkspace.counter != 0))
    {
      sub_0806A7AC(target, work, 0x10);
      sub_08003740(animPtr, target);
      (arg0 + ((*((s16 *) (0x22 + arg0))) * 2))[0x19] = 0;
      {
        s32 *scriptOps = (s32 *) 0x08671BD0;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 3, *scriptOps);
      }
    }
  }
  sub_08086648(target, work, 0xB);
  sub_08086D58(work, 0xC);
  result = sub_0806BCD8(arg0, target, work, workState);
  gameFlags = work;
  gameFlags += (unsigned long long) resultOffset;
  *((s32 *) gameFlags) = (u16) result;
  if (((u16) result) != 0)
  {
    sub_08003740(animPtr, target);
    (arg0 + ((*((s16 *) (arg0 + 0x22))) * 2))[0x19] = 0;
    scriptOpsAddr = 0x08671BD0;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, *((s32 *) gameFlags), *((s32 *) scriptOpsAddr));
  }
  sub_0806C6B0(arg0, target, work, workState);
}
