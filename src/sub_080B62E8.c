extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080B7134(void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0 { u8 _0[0x18C2]; u16 word18C2; };
extern struct S_02025FF0 gMainWorkspace;

/* Spawn a sprite plus motion state for this actor, initialise its animation and
 * position, then run the current script step and switch to the step's handler. */
void sub_080B62E8(void *entity)
{
  void *sprite;
  void *motion;
  void *animState;
  u8 *actionList;
  u8 *actionEntry;
  s32 *stepHandlers;
  s32 zero;

  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    sub_080C31E0(entity, *((s32 *)(((char *) entity) + 0x24)));
    return;
  }
  *((void **)(((char *) entity) + 0x38)) = sprite;
  allocWorkSlot(entity, 0, 0x48, 0);
  if ((*((vu32 *)(((char *) entity) + 0x3C))) == 0)
  {
    sub_080C31E0(entity, *((s32 *)(((char *) entity) + 0x24)));
    return;
  }
  *((s32 *)(((char *) sprite) + 0x1C)) = 0x80000009;
  motion = *((void **)(((char *) entity) + 0x3C));
  animState = ((char *) motion) + 0x34;
  zero = 0;
  *((s16 *)(((char *) motion) + 0x1C)) = 0x66;
  *((u16 *) sprite) |= (&gMainWorkspace)->word18C2;
  *((s32 *)(((char *) motion) + 0x08)) = *((s32 *)(((char *) entity) + 0x4C));
  *((s32 *)(((char *) motion) + 0x0C)) = *((s32 *)(((char *) entity) + 0x5C));
  sub_080B7134(sprite, animState);
  setAnimationFrame(sprite, animState, 0x15, 0);
  *((u16 *)(((char *) entity) + 0x02)) |= 0x1000;
  {
    u8 *stepFlagPtr = (u8 *) ((((s16) (*((s16 *) (((char *) entity) + 0x22)))) * 2) + ((u32) entity));
    stepFlagPtr[0x19] = zero;
  }
  {
    void **scriptTable = (void **) 0x08671BB0;
    actionList = ((char *) entity) + 0x18;
    sub_080C31E4(actionList, ((char *) entity) + 0x22, (s32) (*scriptTable));
  }
  {
    u8 *stepFlagPtr = (u8 *) ((((s16) (*((s16 *) (((char *) entity) + 0x22)))) * 2) + ((u32) entity));
    stepFlagPtr[0x19] = stepFlagPtr[0x19] + 1;
  }
  actionEntry = actionList + (((s16) (*((s16 *) (((char *) entity) + 0x22)))) * 2);
  {
    u8 actionId = *actionEntry;
    stepHandlers = *((s32 **) (((char *) entity) + 0x14));
    sub_080C31E0(entity, stepHandlers[actionId]);
  }
}
