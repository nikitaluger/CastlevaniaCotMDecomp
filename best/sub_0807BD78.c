struct S02025FF0
{
  u8 pad0[0x24];
  u32 f24;
  u8 pad28[0x02];
  u16 f2A;
  u8 pad2C[0x14C1];
  u8 f14ED;
  u8 pad14EE[0x23A];
  u32 f1728;
  u32 f172C;
  u8 pad1730[8];
  u16 f1738;
};
extern struct S02025FF0 gMainWorkspace;
extern u8 gGameStatus[];
extern u8 gCameraState[];
extern u8 D_080E4E54[];
extern u8 D_080E47E8[];
extern u8 D_084E25C0[];
extern u8 D_084E25D4[];
s32 stepDelayTimer(void *, void *);
void startEffectTimer(void *, u32, u32);
void *spawnEntity(u32, u32, u32, u32);
s32 sub_0806D35C(void *, void *, void *);
void setSpriteScreenPosition(void *, void *);
void sub_0808DC40(s32, s32, u32);
void sub_080C31E0(u32, u32);
static inline u8 *inline_fn(u8 *arg0)
{
  return arg0;
}

inline static u8 *inline_fn2(u8 *arg0)
{
  return arg0 + 4;
}

void sub_0807BD78(void *arg0)
{
  u8 *s;
  u8 *p4;
  u8 *p8;
  int new_var5;
  u8 *v38;
  u32 new_var2;
  unsigned int new_var8;
  u8 *p5;
  u8 *new_var7;
  u8 *new_var3;
  u32 *new_var6;
  u8 *g;
  u8 *r6;
  u8 *new_var4;
  u8 *dEnd;
  s32 idx;
  s32 delta;
    s32 __repair_delta_1;
  s32 timer;
  s32 __repair_timer_1;
  void *other;
  void *other_gc;
  s32 *temp;
  s = (u8 *) arg0;
  other = *((u8 **) (s + 0x6C)); p4=(u8 *)other;
  p8 = inline_fn2(p4);
  do { v38 = *((u8 **) (s + 0x38)); } while (0);
  p5 = p8;
  g = gGameStatus;
  if (sub_0806D35C(s, v38, p5) != 0)
  {
    return;
  }
  new_var7 = p5 + 0x10;
  timer = ++(*((s32 *) new_var7));
  new_var4 = D_080E4E54;
  idx = ((timer >> 6) & 0xF) * 8;
  delta = *((s32 *) (new_var4 + idx));
  if (gMainWorkspace.f1738 & 0x10)
  {
    delta = -delta;
  }
  __repair_timer_1 = ((*((s32 *) (&gMainWorkspace.f1728))) + delta) - (*((s32 *) inline_fn2(p4)));
  if (__repair_timer_1 < 0)
  {
    __repair_timer_1 += 31;
  }
  *((s32 *) inline_fn2(p4)) = (*((s32 *) inline_fn2(p4))) + (__repair_timer_1 >> 5);
  temp = (s32 *) (inline_fn2(D_080E4E54) + idx);
  other_gc = (void *) (*((s32 *) (&gMainWorkspace.f172C))); __repair_delta_1 = (u32) other_gc + (*temp); __repair_timer_1 = __repair_delta_1 - (*((s32 *) inline_fn2(p5)));
  if (__repair_timer_1 < 0)
  {
    __repair_timer_1 += 31;
  }
  *((s32 *) (p5 + 4)) += __repair_timer_1 >> 5;
  new_var8 = 0x10;
  if (gMainWorkspace.f24 != 0)
  {
    if (gMainWorkspace.f2A & (*((u16 *) (gGameStatus + 0x3BC))))
    {
      r6 = (p8 + 0x1C);
      if (0 != (*((u32 *) (p8 + 0x54))))
      {
        timer = (*((u32 *) (p8 + 0x54))) - 1; goto dec;
      }
      do { startEffectTimer(r6, 0, (u32) D_084E25D4); } while (0);
      *((u32 *) (p8 + 0x54)) = 0x20;
    }
    else
    {
      r6 = p4 + 0x20;
    }
  }
  else
  {
    new_var5 = 0x146E;
    if (!((*((u16 *) (gCameraState + new_var5))) & (*((u16 *) (g + 0x3BC)))))
    {
      r6 = p4 + 0x20;
    }
    else
    {
      r6 = p8 + 0x1C;
      if ((*((u32 *) (p8 + 0x54))) != 0)
      {
        timer = (*((u32 *) (p8 + 0x54))) - 1; goto dec;
      }
      startEffectTimer(r6, 0, (u32) D_084E25D4);
      *((u32 *) (p8 + 0x54)) = 0x20;
    }
  }
  if ((*((u32 *) (p8 + 0x54))) == 0)
  {
    goto skip;
  }
  dEnd = (u8 *) (&gMainWorkspace);
  timer = (*((u32 *) (p8 + 0x54))) - 1;
dec:

  *((u32 *) (p8 + 0x54)) = timer;
  if (timer == 0x18)
  {
    other = spawnEntity(*((u32 *) (s + 0x28)), 0x54, 0x0A, 0x12);
    new_var6 = &(*((u32 *) p5));
    if (other != NULL)
    {
      s32 timer_a1;
      other_gc = other;
      other = NULL;
      *((u32 *) (((u8 *) other_gc) + 0x7C)) = *new_var6;
      *((u32 *) inline_fn(((u8 *) other_gc) + 0x8C)) = *((u32 *) (p5 + 4));
      timer_a1 = (((*((u8 *) (g + 0x304))) - 1) * 12) + ((idx = (*((u8 *) (g + 0x305))) - 1) * 120);
      *((u32 *) (gGameStatus + 0x2CC)) -= *((u32 *) (inline_fn2(D_080E47E8) + timer_a1));
    }
  }
  skip:
  if ((*((s32 *) p5)) > (*((s32 *) (dEnd + 0x1728))))
  {
    *((u16 *) (v38 + 2)) |= new_var8;
  }
  else
  {
    *((u16 *) (v38 + 2)) &= 0xFFEF;
  }

  if (stepDelayTimer(r6, v38) == 0)
  {
    startEffectTimer(r6, 0, (u32) D_084E25C0);
  }
  new_var2 = (u32) s;
  setSpriteScreenPosition(v38, p5);
  if ((*((u8 *) (dEnd + 0x14ED))) == 0x81)
  {
    return;
  }
  sub_0808DC40(*((s32 *) p5), *((s32 *) inline_fn2(p5)), 0);
  sub_080C31E0(new_var2, *((u32 *) (s + 0x24)));
}

