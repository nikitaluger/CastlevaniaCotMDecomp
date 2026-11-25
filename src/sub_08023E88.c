extern void sub_080113A8(void *actor, void *data);
extern s32 sub_08013B5C(void *actor, void *enemy);
extern void sub_080C31E0(void *self, s32 cmd);
extern u8 D_02021E90[];

/* The byte at +0x18A8 selects a row of the camera/coordinate table. */
struct CameraCoord { u8 _pad[0x18A8]; u8 camRow; };
extern struct CameraCoord D_02025FF0;

/*
 * Entity script update: force the enemy's animation flag, run one display step
 * when its frame was not already handled (or this object's subtype is 2), then
 * position the actor from the enemy's coordinates minus the camera offset.
 */
void sub_08023E88(void *self)
{
  void *actor;
  void *enemy;
  void *enemyData;
  u8 *coordTable;
  u32 coordIndex;
  u8 *xTable;
  u8 *yTable;

  actor = *((void **) (((u8 *) self) + 0x38));
  enemy = *((void **) (((u8 *) self) + 0x3C));
  enemyData = ((u8 *) enemy) + 0x34;

  {
    u8 *animState = *((u8 **) (((u8 *) enemy) + 0x28));
    u8 flag = animState[1];
    u32 flags = 1;
    flags |= flag;
    animState[1] = (u8)flags;
  }

  if ((sub_08013B5C(actor, enemy) == 0) || (*((s16 *) (((u8 *) self) + 0x74)) == 2))
  {
    sub_080113A8(actor, enemyData);
    if ((*((u8 *) enemyData)) & 0x02)
    {
      sub_080C31E0(self, *((s32 *) (((u8 *) self) + 0x24)));
      return;
    }
  }

  coordTable = D_02021E90;
  coordIndex = (D_02025FF0.camRow + 1) * 0x40;
  xTable = coordTable + 0x1278;
  *((s32 *) (((u8 *) actor) + 0x14)) = (*((s32 *) (((u8 *) enemy) + 0x08))) - ((*((s32 *) (xTable + coordIndex)) + 0x8000) & 0xFFFF0000);

  coordIndex = (D_02025FF0.camRow + 1) * 0x40;
  yTable = coordTable + 0x127C;
  *((s32 *) (((u8 *) actor) + 0x18)) = (*((s32 *) (((u8 *) enemy) + 0x0C))) - ((*((s32 *) (yTable + coordIndex)) + 0xFFFF8000) & 0xFFFF0000);
}
