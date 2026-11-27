extern s32 isOutsideCameraBounds(s32, s32);
extern void sub_08027A10(void *);
extern s32 randomSignedOffset(s32);
extern s32 scaleByRandom(s32);
extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, s32);
extern s32 updateObjectDisplayState(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
struct MoveFlags { u8 _0; u8 active; };
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

static inline u8 setBit6Byte(u8 value) { u32 mask = 0x40; mask |= value; return (u8)mask; }
static inline u16 setBit0Half(u16 value) { u32 mask = 1; mask |= value; return (u16)mask; }

/* Per-frame update for a moving entity: cull it when it leaves the camera view, follow its
 * owner, launch it with a random velocity under gravity, advance one script step, then
 * mirror its world position into sprite coordinates. */
void updateMovingScriptedEntity(u8 *entity)
{
  s32 sprite = *((s32 *) (entity + 0x38));
  u8 *state = *((u8 **) (entity + 0x3C));
  u8 *animTrack = state + 0x34;
  u8 *stepState = state + 0x48;

  if (isOutsideCameraBounds(*((s32 *) (state + 8)), *((s32 *) (state + 0xC))) == 1)
  {
    ((struct MoveFlags *) (*((u8 **) (state + 0x28))))->active = 0;
    ((u8 *) sprite)[0x2A] = ((u8 *) sprite)[0x2A] & 0xBF;
    if (((*((u16 *) (entity + 0x64))) & 2) == 0) goto epilogue;
  }
  else
  {
    ((struct MoveFlags *) (*((u8 **) (state + 0x28))))->active = 1;
    { u8 spriteFlags = *(volatile u8 *)((u8 *)sprite + 0x2A); *((u8 *)sprite + 0x2A) = setBit6Byte(spriteFlags); }
  }

  sub_08027A10(entity);
  do
  {
    if ((*((u16 *) (entity + 0x64))) & 0x41)
    {
      u16 stateFlags = *(volatile u16 *)state;
      *(u16 *)state = setBit0Half(stateFlags);
    }
    if ((*((u16 *) state)) & 1)
    {
      ((struct MoveFlags *) (*((u8 **) (state + 0x28))))->active = 0;
      if (entity[((*((s16 *) (entity + 0x22))) * 2) + 0x1A] != 5)
      {
        s32 *callback;
        *((u32 *) (stepState + 0x10)) = 0x16C1;
        *((u32 *) (state + 0x10)) = randomSignedOffset(0x4000);
        *((u32 *) (state + 0x14)) = scaleByRandom(0x2000);
        {
          void *owner = *((void **) (entity + 0x30));
          if (owner != NULL)
          {
            sub_080C31E0(owner, *((void **) (((u8 *) owner) + 0x24)));
          }
        }
        entity[((*((s16 *) (entity + 0x22))) * 2) + 0x1B] = 0;
        callback = (s32 *) SCRIPT_EVENT_CALLBACK_TABLE;
        sub_080C31E8(entity + 0x18, entity + 0x22, 5, *callback);
      }
    }
    if (updateObjectDisplayState((void *) sprite, state) == 0)
    {
      s32 stepOffset;
      u8 *scriptSteps;
      u8 opcode;
      void **stepHandlers;
      *((u32 *) (entity + 0x14)) = MOVING_ENTITY_STEP_TABLE;
      *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) + 1;
      {
        u32 timerOffset = (u32)(*((s16 *) (entity + 0x22))) * 2;
        u8 *stepEntry = (u8 *)(timerOffset + (u32)entity);
        stepEntry[0x19] = stepEntry[0x19] + 1;
      }
      stepOffset = (*((s16 *) (entity + 0x22))) * 2;
      scriptSteps = entity + 0x18;
      opcode = *(scriptSteps + stepOffset);
      stepHandlers = *((void **) (entity + 0x14));
      sub_080C31E0(entity, stepHandlers[opcode]);
      *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) - 1;
      if (((*((u16 *) (entity + 2))) & SCRIPT_OBJ_FLAG_SKIP_ANIM) == 0)
      {
        stepAnimationTrack((void *) sprite, animTrack);
        advanceMotion(state, *((s32 *) (stepState + 0x10)));
      }
      else
      {
        goto epilogue;
      }
    }
    {
      u8 *cameraTable = gCameraState;
      u8 *workspace = gMainWorkspace;
      u8 *scrollXBase;
      u8 *scrollYBase;
      u32 scrollRow;
      workspace += 0x18A8;
      scrollRow = (((u32) (*workspace)) + 1) * 0x40;
      scrollXBase = cameraTable + 0x1278;
      *((u32 *) (((u8 *) sprite) + 0x14)) = (*((u32 *) (((u8 *) state) + 0x08))) - (((*((u32 *) (scrollXBase + scrollRow))) + 0x8000) & 0xFFFF0000);
      scrollRow = (((u32) (*workspace)) + 1) * ((unsigned char) 0x40);
      scrollYBase = cameraTable + 0x127C;
      *((u32 *) (((u8 *) sprite) + 0x18)) = (*((u32 *) (((u8 *) state) + 0x0C))) - (((*((u32 *) (scrollYBase + scrollRow))) + 0xFFFF8000) & 0xFFFF0000);
    }
  epilogue:
    ;
  } while (0);
  ;
}
