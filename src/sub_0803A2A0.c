void sub_080113A8(s32, void *);
void *sub_0805FB24(void *, s32);
void sub_080C31E4(void *, void *, s32);

/* Spawned-child object: state byte at 0x7C, second byte at 0x84. */
struct SpawnedChild { u8 _0[0x7C]; u8 state; u8 pad[7]; u8 unk_84; };

/* When the enemy's animation-control flags signal a spawn, allocate a child of
 * type 0xF4 and copy in the owner id, coordinates, state byte and sprite flip;
 * then reset this script slot's parameter and dispatch the spawn callback. */
void sub_0803A2A0(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *actor = *((u8 **) (self + 0x38));
  u8 *enemy = *((u8 **) (self + 0x3C));
  u8 *enemyData = enemy + 0x34;
  u8 *enemyState = enemy + 0x48;
  sub_080113A8((s32) actor, enemyData);
  if ((*enemyData) & 2)
  {
    void *child = sub_0805FB24(self, 0xF4);
    if (child != 0)
    {
      u8 ownerId = self[0x4C];
      u8 *childDst = (u8 *)child + 0x4C;
      u8 zero = 0;
      *childDst = ownerId;
      *((u32 *)((u8 *)child + 0x5C)) = *((u32 *)(enemy + 0x08));
      *((u32 *)((u8 *)child + 0x6C)) = *((u32 *)(enemy + 0x0C));
      {
        u8 stateValue = enemyState[0x0C];
        struct SpawnedChild *childObj = (struct SpawnedChild *)child;
        childObj->state = stateValue;
        childObj->unk_84 = zero;
      }
      {
        u16 flipBits = (*((u16 *)(actor + 2))) & 0x10;
        if (flipBits != 0)
        {
          *((u8 *)child + 0x80) = 1;
        }
        else
        {
          *((u8 *)child + 0x80) = (u8)flipBits;
        }
      }
    }
    self[((*((s16 *)(self + 0x22))) * 2) + 0x19] = 0;
    {
      s32 *lit = (s32 *) 0x08671BB0;
      sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
  }
}
