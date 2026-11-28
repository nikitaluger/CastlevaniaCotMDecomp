extern s32 applyAreaSpecialBehavior(void *, void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080168C4(void);
extern void *sub_080168F8(void);
extern void *spawnEntity(void *, s32, s32, s32);
extern void spawnScaledEffect(s32, s32);
extern s32 D_080E5EA4[8][2];
extern s32 D_02027710[8][2];
extern s32 gMainWorkspace[];

/*
 * Update for a moving attack. Advances its position from a coordinate table,
 * and while its trigger flag is set walks the global object list to spawn
 * tracked projectiles at matching targets. Finally checks world state to
 * decide whether to run the entity's callback.
 */
void sub_08083820(void *self)
{
  u8 *node;
  u8 *eventPtr;
  void *attack = ((u8 *) (*((u32 *) (((u8 *) self) + 0x6C)))) + 4;
  void *obj = *((void **) (((u8 *) self) + 0x38));
  s32 step;
  void *targetTable;
  void *spawned;
  void *owner;
  void *world;
  if (applyAreaSpecialBehavior(self, obj, attack) > 0)
  {
    sub_080C31E0(self, *((s32 *) (((u8 *) self) + 0x24)));
    return;
  }
  *((s32 *) (((u8 *) attack) + 0x10)) = (step = (*((s32 *) (((u8 *) attack) + 0x10))) + 1);
  *((s32 *) (((u8 *) obj) + 0x14)) = D_080E5EA4[(step >> 3) & 7][0];
  *((s32 *) (((u8 *) obj) + 0x18)) = D_080E5EA4[((*((s32 *) (((u8 *) attack) + 0x10))) >> 3) & 7][1];
  if (1 & (*((u16 *) (((u8 *) (*((void **) (((u8 *) attack) + 0x2C)))) + 0x14))))
  {
    sub_080168C4();
    targetTable = (void *) 0x02027710;
    while ((obj = sub_080168F8()) != 0)
    {
      node = (u8 *) obj;
      if ((*((void **) (node + 8))) != (*((void **) (((u8 *) attack) + 0x2C))))
      {
        continue;
      }
      spawnScaledEffect(*((s32 *) targetTable), 1);
      owner = *((void **) (node + 4));
      ;
      if (!(2 & (*((u16 *) (*((void **) (((u8 *) owner) + 0x3C)))))))
      {
        continue;
      }
      spawned = spawnEntity(*((void **) (((u8 *) (*((void **) (((u8 *) self) + 0x28)))) + 0x28)), 0x78, 0x0A, 0x12);
      if (!spawned)
      {
        continue;
      }
      *((void **) (((u8 *) spawned) + 0x7C)) = obj;
      *((u32 *) (((u8 *) spawned) + 0x8C)) = *((u8 *) (node + 1));
    }

  }
  *((u16 *) (((u8 *) (*((void **) (((u8 *) attack) + 0x2C)))) + 0x14)) = 0;
  ;
  world = (u8 *) gMainWorkspace;
  if (((*(eventPtr = ((u8 *) gMainWorkspace) + 0x173A)) == 0x1C) || (((*((u8 *) (world + 0x14ED))) == 0) && ((*((s32 *) (((u8 *) gMainWorkspace) + 0x10))) != 0)))
  {
    sub_080C31E0(self, *((s32 *) (((u8 *) self) + 0x24)));
  }
}
