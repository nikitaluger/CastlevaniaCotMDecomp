s32 checkActorViewBounds(void *, void *);
void applySpritePaletteVariant(void *, void *);
s32 sub_08013558(void *, void *, s32);
void spawnContactEffectOnHit(void *, s32);
void uploadPendingSpriteGraphic(void *, void *);
void updateActorWorldPosition(void *);
void playSound(s32);
s32 updateObjectDisplayState(void *, void *);
void _call_via_r1(void *, s32);
void _call_via_r3(void *, void *, s32, s32);
void sub_08011460(void *, void *, s32);
void sub_08011EE8(void *, s32, s32);
void sub_08013C8C(void *, void *);
extern u32 sScriptStepCallbacks;
struct ContactStatus { u8 pad[0x14]; u16 status; };
struct WorkFlags { u16 flags; };

/* Updates one script-driven enemy: applies the hit/damage responses, flags
 * oversized velocities, advances and dispatches its script step, then animates
 * and moves the work and clears the contact status. */
void updateScriptedEnemySpeedCheck(u8 *enemy)
{
  u8 *sprite = *(u8 **)(enemy + 0x38);
  u8 *work = *(u8 **)(enemy + 0x3C);
  u8 *animTrack = work + 0x34;
  u8 *stepState = work + 0x48;
  u16 workFlags, savedFlags;
  u32 hitFlag;
  if (checkActorViewBounds(sprite, work) == 1) goto end;
  applySpritePaletteVariant(enemy, sprite);
  if (sub_08013558(sprite, work, *(s32 *)(work + 0x28)) != 0)
    spawnContactEffectOnHit(enemy, *(s32 *)(work + 0x28));
  if (((struct ContactStatus *)*(void **)(work + 0x28))->status & 1)
  {
    s32 speed = *(s32 *)(work + 0x10);
    if (speed < 0) speed = -speed;
    if ((speed > (0x80 << 10)) || (*(s32 *)(work + 0x14) > (0x80 << 10)))
      *(u16 *)(work + 0) |= 1;
  }
  workFlags = *(u16 *)(work + 2);
  hitFlag = workFlags & 1;
  savedFlags = workFlags;
  if (hitFlag)
  {
    s32 speed = *(s32 *)(work + 0x10);
    if (speed < 0) speed = -speed;
    if (speed > (0x80 << 10)) *(u16 *)(work + 0) |= 1;
  }
  if (savedFlags & 4)
  {
    if (*(s32 *)(work + 0x14) > (0x80 << 10))
      ((struct WorkFlags *)work)->flags |= 1;
  }
  uploadPendingSpriteGraphic(enemy, *(void **)(work + 0x28));
  if (*(u16 *)(work + 0) & 1)
  {
    u8 *stepPtr = (u8 *)((u32)(*(s16 *)(enemy + 0x22)) * 2 + (u32)enemy);
    if (stepPtr[0x1A] != 3)
    {
      updateActorWorldPosition(enemy);
      playSound(0x8B);
      {
        u8 *stepPtr2 = (u8 *)((u32)(*(s16 *)(enemy + 0x22)) * 2 + (u32)enemy);
        stepPtr2[0x1B] = 0;
        {
          u32 *eventCallback = (u32 *)0x08671BDC;
          _call_via_r3(enemy + 0x18, enemy + 0x22, 3, *eventCallback);
        }
      }
    }
  }
  if (updateObjectDisplayState(sprite, work) == 0)
  {
    *(u32 *)(enemy + 0x14) = 0x0866DBC0;
    *(u16 *)(enemy + 0x22) = *(u16 *)(enemy + 0x22) + 1;
    {
      u8 *stepPtr = (u8 *)((u32)(*(s16 *)(enemy + 0x22)) * 2 + (u32)enemy);
      stepPtr[0x19] = stepPtr[0x19] + 1;
    }
    {
      s32 stepOffset = (*(s16 *)(enemy + 0x22)) * 2;
      u8 *stepStream = enemy + 0x18;
      u8 stepOpcode = *(stepStream + stepOffset);
      _call_via_r1(enemy, *(u32 *)(*(u32 *)(enemy + 0x14) + stepOpcode * 4));
    }
    *(u16 *)(enemy + 0x22) = *(u16 *)(enemy + 0x22) - 1;
    if (*(u16 *)(enemy + 2) & 0x8000) goto end;
    sub_08011460(sprite, animTrack, *(u32 *)stepState);
    sub_08011EE8(work, 0x16C1, 0);
  }
  *(u16 *)(*(u8 **)(work + 0x28) + 0x14) = 0;
  sub_08013C8C(enemy, sprite);
end:
  return;
}
