void sub_0803B0D0(void *);
void sub_0803B0D8(void *, void *, s32);
s32 sub_08005820(s32);
void sub_08011344(void *, void *, s32, s32);
void sub_08014668(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

extern u32 D_08671BB0[];

/*
 * Scripted entity setup/update: reset and configure the enemy's state block,
 * seed its timer and data pointer, run the actor's display step, then dispatch
 * one script command from the table installed at self+0x14.
 */
void sub_0803A134(void *arg0)
{
  u8 *self = (u8 *) arg0;
  void *actor = *((void **) (self + 0x38));
  void *enemy = *((void **) (self + 0x3C));
  void *enemyData = ((u8 *) enemy) + 0x34;
  void *enemyState = ((u8 *) enemy) + 0x48;
  u8 zeroCounter;
  u32 *pScriptParam;
  u8 *pCmdArray;
  u8 *pScriptIndex;
  s32 timerValue;
  sub_0803B0D0(enemyState);
  timerValue = sub_08005820(3) + 2;
  zeroCounter = 0;
  *((u8 *) (((u8 *) enemyState) + 0x0D)) = (u8)timerValue;
  sub_0803B0D8(enemy, enemyState, 0x4000);
  *((void **) (((u8 *) enemy) + 0x10)) = *((void **) (((u8 *) enemy) + 0x48));
  sub_08011344(actor, enemyData, 0, 1);
  sub_08014668(actor, *((void **) (((u8 *) enemy) + 0x10)));
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = zeroCounter;
  pScriptParam = (u32 *) 0x08671BB0;
  pCmdArray = self + 0x18;
  pScriptIndex = self + 0x22;
  sub_080C31E4(pCmdArray, pScriptIndex, *pScriptParam);
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) += 1;
  do { pCmdArray += (*((s16 *) (self + 0x22))) * 2; sub_080C31E0(self, *((void **) (((*((u8 *) pCmdArray)) * 4) + (*((u32 *) (self + 0x14)))))); } while (0);
}
