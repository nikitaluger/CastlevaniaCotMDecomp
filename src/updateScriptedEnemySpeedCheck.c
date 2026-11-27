s32 checkActorViewBounds(void *, void *);
void applySpritePaletteVariant(void *, void *);
s32 sub_08013558(void *, void *, s32);
void spawnContactEffectOnHit(void *, s32);
void uploadPendingSpriteGraphic(void *, void *);
void updateActorWorldPosition(void *);
void sub_08005E80(s32);
s32 updateObjectDisplayState(void *, void *);
void _call_via_r1(void *, s32);
void _call_via_r3(void *, void *, s32, s32);
void sub_08011460(void *, void *, s32);
void sub_08011EE8(void *, s32, s32);
void sub_08013C8C(void *, void *);
extern u32 sScriptStepCallbacks;
struct P28 { u8 pad[0x14]; u16 f14; };
struct Flags { u16 f0; };

/* Script-driven enemy update with a movement-speed check: run hit/damage
 * helpers, flag oversized velocities, then advance the script and dispatch
 * its handler, optionally applying a movement/animation update. */
void updateScriptedEnemySpeedCheck(u8 *entity)
{
  u8 *owner = *(u8 **)(entity + 0x38);
  u8 *comp = *(u8 **)(entity + 0x3C);
  u8 *status = comp + 0x34;
  u8 *compTail = comp + 0x48;
  u16 f2, f4;
  u32 bit0;
  if (checkActorViewBounds(owner, comp) == 1) goto end;
  applySpritePaletteVariant(entity, owner);
  if (sub_08013558(owner, comp, *(s32 *)(comp + 0x28)) != 0)
    spawnContactEffectOnHit(entity, *(s32 *)(comp + 0x28));
  if (((struct P28 *)*(void **)(comp + 0x28))->f14 & 1)
  {
    s32 spd = *(s32 *)(comp + 0x10);
    if (spd < 0) spd = -spd;
    if ((spd > (0x80 << 10)) || (*(s32 *)(comp + 0x14) > (0x80 << 10)))
      *(u16 *)(comp + 0) |= 1;
  }
  f2 = *(u16 *)(comp + 2);
  bit0 = f2 & 1;
  f4 = f2;
  if (bit0)
  {
    s32 spd = *(s32 *)(comp + 0x10);
    if (spd < 0) spd = -spd;
    if (spd > (0x80 << 10)) *(u16 *)(comp + 0) |= 1;
  }
  if (f4 & 4)
  {
    if (*(s32 *)(comp + 0x14) > (0x80 << 10))
      ((struct Flags *)comp)->f0 |= 1;
  }
  uploadPendingSpriteGraphic(entity, *(void **)(comp + 0x28));
  if (*(u16 *)(comp + 0) & 1)
  {
    u8 *step = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    if (step[0x1A] != 3)
    {
      updateActorWorldPosition(entity);
      sub_08005E80(0x8B);
      {
        u8 *step2 = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        step2[0x1B] = 0;
        {
          u32 *audioCmd = (u32 *)0x08671BDC;
          _call_via_r3(entity + 0x18, entity + 0x22, 3, *audioCmd);
        }
      }
    }
  }
  if (updateObjectDisplayState(owner, comp) == 0)
  {
    *(u32 *)(entity + 0x14) = 0x0866DBC0;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    {
      u8 *step = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
      step[0x19] = step[0x19] + 1;
    }
    {
      s32 stepOffset = (*(s16 *)(entity + 0x22)) * 2;
      u8 *scriptData = entity + 0x18;
      u8 handlerId = *(scriptData + stepOffset);
      _call_via_r1(entity, *(u32 *)(*(u32 *)(entity + 0x14) + handlerId * 4));
    }
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    if (*(u16 *)(entity + 2) & 0x8000) goto end;
    sub_08011460(owner, status, *(u32 *)compTail);
    sub_08011EE8(comp, 0x16C1, 0);
  }
  *(u16 *)(*(u8 **)(comp + 0x28) + 0x14) = 0;
  sub_08013C8C(entity, owner);
end:
  return;
}
