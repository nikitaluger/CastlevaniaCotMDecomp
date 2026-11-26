/* Per-frame update of the arcing trail attack: switches its start/loop
 * animation, oscillates its angle through the IWRAM sine table, and every few
 * frames spawns a dust/impact object along the trail; when the trail count runs
 * out it advances the entity to the next state. */
extern u8 gMainWorkspace[];   /* scene state (camera index at +0x18A8) */
extern u8 D_00001870[];   /* address constant for the camera index */
extern s32 setAnimationFrame(s32, void *, s32, s32);   /* set animation frame */
extern s32 sub_080133EC(s32, s32);                /* terrain has solid flags? */
extern s32 sub_0805FAEC(s32, s32);                /* spawn budgeted effect object */
extern s32 sub_080C364C(s32, s32);                /* division */
extern s32 sub_080C31E0(void *, void *);          /* indirect call (sine routine) */
extern void sub_080C31E8(void *, void *, s32, void *); /* state machine dispatch */

void sub_0802318C(void *entity)
{
  s32 sprite;
  u8 *work;
  u8 *gfxInit;
  u8 *trail;
  u16 timerValue;
  u16 newTimer;
  s32 index;
  s32 spawnX;
  s32 spawnY;
  s32 slotOffset;
  u8 *slotBase;
  void *spawned;
  s32 x;
  s32 y;
  s32 vx;
  s32 vy;
  s32 countLeft;
  s16 animFrame;
  u32 *sinFuncs;
  u32 *stateTable;
  s32 zero;

  sprite = *((s32 *) (((u8 *) entity) + 0x38));
  work = *((u8 **) (((u8 *) entity) + 0x3C));
  gfxInit = work + 0x34;
  trail = work + 0x48;
  if ((*((s16 *) (trail + 0x10))) == 1)
  {
    setAnimationFrame(sprite, gfxInit, 0, 1);
    if ((gfxInit[1] == 1) && ((*((s32 *) (gfxInit + 0x04))) == 1))
    {
      *((u16 *) (trail + 0x04)) = 0;
    }
    sinFuncs = (u32 *) 0x08671BFC;
    *((s32 *) (trail + 0x00)) = sub_080C31E0(sub_080C364C((*((s16 *) (trail + 0x04))) << 16, 0x24), (void *) *sinFuncs) * 2;
    *((u16 *) (trail + 0x04)) = (*((u16 *) (trail + 0x04))) + 1;
  }
  else
  {
    setAnimationFrame(sprite, gfxInit, 8, 0);
    if (gfxInit[0] & 2)
    {
      *((s16 *) (trail + 0x10)) = 1;
    }
  }
  animFrame = *((s16 *) (trail + 0x0E));
  if ((animFrame <= 0) && (((s32) ((*((u16 *) (trail + 0x08))) << 16)) <= 0))
  {
    zero = 0;
    *((u16 *) (trail + 0x06)) = 0x1E;
    *((((u8 *) entity) + ((*((s16 *) (((u8 *) entity) + 0x22))) * 2)) + 0x17) = zero;
    stateTable = (u32 *) 0x08671BD8;
    sub_080C31E8(((u8 *) entity) + 0x18, ((u8 *) entity) + 0x22, 3, (void *) *stateTable);
    return;
  }
  timerValue = *((u16 *) (trail + 0x08));
  *((u16 *) (trail + 0x08)) = (newTimer = timerValue - 1);
  if (((s32) (newTimer << 16)) < 0)
  {
    index = 0xA - (*((s16 *) (trail + 0x0E)));
    spawnX = (*((s32 *) (trail + 0x14))) - ((index * (*((s16 *) (trail + 0x24)))) * 0x180000);
    spawnY = *((s32 *) (trail + 0x18));
    if ((sub_080133EC(spawnX, spawnY) == 0) && (sub_080133EC(spawnX - ((*((s16 *) (trail + 0x24))) << 20), spawnY + 0x10000) == 1))
    {
      spawned = (void *) sub_0805FAEC(*((s32 *) ((u32) D_00001870 + (u32) gMainWorkspace)), 0xA2);
      slotOffset = index * 4;
      slotBase = trail + 0x28;
      *((void **) (slotBase + slotOffset)) = spawned;
      if (spawned != NULL)
      {
        if ((*((s16 *) (trail + 0x24))) < 0)
          *((u16 *) (((u8 *) spawned) + 0x6C)) = 0x10;
        else
          *((u16 *) (((u8 *) spawned) + 0x6C)) = 0x20;
        x = spawnX;
        if (x < 0)
          x += 0xFFFF;
        vx = x >> 16;
        *((s16 *) (((u8 *) spawned) + 0x4C)) = vx;
        y = spawnY;
        if (y < 0)
          y += 0xFFFF;
        vy = y >> 16;
        *((s16 *) (((u8 *) spawned) + 0x54)) = vy;
        *((void **) (((u8 *) spawned) + 0x8C)) = entity;
      }
    }
    *((u16 *) (trail + 0x08)) = 8;
    countLeft = (*((u16 *) (trail + 0x0E))) - 1;
    *((u16 *) (trail + 0x0E)) = countLeft;
    if ((countLeft << 16) == 0)
      *((u16 *) (trail + 0x08)) = 0x10;
  }
}
