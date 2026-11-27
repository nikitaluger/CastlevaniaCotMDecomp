extern u32 D_081020DC[];
extern void *gScriptStepCallbackTable;
extern s32 sub_08005910(s32 a, s32 b);
extern u32 scaleByRandom(u32 a);
extern s32 sub_0801473C(s32 a, s32 b);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);

/* Pick a renewed facing angle that differs from the current one, store it and
 * its turn direction on the actor's tracker, then run the current script step. */
void sub_080A7C7C(void *arg0)
{
  void *entity;
  u8 *turnRateSlot;
  void *actor;
  void *ai;
  s32 currentAngle;
  u32 r0;
  u32 chosenAngle;
  u32 angleMax;
  u32 angleBase;
  s16 stepOffset;
  u8 stepByte;
  void *r1;
  entity = arg0;
  actor = *((void **) (((u8 *) entity) + 0x3C));
  ai = ((u8 *) actor) + 0x48;
  {
    u32 ax = *((u32 *) (((u8 *) ai) + 0x1C));
    u32 bx = *((u32 *) (((u8 *) ai) + 0x08));
    u32 dx = ax - bx;
    u32 ay = *((u32 *) (((u8 *) ai) + 0x18));
    u32 by = *((u32 *) (((u8 *) ai) + 0x04));
    currentAngle = sub_08005910(dx, ay - by);
  }
  r0 = 0x108;
  r1 = ((u8 *) actor) + r0;
  r0 = (u32)currentAngle & 0xFFFF;
  *((u32 *) r1) = r0;
  angleMax = D_081020DC[0];
  angleBase = D_081020DC[1];
  do
  {
    r0 = angleMax - angleBase;
    r0 = scaleByRandom(r0);
    chosenAngle = r0 + angleBase;
  }
  while (chosenAngle == ((u32) currentAngle));
  r0 = sub_0801473C(currentAngle, chosenAngle);
  r1 = ((u8 *) ai) + 0xC4;
  turnRateSlot = ((u8 *) ai) + 0xD0;
  *((u32 *) r1) = chosenAngle;
  r1 = turnRateSlot;
  r0 = r0 << 4;
  *((u32 *) r1) = r0;
  r0 = ((u8 *) ai) + 0xC8;
  r1 = 0;
  *((u32 *) r0) = r1;
  r0 = ((u8 *) ai) + 0xD8;
  *((u8 *) r0) = (u8) r1;
  stepOffset = *((s16 *) (((u8 *) entity) + 0x22));
  r0 = ((u8 *) entity) + (stepOffset * 2);
  *((u8 *) (r0 + 0x19)) = 0;
  {
    void **lit = &gScriptStepCallbackTable;
    void *stepBase = ((u8 *) entity) + 0x18;
    sub_080C31E4(stepBase, ((u8 *) entity) + 0x22, *lit);
    actor = stepBase;
  }
  stepOffset = *((s16 *) (((u8 *) entity) + 0x22));
  ((u8 *) entity)[(stepOffset * 2) + 0x19]++;
  stepOffset = *((s16 *) (((u8 *) entity) + 0x22));
  actor = ((u8 *) actor) + (stepOffset * 2);
  stepByte = *((u8 *) actor);
  r1 = *((void **) (((u8 *) entity) + 0x14));
  r0 = ((u32) stepByte) << 2;
  r0 = r0 + ((u32) r1);
  r1 = *((void **) ((void *) r0));
  sub_080C31E0(entity, r1);
}
