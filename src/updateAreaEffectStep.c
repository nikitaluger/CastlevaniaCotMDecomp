extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u8 D_084A4C84[];
extern u8 D_084A4C98[];
/* These symbols are used only for their addresses: they are byte offsets into
 * gMainWorkspace (0x174C/0x1750/0x18C2/0x14ED) materialised as link-time literals. */
extern u8 D_0000174C[];
extern u8 D_00001750[];
extern u8 D_000018C2[];
extern u8 D_000014ED[];
extern s32 applyAreaEffectBehavior(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern void startEffectTimer(void *, s32, void *);

/* Update a timer-driven effect: run the area special-behavior check, handle
 * the 0xA5/0xA8 command bytes, snap the effect's position to the shared
 * target point, convert it to screen space and tick its action timer. */
/* Update an area-effect action step: run the special-area behavior probe, apply the 0xA5/0xA8 distance commands, copy the shared target position into the effect state, place its sprite on screen, refresh its coordinates and tick the delay timer. */ void updateAreaEffectStep(void *actor)
{
  void *workBase = *((void **) (((u8 *) actor) + 0x6C));
  u8 *state = ((u8 *) workBase) + 4;
  u8 *workspace;
  void *sprite = *((void **) (((u8 *) actor) + 0x38));
  void *pos = state;
  u8 *status = gGameStatus;
  s16 targetY;
  u8 command;
  void *timer;

  if (applyAreaEffectBehavior(actor, sprite, state) != 0)
  {
    return;
  }
  command = *((u8 *) (((u8 *) workBase) + 0x55));
  switch (command)
  {
    case 0xA5:
      targetY = *((s16 *) (status + 0x2EA));
      if ((*((s32 *) (((u8 *) state) + 0x58))) < targetY)
      {
        startEffectTimer(((u8 *) workBase) + 0x20, 0, D_084A4C84);
      }
      break;

    case 0xA8:
      if ((*((s32 *) (((u8 *) state) + 0x54))) < (*((s16 *) (status + 0x2E2))))
      {
        startEffectTimer(((u8 *) workBase) + 0x20, 0, D_084A4C84);
      }
      break;
  }

  workspace = gMainWorkspace;
  *((s32 *) pos) = *((s32 *) (((u32) workspace) + ((u32) D_0000174C)));
  *((s32 *) (((u8 *) pos) + 4)) = *((s32 *) (((u32) workspace) + ((u32) D_00001750)));
  sub_0806D588(sprite, pos);
  *((s32 *) (((u8 *) state) + 0x54)) = *((s16 *) (status + 0x2E2));
  *((s32 *) (((u8 *) state) + 0x58)) = *((s16 *) (status + 0x2EA));
  *((u16 *) sprite) = *((u16 *) (((u32) workspace) + ((u32) D_000018C2)));
  timer = ((u8 *) state) + 0x1C;
  if (stepDelayTimer(timer, sprite) == 0)
  {
    startEffectTimer(timer, 0, D_084A4C98);
  }
  if ((*((u8 *) (((u32) workspace) + ((u32) D_000014ED)))) != (*((u8 *) (((u8 *) state) + 0x51))))
  {
    ((void (*)(void *)) (*((void **) (((u8 *) actor) + 0x24))))(actor);
  }
}
