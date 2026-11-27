/* Per-frame update of the arcing trail attack: switches its start/loop
 * animation, oscillates its angle through the IWRAM sine table, and every few
 * frames spawns a dust/impact object along the trail; when the trail count runs
 * out it advances the entity to the next state. */
extern u8 gMainWorkspace[];   /* scene state (camera index at +0x18A8) */
extern u8 D_00001870[];   /* address constant for the camera index */
extern s32 setAnimationFrame(s32, void *, s32, s32);   /* set animation frame */
extern s32 terrainHasSolidFlags(s32, s32);                /* terrain has solid flags? */
extern s32 spawnBudgetedEffect(s32, s32);                /* spawn budgeted effect object */
extern s32 divInt32(s32, s32);                /* division */
extern s32 sub_080C31E0(void *, void *);          /* indirect call (sine routine) */
extern void sub_080C31E8(void *, void *, s32, void *); /* state machine dispatch */

/* Per-frame update of the arcing trail attack: animate, oscillate the spawn angle, emit dust points, then advance state when the trail runs out. */ void updateArcingTrailAttack(void *entity)
{
  s32 sprite;
  u8 *work;
  u8 *gfxInit;
  u8 *trailState;
  u16 oldSpawnTimer;
  u16 newSpawnTimer;
  s32 pointIndex;
  s32 spawnX;
  s32 spawnY;
  s32 pointOffset;
  u8 *pointsBase;
  void *dust;
  s32 fixedX;
  s32 fixedY;
  s32 dustX;
  s32 dustY;
  s32 remainingPoints;
  s16 pointsLeft;
  u32 *trigFuncTable;
  u32 *stateCallbackTable;
  s32 zero;

  sprite = *((s32 *) (((u8 *) entity) + 0x38));
  work = *((u8 **) (((u8 *) entity) + 0x3C));
  gfxInit = work + 0x34;
  trailState = work + 0x48;
  if ((*((s16 *) (trailState + 0x10))) == 1)
  {
    setAnimationFrame(sprite, gfxInit, 0, 1);
    if ((gfxInit[1] == 1) && ((*((s32 *) (gfxInit + 0x04))) == 1))
    {
      *((u16 *) (trailState + 0x04)) = 0;
    }
    trigFuncTable = (u32 *) 0x08671BFC;
    *((s32 *) (trailState + 0x00)) = sub_080C31E0(divInt32((*((s16 *) (trailState + 0x04))) << 16, 0x24), (void *) *trigFuncTable) * 2;
    *((u16 *) (trailState + 0x04)) = (*((u16 *) (trailState + 0x04))) + 1;
  }
  else
  {
    setAnimationFrame(sprite, gfxInit, 8, 0);
    if (gfxInit[0] & 2)
    {
      *((s16 *) (trailState + 0x10)) = 1;
    }
  }
  pointsLeft = *((s16 *) (trailState + 0x0E));
  if ((pointsLeft <= 0) && (((s32) ((*((u16 *) (trailState + 0x08))) << 16)) <= 0))
  {
    zero = 0;
    *((u16 *) (trailState + 0x06)) = 0x1E;
    *((((u8 *) entity) + ((*((s16 *) (((u8 *) entity) + 0x22))) * 2)) + 0x17) = zero;
    stateCallbackTable = (u32 *) 0x08671BD8;
    sub_080C31E8(((u8 *) entity) + 0x18, ((u8 *) entity) + 0x22, 3, (void *) *stateCallbackTable);
    return;
  }
  oldSpawnTimer = *((u16 *) (trailState + 0x08));
  *((u16 *) (trailState + 0x08)) = (newSpawnTimer = oldSpawnTimer - 1);
  if (((s32) (newSpawnTimer << 16)) < 0)
  {
    pointIndex = 0xA - (*((s16 *) (trailState + 0x0E)));
    spawnX = (*((s32 *) (trailState + 0x14))) - ((pointIndex * (*((s16 *) (trailState + 0x24)))) * 0x180000);
    spawnY = *((s32 *) (trailState + 0x18));
    if ((terrainHasSolidFlags(spawnX, spawnY) == 0) && (terrainHasSolidFlags(spawnX - ((*((s16 *) (trailState + 0x24))) << 20), spawnY + 0x10000) == 1))
    {
      dust = (void *) spawnBudgetedEffect(*((s32 *) ((u32) D_00001870 + (u32) gMainWorkspace)), 0xA2);
      pointOffset = pointIndex * 4;
      pointsBase = trailState + 0x28;
      *((void **) (pointsBase + pointOffset)) = dust;
      if (dust != NULL)
      {
        if ((*((s16 *) (trailState + 0x24))) < 0)
          *((u16 *) (((u8 *) dust) + 0x6C)) = 0x10;
        else
          *((u16 *) (((u8 *) dust) + 0x6C)) = 0x20;
        fixedX = spawnX;
        if (fixedX < 0)
          fixedX += 0xFFFF;
        dustX = fixedX >> 16;
        *((s16 *) (((u8 *) dust) + 0x4C)) = dustX;
        fixedY = spawnY;
        if (fixedY < 0)
          fixedY += 0xFFFF;
        dustY = fixedY >> 16;
        *((s16 *) (((u8 *) dust) + 0x54)) = dustY;
        *((void **) (((u8 *) dust) + 0x8C)) = entity;
      }
    }
    *((u16 *) (trailState + 0x08)) = 8;
    remainingPoints = (*((u16 *) (trailState + 0x0E))) - 1;
    *((u16 *) (trailState + 0x0E)) = remainingPoints;
    if ((remainingPoints << 16) == 0)
      *((u16 *) (trailState + 0x08)) = 0x10;
  }
}
