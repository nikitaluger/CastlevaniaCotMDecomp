extern s32 checkGlobalStateChange(void *a, void *b, void *c);
extern void stepDelayTimer(void *a, void *b);
extern void sub_0806D588(void *a, void *b);
extern void cullOffscreenEntity(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, void *c);
extern void sub_080C31E0(void *a, void *b);
struct Mover { u8 _0[4]; s32 posY; s32 velX; s32 velY; u8 _10[0x2C-0x10]; void *moveCtrl; u8 _30[0x48-0x30]; s32 timer; };
struct Actor { u8 _0[4]; s32 posX; s32 posY; s32 velX; s32 velY; u8 _14[0x2C-0x14]; void *moveCtrl; u8 _30[0x48-0x30]; s32 timer; };
struct Script { u8 _0[0x22]; s16 step; void *callback; u8 _28[0x38-0x28]; void *world; u8 _3C[0x6C-0x3C]; struct Actor *actor; };
struct GameState { u8 _0[0x10]; s32 field10; u8 _1[0x14ED-0x14]; u8 field14ED; u8 _2[0x173A-0x14EE]; u8 field173A; u8 _3[0x18C2-0x173B]; u16 field18C2; };
extern struct GameState gMainWorkspace;
extern void *gMainObjTimerCallbacks;

/* One frame of a scripted actor: skip it while an area movement override is
 * active, otherwise integrate velocity, count down the script timer (restoring
 * the script step when it expires) and decide between aborting the script and
 * running the off-screen check. */
void sub_08078FA8(struct Script *arg0)
{
  void *worldCopy;
  struct Actor *actor;
  struct Mover *mover;
  void *world;
  s32 timer;
  s32 zero;
  u16 stateValue;
  actor = arg0->actor;
  mover = (struct Mover *)((u8 *)actor + 4);
  world = arg0->world;
  if (checkGlobalStateChange(arg0, world, mover) != 0) return;
  actor->posX += mover->velX;
  mover->posY += mover->velY;
  stateValue = gMainWorkspace.field18C2;
  zero = 0;
  *(u16 *)world = stateValue;
  timer = mover->timer;
  timer -= 1;
  mover->timer = timer;
  if (timer == 0) {
    void **cmdTable;
    timer = 0x19;
    *((u8 *)(mover->moveCtrl) + 1) = zero;
    *((u8 *)((u8 *)arg0 + arg0->step * 2) + timer) = zero;
    cmdTable = &gMainObjTimerCallbacks;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *cmdTable);
  }
  stepDelayTimer((u8 *)actor + 0x20, world);
  sub_0806D588(world, mover);
  if (gMainWorkspace.field173A == 0x1C ||
      (gMainWorkspace.field14ED == 0 && gMainWorkspace.field10 != 0)) {
    sub_080C31E0(arg0, arg0->callback);
  } else {
    worldCopy = world;
    cullOffscreenEntity(arg0, worldCopy);
  }
}
