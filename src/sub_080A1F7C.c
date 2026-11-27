extern void allocWorkSlot(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallbacks;
/* Script-step callback: initialises the companion sprite, flags this entity,
 * resets then advances its script step, redirects the script, and finally
 * dispatches the handler indexed by the new step's byte. No companion -> bail. */
void sub_080A1F7C(u8 *entity)
{
  s16 stepIndex;
  u8 *scriptPtr;
  u8 *spriteState;
  s32 zero;
  allocWorkSlot(entity, 0, 0x48, 0);
  if ((*((u32 *) (entity + 0x3C))) == 0)
  {
    sub_080C31E0(entity, *((void **) (entity + 0x24)));
    return;
  }
  spriteState = *((u8 **) (entity + 0x3C));
  zero = 0;
  *((u16 *) (spriteState + 0x1C)) = 0x54;
  (entity + 0x4C)[0] = zero;
  *((u16 *) (entity + 0x02)) |= 0x1000;
  stepIndex = *((s16 *) (entity + 0x22));
  entity[(stepIndex * 2) + 0x19] = zero;
  {
    void **lit = &gMainObjTimerCallbacks;
    scriptPtr = entity + 0x18;
    sub_080C31E4(scriptPtr, entity + 0x22, *lit);
  }
  stepIndex = *((s16 *) (entity + 0x22));
  entity[(stepIndex * 2) + 0x19]++;
  stepIndex = *((s16 *) (entity + 0x22));
  scriptPtr = scriptPtr + (stepIndex * 2);
  sub_080C31E0(entity, *((void **) ((*((u32 *) (entity + 0x14))) + (scriptPtr[0] * 4))));
}
