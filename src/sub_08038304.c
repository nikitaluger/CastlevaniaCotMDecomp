void sub_0803B0D0(void *);
void sub_0803B0D8(void *, void *, s32);
void setObjectAnimationFrame(void *, void *, s32, s32);
void setSpriteFlipForDirection(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Scripted entity setup/update: reset and configure the enemy's state block,
 * seed its data pointer, run the actor's display step, then dispatch one script
 * command from the table installed at self+0x14. */
void sub_08038304(void *arg0)
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
  sub_0803B0D0(enemyState);
  zeroCounter = 0;
  *((u8 *) (((u8 *) enemyState) + 0x10)) = zeroCounter;
  *((u8 *) (((u8 *) enemyState) + 0x11)) = zeroCounter;
  sub_0803B0D8(enemy, enemyState, 0x3000);
  *((void **) (((u8 *) enemy) + 0x10)) = *((void **) (((u8 *) enemy) + 0x48));
  setObjectAnimationFrame(actor, enemyData, 0, 1);
  setSpriteFlipForDirection(actor, *((void **) (((u8 *) enemy) + 0x10)));
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = zeroCounter;
  pScriptParam = (u32 *) 0x08671BB0;
  pCmdArray = self + 0x18;
  pScriptIndex = self + 0x22;
  sub_080C31E4(pCmdArray, pScriptIndex, *pScriptParam);
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) += 1;
  do { pCmdArray += (*((s16 *) (self + 0x22))) * 2; sub_080C31E0(self, *((void **) (((*((u8 *) pCmdArray)) * 4) + (*((u32 *) (self + 0x14)))))); } while (0);
}
