extern void stepAnimationTrack(void *, void *);
extern s32 isOutsideCameraBounds(s32, s32);
extern u8 *hitTestEntities(u8 *);
extern s32 _call_via_r1(s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern s16 gAttackTargetKinds[];
extern u8 gTargetedAttackStepTable[];

/* Per-frame update of a targeted scripted attack: clear the target's transient
 * hit flag, show/hide the sprite according to the camera-bounds test, resolve a
 * pending hit target against the allowed-kind table, dispatch one script step,
 * then advance the animation and place the sprite at its camera-relative
 * world position. */
void updateTargetedScriptedAttack(u8 *entity)
{
  u8 *sprite;
  u8 *state;
  u8 *animTrack;
  s32 outsideCamera;
  u8 *scrollTable;
  u8 *scrollXRow;
  u8 *frameCounterPtr;
  u32 scrollRow;
  u32 scrollX;
  u32 scrollY;
  u32 stepOpcode;
  u8 *stepStream;
  u32 scrollYRaw;
  u8 *hitTarget;
  s16 *kindCursor;
  s16 *nextKind;
  s32 hitKind;
  s32 targetAcquired;
  sprite = *((u8 **) (entity + 0x38));
  state = *((u8 **) (entity + 0x3C));
  animTrack = state + 0x20;
  {
    u8 *target = *((u8 **) (state + 4));
    u8 zero = ATTACK_TARGET_CLEAR;
    *((u8 *) (target + 1)) = zero;
  }
  outsideCamera = isOutsideCameraBounds(*((s32 *) (state + 0xC)), *((s32 *) (state + 0x10)));
  if (outsideCamera == 1)
  {
    ((struct AttackSpriteFlags *) (sprite + 0x2A))->flag &= ATTACK_SPRITE_SHOW_MASK;
  }
  else
  {
    ((struct AttackSpriteFlags *) (sprite + 0x2A))->flag |= ATTACK_SPRITE_HIDE_FLAG;
  }
  targetAcquired = *((s16 *) (state + 0x16));
  stepStream = entity + 0x18;
  if (targetAcquired == 0)
  {
    *((u8 *) ((*((u8 **) (state + 4))) + 1)) = ATTACK_TARGET_PENDING;
    hitTarget = hitTestEntities(*((u8 **) (state + 4)));
    if (hitTarget != NULL)
    {
      kindCursor = gAttackTargetKinds;
      if ((*kindCursor) != 0)
      {
        do
        {
          hitKind = *((s16 *) (hitTarget + 0x18));
          nextKind = kindCursor;
          do
          {
            if (hitKind == (*kindCursor))
            {
              *((s16 *) (state + 0x16)) = 1;
              break;
            }
            nextKind++;
            kindCursor++;
          }
          while ((*nextKind) != 0);
        }
        while (0);
      }
    }
  }
  *((u32 *) (entity + 0x14)) = (u32) gTargetedAttackStepTable;
  *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) + 1;
  *((u8 *) (((u32) entity) + ((u32) (*((s16 *) (entity + 0x22)))) * 2 + 0x19)) = (*((u8 *) (((u32) entity) + ((u32) (*((s16 *) (entity + 0x22)))) * 2 + 0x19))) + 1;
  stepOpcode = *((u8 *) (((u32) stepStream) + ((u32) (*((s16 *) (entity + 0x22)))) * 2));
  _call_via_r1((s32) entity, *((u32 *) ((*((u32 *) (entity + 0x14))) + (stepOpcode * 4))));
  *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) - 1;
  if (((*((u16 *) (entity + 2))) & SCRIPT_OBJ_FLAG_SKIP_ANIM) == 0)
  {
    if ((*((s16 *) (state + 0x14))) == 1)
    {
      stepAnimationTrack(sprite, animTrack);
    }
    scrollTable = gCameraState;
    frameCounterPtr = gMainWorkspace;
    frameCounterPtr += 0x18A8;
    scrollRow = (((u32) (*frameCounterPtr)) + 1) * 0x40;
    scrollXRow = scrollTable + 0x1278;
    scrollX = *((u32 *) (scrollXRow + scrollRow));
    *((u32 *) (sprite + 0x14)) = (*((u32 *) (state + 0xC))) - ((scrollX + 0x8000) & 0xFFFF0000);
    scrollRow = (((u32) (*frameCounterPtr)) + 1) * 0x40;
    scrollTable += 0x127C;
    scrollYRaw = *((u32 *) (scrollTable + scrollRow));
    scrollY = scrollYRaw;
    *((u32 *) (sprite + 0x18)) = (*((u32 *) (state + 0x10))) - ((scrollY + 0xFFFF8000) & 0xFFFF0000);
  }
}
