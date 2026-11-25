extern void sub_080113A8(void *, void *);

/* Byte at +0x2A of the actor holds a sprite-attribute flag. */
struct ActorFlags { u8 pad[0x2A]; u8 flag; };

/*
 * Follow-entity update: mirror the sprite flag and priority bits onto the
 * actor, shift the two coordinate ring buffers held on the enemy (storing new
 * coordinates from self and recalling the previous ones), then run the actor's
 * display step.
 */
void sub_0803532C(void *arg0)
{
  u8 *ringIndex;
  u8 *ringBase;
  u8 *actor;
  u8 *enemyData;
  u8 *enemy;
  u8 *ringBase2;
  u8 *pFlag;
  u32 slotOffset;

  actor = *((u8 **) (((u8 *) arg0) + 0x38));
  enemy = *((u8 **) (((u8 *) arg0) + 0x3C));
  enemyData = enemy + 0x34;
  ringBase = enemy + 0x48;
  if ((*((u8 *) (enemy + 0x68))) & 1)
  {
    pFlag = actor + 0x2A;
    *pFlag &= 0xBF;
  }
  else
  {
    ((struct ActorFlags *)actor)->flag |= 0x40;
  }
  *((u16 *) actor) = ((*((u16 *) actor)) & 0xFFF) | (0xC0 << 8);
  ringIndex = ringBase + 0x20;
  slotOffset = (((*ringIndex) - 1) & 3) * 4;
  *((u32 *) (ringBase + slotOffset)) = *((u32 *) (((u8 *) arg0) + 0x4C));
  slotOffset = (((*ringIndex) - 1) & 3) * 4;
  {
    ringBase2 = ringBase + 0x10;
    *((u32 *) (ringBase2 + slotOffset)) = *((u32 *) (((u8 *) arg0) + 0x5C));
    slotOffset = ((*ringIndex) & 3) * 4;
    *((u32 *) (enemy + 8)) = *((u32 *) (ringBase + slotOffset));
    slotOffset = ((*ringIndex) & 3) * 4;
    *((u32 *) (enemy + 0xC)) = *((u32 *) (ringBase2 + slotOffset));
  }
  *ringIndex = (*ringIndex) + 1;
  sub_080113A8(actor, enemyData);
}
