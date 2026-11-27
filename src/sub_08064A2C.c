extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806BA20(void *, void *, void *);
extern void sub_0806B104(void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_08005E80(s32);
extern void spawnKind2CEntity(void *, s32, s32, s32);
extern void sub_0806A884(void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern void sub_0806A7AC(void *, void *, s32);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
struct FF0
{
  u8 _0[0x14ED];
  u8 f14ED;
  u8 _1[0x1754 - 0x14EE];
  s32 f1754;
};
extern struct FF0 gMainWorkspace;
struct Actor
{
  u8 _0[8];
  s32 f8;
  s32 speed;
  u8 _10[0x40 - 0x10];
  s32 state;
  s32 type;
  u8 _48[4];
  s32 f4C;
  s32 f50;
  s32 f54;
};
/* Per-frame update for a moving actor: run the collision, movement and
 * animation steps, accelerate it using the per-type speed table, handle the
 * state transition, then run any command script the actor just reached. */
void sub_08064A2C(u8 *arg0)
{
  u8 *timer;
  u8 *state;
  u8 *obj;
  u8 *sprite;
  s32 table;
  s32 typeOfs;
  u8 *spriteRef;
  state = *((u8 **) (arg0 + 0x6C)) + 4;
  sprite = *((u8 **) (arg0 + 0x38));
  spriteRef = sprite;
  obj = state;
  if (syncViewPosition(obj, obj) != 0)
  {
    return;
  }
  resetActionResultState(arg0, spriteRef, obj, obj);
  sub_0806BA20(spriteRef, obj, obj);
  table = 0x080E03A0;
  typeOfs = ((struct Actor *) obj)->type * 0x58;
  ((struct Actor *) obj)->speed = ((struct Actor *) obj)->speed + (*((s32 *) (table + typeOfs)));
  table += 4;
  {
    s32 lim = *((s32 *) (table + typeOfs));
    if (((struct Actor *) obj)->speed > lim)
    {
      ((struct Actor *) obj)->speed = lim;
    }
  }
  sub_0806B104(spriteRef, obj, obj);
  sub_0806AB04(arg0, spriteRef, obj, obj);
  if (((struct Actor *) obj)->state == 1)
  {
    u8 *q;
    s32 *g;
    sub_08005E80(0x67);
    ((struct Actor *) obj)->f4C = 0;
    ((struct Actor *) obj)->f50 = 0;
    ((struct Actor *) obj)->f54 = 0;
    if (gMainWorkspace.f14ED == 0x35)
    {
      if (gMainWorkspace.f1754 <= 8)
      {
        gMainWorkspace.f1754 = 9;
      }
    }
    ((struct Actor *) obj)->f8 = 0;
    spawnKind2CEntity(arg0, 9, *((s32 *) (obj + 0)), *((s32 *) (obj + 4)));
    q = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    *((u8 *) (q + 0x19)) = 0;
    g = (s32 *) 0x08671BD0;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x10, *g);
  }
  sub_0806A884(spriteRef, obj);
  timer = state + 0x28;
  if (stepDelayTimer(timer, spriteRef) == 0)
  {
    u8 *q;
    s32 *g;
    sub_0806A7AC(spriteRef, state, 0x10);
    stepDelayTimer(timer, spriteRef);
    q = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    *((u8 *) (q + 0x19)) = 0;
    g = (s32 *) 0x08671BD0;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 3, *g);
  }
  *((s32 *) (state + 0xC4)) = (u16) sub_0806BCD8(arg0, spriteRef, state, obj);
  if ((*((s32 *) (state + 0xC4))) != 0)
  {
    u8 *q;
    s32 *g;
    stepDelayTimer(timer, spriteRef);
    q = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    *((u8 *) (q + 0x19)) = 0;
    g = (s32 *) 0x08671BD0;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, *((s32 *) (state + 0xC4)), *g);
  }
  sub_0806C6B0(arg0, spriteRef, state, obj);
}
