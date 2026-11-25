extern s32 sub_0806D518(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_08003740(void *);
extern void sub_0806D2F8(void *, void *);
extern void sub_0808DBF8(s32, s32, s32);
extern void sub_080C31E0(void *, s32);
struct GlobalState {
  u8 _0[0x10];
  u32 f0010;
  u8 _1[0x14ED - 0x14];
  u8 f14ED;
  u8 _2[0x173A - 0x14EE];
  u8 f173A;
  u8 _3[0x18C2 - 0x173B];
  u16 f18C2;
};
extern struct GlobalState D_02025FF0;

/* Entity AI callback: advance position, react to a one-way collision, then end or continue. */
void sub_0807F490(u8 *self)
{
  u8 *actor;
  u8 *work;
  u8 *body;
  u8 *state;
  u8 *statePtr;
  struct GlobalState *gs;
  u32 newX;
  u8 *hit;
  actor = *((u8 **) (self + 0x6C));
  statePtr = self + 0x38;
  work = actor + 4;
  state = *((u8 **) statePtr);
  body = work;
  if (sub_0806D518(self, state, body) != 0)
  {
    return;
  }
  newX = (*((u32 *) (actor + 4))) + (*((u32 *) (body + 8)));
  *((u32 *) (actor + 4)) = newX;
  hit = *((u8 **) (body + 0x2C));
  if (((*((u16 *) (hit + 0x14))) & 1) && (!((*((u16 *) (hit + 0x14))) & 2)))
  {
    sub_0808DBF8(newX, *((u32 *) (body + 4)), 0);
  }
  *((u16 *) ((*((u8 **) (work + 0x2C))) + 0x14)) = 0;
  gs = &D_02025FF0;
  *((u16 *) state) = gs->f18C2;
  sub_08003740(work + 0x1C);
  sub_0806D588(state, body);
  if ((gs->f173A == 0x1C) || ((gs->f14ED == 0) && (gs->f0010 != 0)))
  {
    sub_080C31E0(self, *((s32 *) (self + 0x24)));
    return;
  }
  sub_0806D2F8(self, state);
}
