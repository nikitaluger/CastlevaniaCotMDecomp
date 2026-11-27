s32 nextRandomWord(void);
s32 getAngleFromDelta(s32, s32);
void setSpriteFacingToTarget(void *, s32);
void sub_0809E32C(void *, void *, void *, void *);
void sub_0809E490(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Shared player position, stored as 16.16 fixed point. */
struct PlayerPos {
  u8 pad[0x174C];
  s32 x;
  s32 y;
};
extern struct PlayerPos gMainWorkspace;

/* Aim block at +0x48 of the AI data. */
struct AimState {
  u8 _0[0x0C];
  u8 timer;
  u8 _0D[0x21];
  u16 angle;
  u32 flag;
};

/* Enemy AI state: on timer == 30, aim at the player with a random angular spread. */
void sub_0809D3E8(void *arg0)
{
  void *gfx;
  void *ai;
  void *anim;
  struct AimState *state;
  gfx = *((void **) (((u8 *) arg0) + 0x38));
  ai = *((void **) (((u8 *) arg0) + 0x3C));
  anim = ((u8 *) ai) + 0x34;
  state = (struct AimState *)(((u8 *) ai) + 0x48);
  sub_0809E32C(gfx, anim, ai, state);
  setSpriteFacingToTarget(gfx, *((s32 *) (((u8 *) ai) + 8)));
  if ((*((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19))) == 0x1E)
  {
    s32 zero = 0;
    s32 jitter;
    s32 angle;
    state->timer = zero;
    sub_0809E490(ai, state);
    jitter = nextRandomWord() & 1;
    if (jitter == 0)
    {
      jitter = -1;
    }
    angle = getAngleFromDelta(gMainWorkspace.y - (*((s32 *) (((u8 *) ai) + 0x0C))), gMainWorkspace.x - (*((s32 *) (((u8 *) ai) + 0x08))));
    state->angle = angle + (jitter << 14);
    state->flag = zero;
    *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) = 0;
    {
      s32 *lit = (s32 *) 0x08671BB0;
      sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *lit);
    }
  }
}
