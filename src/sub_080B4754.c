/*
 * Actor jump action: force animation frame 0x5F, tick it, and when that frame
 * reports its trigger marker integrate the actor's motion plus a downward
 * velocity impulse; once vertical velocity turns non-negative, set the actor's
 * flag, clear a byte on the parent and dispatch the actor callback.
 */
extern s32 setObjectAnimation(void *, void *, s32, s32);
extern void sub_08011528(void *, void *);
extern void advanceMotion(void *, s32);
extern s32 sub_080B7290(s32);
extern void sub_080C31E4(void *, void *, s32);

/* Frame-table entries are 4 bytes; the property word is at offset +2. */
struct FrameProp { u8 _pad[2]; u16 value; };

/* The action's fixed frame, trigger property and velocity impulse. */
#define ACTION_FRAME       0x5F
#define TRIGGER_PROP       0x4E
#define VY_IMPULSE         0x200

void sub_080B4754(void *arg0)
{
  u8 *actor = (u8 *) arg0;
  void **frameTablePtr;
  void *animOwner = *((void **) (actor + 0x38));
  void *actorState = *((void **) (actor + 0x3C));
  u8 *anim = ((u8 *) actorState) + 0x34;
  u8 *auxState = ((u8 *) actorState) + 0x48;
  setObjectAnimation(animOwner, anim, ACTION_FRAME, 0);
  sub_08011528(animOwner, anim);
  frameTablePtr = *((void ***) (anim + 0x08));
  {
    s32 frameIndex = (*((s16 *) (anim + 0x0E))) + (*((u8 *) (anim + 0x01)));
    void **table = frameTablePtr;
    u16 frameProp = ((struct FrameProp *)((u8 *) table[0] + (frameIndex * 4) - 4))->value;
    if (frameProp == TRIGGER_PROP)
    {
      advanceMotion(actorState, 0);
      *((s32 *) (((u8 *) actorState) + 0x14)) += VY_IMPULSE;
    }
  }
  if ((*((s32 *) (((u8 *) actorState) + 0x14))) >= 0)
  {
    sub_080B7290(*((s32 *) (((u8 *) auxState) + 0x14)));
    *((u8 *) ((actor + ((*((s16 *) (actor + 0x22))) * 2)) + 0x19)) = 0;
    {
      s32 *callbackTable = (s32 *) 0x08671BB0;
      sub_080C31E4(actor + 0x18, actor + 0x22, *callbackTable);
    }
  }
}
