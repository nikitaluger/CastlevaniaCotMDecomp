extern s32 sub_08013B5C(void *actor, void *enemy);
extern void sub_080113A8(void *actor, void *data);
extern void sub_0801165C(void *enemy, s32 value);
extern s32 sub_0805F9B4(s32 a, s32 b);
extern s32 sub_080C31E0(void *self, void *cmd);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

inline int withAnimBit(u8 *animState)
{
  return animState[1] | 1;
}

/*
 * Entity AI/script update: force the enemy's animation flag, check whether
 * the enemy is already handled by sub_0805F9B4, run one display step, then
 * position the actor from the enemy's coordinates minus the camera offset.
 */
void sub_080259C0(void *self)
{
  void *actor;
  void *enemy;
  void *enemyData;
  u8 *coordTable;
  u8 *camPtr;
  u32 coordIndex;
  u8 *xTable;
  u8 *yTable;

  actor = *((void **) (((u8 *) self) + 0x38));
  enemy = *((void **) (((u8 *) self) + 0x3C));
  enemyData = ((u8 *) enemy) + 0x34;
  {
    u8 *animState = *((u8 **) (((u8 *) enemy) + 0x28));
    animState[1] = (u8) withAnimBit(animState);
  }
  if (sub_0805F9B4(*((s32 *) (((u8 *) enemy) + 0x08)), *((s32 *) (((u8 *) enemy) + 0x0C))) == 1)
  {
    sub_080C31E0(self, *((void **) (((u8 *) self) + 0x24)));
    return;
  }
  if (sub_08013B5C(actor, enemy) == 0)
  {
    sub_080113A8(actor, enemyData);
    sub_0801165C(enemy, 0);
  }
  coordTable = gCameraState;
  camPtr = gMainWorkspace;
  camPtr += 0x18A8;
  coordIndex = (((u32) (*camPtr)) + 1) * 0x40;
  xTable = coordTable + 0x1278;
  *((s32 *) (((u8 *) actor) + 0x14)) = (*((s32 *) (((u8 *) enemy) + 0x08))) - (((*((s32 *) (xTable + coordIndex))) + 0x8000) & 0xFFFF0000);
  coordIndex = (((u32) (*camPtr)) + 1) * 0x40;
  yTable = coordTable + 0x127C;
  *((s32 *) (((u8 *) actor) + 0x18)) = (*((s32 *) (((u8 *) enemy) + 0x0C))) - (((*((s32 *) (yTable + coordIndex))) + 0xFFFF8000) & 0xFFFF0000);
}
