/* Per-frame update of the player's action state: syncs the camera and shared
 * result flags, advances the action timer/physics from the D_080E03A0 table,
 * runs the action, body and sprite handlers, then either plays the follow-up
 * (spawning effect 9) or dispatches the next state when the action timer or a
 * hit fires. */
struct ActionTiming            /* 0x58-byte per-action timing entry */
{
  s32 speed;                   /* per-frame increment of the action timer */
  s32 max;                     /* timer clamp */
  u8 rest[0x50];
};
extern struct ActionTiming D_080E03A0[];
struct S_02025FF0_63F80
{
  u8 _0[0x24];
  s32 f24;                     /* 0x24: nonzero = use latched key state */
  u8 _28[2];
  u16 f2A;                     /* 0x2A: latched key state */
  u8 _2C[0x14ED - 0x2C];
  u8 f14ED;                    /* 0x14ED: game mode */
  u8 _14EE[0x1514 - 0x14EE];
  s32 f1514;                   /* 0x1514: reset request flag */
  u8 _1518[0x1754 - 0x1518];
  s32 f1754;                   /* 0x1754: small slot counter */
};
extern struct S_02025FF0_63F80 D_02025FF0;
struct S_02021E90_63F80
{
  u8 _0[0x146E];
  u16 f146E;                   /* 0x146E: raw key state */
};
extern struct S_02021E90_63F80 D_02021E90;
extern s32 sub_08003740(void *, void *);          /* decrement timer / fire callback */
extern void sub_08005E80(s32);                    /* play sound */
extern void sub_0806A7AC(void *, void *, s32);    /* set entity form */
extern void sub_0806A884(void *, void *);         /* clamp sprite position */
extern void sub_0806B104(void *, void *, void *); /* action handler */
extern void sub_0806BA20(void *, void *, void *); /* action timer / keys */
extern s32 sub_0806C4B4(void *, void *);          /* camera/view sync */
extern void sub_0806C5EC(void *, void *, void *, void *); /* reset result flags */
extern void sub_0806C6B0(void *, void *, void *, void *); /* common update tail */
extern void sub_0806E114(void *, s32, s32, s32);  /* spawn entity by definition */
extern void sub_08086240(void *, s32);            /* body part handler */
extern void sub_08086648(void *, void *, s32);    /* body part handler */
extern void sub_08086744(void *, void *, void *, s32); /* body part handler */
extern void sub_08086D58(void *, s32);            /* body part handler */
extern void sub_080C31E8(void *, void *, s32, s32); /* state machine dispatch */
extern void sub_0806AB04(void *, void *, void *, void *); /* action handler */
extern u16 sub_0806BCD8(void *, void *, void *, void *);  /* hit check -> next state */

void sub_08063F80(u8 *entity)
{
  u8 *work = *((u8 **) (entity + 0x6C)) + 4;   /* action state block */
  u8 *sprite = *((u8 **) (entity + 0x38));
  u8 *state = work;                            /* alias used for call args */
  u8 *p = (u8 *) 0x02025368;                   /* stats block, later the result pointer */
  u8 *timing;
  int stateTable;
  s32 timingOffset;
  s32 timerMax;
  u16 keys;
  s32 actionId;
  int resultOffset;
  s32 zero;
  u8 *timer;
  u32 nextState;
  u32 zero70 = 0;
  if (sub_0806C4B4(work, work) != 0)
  {
    return;
  }
  sub_0806C5EC(entity, sprite, state, state);
  sub_0806BA20(sprite, state, state);
  timing = (u8 *) 0x080E03A0;
  actionId = *((s32 *) (state + 0x44));
  timingOffset = actionId * 0x58;
  *((s32 *) (state + 0x0C)) = (*((s32 *) (state + 0x0C))) + (*((s32 *) (timingOffset + timing)));
  timing += 4;
  timerMax = *((s32 *) (timingOffset + timing));
  resultOffset = 0xC4;
  if ((*((s32 *) (state + ((short) 0x0C)))) > timerMax)
  {
    *((s32 *) (state + 0x0C)) = timerMax;
  }
  keys = (D_02025FF0.f24 != 0) ? (D_02025FF0.f2A & (*((u16 *) (p + 0x3BC)))) : (D_02021E90.f146E & (*((u16 *) (p + 0x3BC))));
  if (keys == 0)
  {
    *((s32 *) (work + 0x70)) = zero70;
  }
  sub_08086744(entity, work, state, 0xB);
  sub_0806B104(sprite, work, state);
  sub_0806AB04(entity, sprite, work, state);
  if ((*((s32 *) (work + 0x40))) == 1)
  {
    sub_08005E80(0x67);
    *((s32 *) (work + 0x4C)) = 0;
    *((s32 *) (work + 0x50)) = 0;
    *((s32 *) (work + 0x54)) = 0;
    if (D_02025FF0.f14ED == 0x35)
    {
      if (D_02025FF0.f1754 <= 8)
      {
        D_02025FF0.f1754 = 9;
      }
    }
    sub_08086240(work, 9);
    zero = 0;
    *((s32 *) (state + 0x08)) = zero;
    sub_0806E114(entity, 9, *((s32 *) (state + 0x00)), *((s32 *) (state + 0x04)));
    (entity + ((*((s16 *) (entity + 0x22))) * 2))[0x19] = (u8) zero;
    {
      s32 *g = (s32 *) 0x08671BD0;
      sub_080C31E8(entity + 0x18, entity + 0x22, 9, *g);
    }
  }
  sub_0806A884(sprite, state);
  p = work;
  p += 0x28;
  {
    u8 *tmp = p;
    s32 r = sub_08003740(tmp, sprite);
    timer = tmp;
    if ((r == 0) || (D_02025FF0.f1514 != 0))
    {
      sub_0806A7AC(sprite, work, 0x10);
      sub_08003740(timer, sprite);
      (entity + ((*((s16 *) (0x22 + entity))) * 2))[0x19] = 0;
      {
        s32 *g = (s32 *) 0x08671BD0;
        sub_080C31E8(entity + 0x18, entity + 0x22, 3, *g);
      }
    }
  }
  sub_08086648(sprite, work, 0xB);
  sub_08086D58(work, 0xB);
  nextState = sub_0806BCD8(entity, sprite, work, state);
  p = work;
  p += (unsigned long long) resultOffset;
  *((s32 *) p) = (u16) nextState;
  if (((u16) nextState) != 0)
  {
    sub_08003740(timer, sprite);
    (entity + ((*((s16 *) (entity + 0x22))) * 2))[0x19] = 0;
    stateTable = 0x08671BD0;
    sub_080C31E8(entity + 0x18, entity + 0x22, *((s32 *) p), *((s32 *) stateTable));
  }
  sub_0806C6B0(entity, sprite, work, state);
}
