extern s32 sub_08005910(s32, s32);
extern void sub_08011528(void *, void *);
extern void sub_0809E4F8(void *);
extern void sub_080C31E4(void *, void *, u32);
typedef struct { s32 v[8]; } S32x8;
extern const S32x8 D_081019B4;
extern u32 gScriptStepCallbackTable;

/* Refreshes the actor's animation, then on script step 0x10 picks a direction
 * vector from an eight-entry table using the angle to the player, stores it as
 * the actor's velocity, clears the step and advances the script. */
void sub_0809D9D4(void *arg0)
{
  s32 vectorTable[8];
  void *self;
  void *actor;
  void *gfx;
  u8 *anim;
  u8 *state;
  s32 tableOffset;
  s32 zero;
  s32 deltaY;
  s32 deltaX;
  s32 *entry2;
  u32 *msgPtr;

  self = arg0;
  gfx = *((void **) (((u8 *) self) + 0x38));
  actor = *((void **) (((u8 *) self) + 0x3C));
  anim = ((u8 *) actor) + 0x34;
  state = ((u8 *) actor) + 0x48;
  *((S32x8 *) vectorTable) = D_081019B4;
  sub_08011528(gfx, anim);
  sub_0809E4F8(self);
  if ((*((u8 *) ((((u8 *) self) + ((*((s16 *) (((u8 *) self) + 0x22))) * 2)) + 0x19))) == 0x10)
  {
    s32 base = 0x02025FF0;
    deltaY = (*((s32 *) (base + 0x1750))) - (*((s32 *) (((u8 *) actor) + 0x0C)));
    deltaX = (*((s32 *) (base + 0x174C))) - (*((s32 *) (((u8 *) actor) + 0x08)));
    tableOffset = sub_08005910(deltaY, deltaX);
    tableOffset = (tableOffset >> 14) << 3;
    *((s32 *) (((u8 *) actor) + 0x10)) = vectorTable[tableOffset >> 2];
    entry2 = vectorTable + 1;
    *((s32 *) (((u8 *) actor) + 0x14)) = *(s32 *)((s32)entry2 + (s32)(tableOffset >> 2 << 2));
    zero = 0;
    {
      *((s32 *) (((u8 *) self) + 0x04)) = zero;
      *((s32 *) (((u8 *) state) + 0x44)) = zero;
      *((u8 *) ((((u8 *) self) + ((*((s16 *) (((u8 *) self) + 0x22))) * 2)) + 0x19)) = (u8) zero;
    }
    msgPtr = &gScriptStepCallbackTable;
    sub_080C31E4(((u8 *) self) + 0x18, ((u8 *) self) + 0x22, *msgPtr);
  }
}
