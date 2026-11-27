struct S_02025FF0
{
  u8 _0[0x10];
  u32 f10;
  u8 _1[0x14ED - 0x14];
  u8 f14ED;
  u8 _2[0x173A - 0x14EE];
  u8 f173A;
  u8 _3[0x18A8 - 0x173B];
  u8 f18A8;
  u8 _4[0x18C2 - 0x18A9];
  u16 f18C2;
};
extern struct S_02025FF0 gMainWorkspace;
extern u32 gTilemapPages;
extern u32 D_084DD0AC;
extern u32 gMainObjTimerCallbacks;
void stepDelayTimer(void *);
void startEffectTimer(void *, s32, void *);
void playSound(s32);
s32 getTileTerrainB(s32, s32);
void *spawnEntity(s32, s32, s32, s32);
void releaseEntityIfOffscreen(void *, void *);
s32 checkGlobalStateChange(void *, void *, void *);
void setSpriteScreenPosition(void *, void *);
s32 sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
inline u8 *inline_fn(void **arg0)
{
  return (u8 *) (*arg0);
}

void sub_0807936C(void *arg0)
{
  u8 *new_var4;
  u8 *new_var6;
  void *r4 = *((void **) (((u8 *) arg0) + 0x6C));
  int new_var7;
  u8 *new_var;
  s32 *new_var3;
  u8 *new_var2;
  void *r6 = ((u8 *) r4) + 4;
  void **new_var5;
  void *r8 = *((void **) (((u8 *) arg0) + 0x38));
  s32 i;
  new_var3 = &(*((s32 *) (((u8 *) r6) + 0x54)));
  if (checkGlobalStateChange(arg0, r8, r6) != 0)
  {
    return;
  }
  *((s32 *) (((u8 *) r6) + 0x0C)) = (*((s32 *) (new_var2 = ((u8 *) r6) + 0x0C))) + (new_var7 = 0x4000);
  if ((*((s32 *) (((u8 *) r6) + 0x0C))) > 0x80000)
  {
    *((s32 *) (((u8 *) r6) + 0x0C)) = 0x80000;
  }
  new_var5 = &r6;
  *((s32 *) (((u8 *) r4) + 0x04)) = (*((s32 *) (((u8 *) r4) + 0x04))) + (*((s32 *) (inline_fn(new_var5) + 0x08)));
  i = (*((s32 *) (((u8 *) r6) + 0x04))) + (*((s32 *) (((u8 *) r6) + 0x0C)));
  *((s32 *) (((u8 *) r6) + 0x04)) = i;
  *((s32 *) (((u8 *) r6) + 0x54)) = (*(&(*((s32 *) (((u8 *) r6) + 0x54))))) - 1;
  new_var6 = ((u8 *) r6) + 0x1C;
  if ((((*((u16 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 0x14))) & 1) || ((getTileTerrainB((gMainWorkspace.f18A8 << 6) + ((u32) (&gTilemapPages)), *((s32 *) (((u8 *) r4) + 0x04))) << 16) != 0)) || ((*new_var3) == 0))
  {
    void *var_r4 = new_var6;
    new_var = (u8 *) arg0;
    startEffectTimer(var_r4, 0, (void *) 0x084DD0AC);
    *((u8 *) (((u8 *) (*((void **) (((u8 *) r6) + 0x2C)))) + 0x01)) = 0;
    playSound(0x149);
    for (i = 0; i <= 7; i++)
    {
      void *t = spawnEntity(*((s32 *) (((u8 *) arg0) + 0x28)), 0x4A, 0x0A, 0x12);
      if (t)
      {
        *((s32 *) (((u8 *) t) + 0x7C)) = *((s32 *) (((u8 *) r6) + 0x00));
        *((s32 *) (((u8 *) t) + 0x8C)) = *((s32 *) (((u8 *) r6) + 0x04));
        *((s32 *) (((u8 *) t) + 0x9C)) = i;
      }
    }

    *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) = 0;
    sub_080C31E4(new_var + 0x18, new_var + 0x22, gMainObjTimerCallbacks);
  }
  *((u16 *) r8) = gMainWorkspace.f18C2;
  new_var4 = (u8 *) r4;
  stepDelayTimer(new_var4 + 0x20);
  setSpriteScreenPosition(r8, r6);
  i = *((u8 *) (((u8 *) (&gMainWorkspace)) + 0x173A));
  if ((i == 0x1C) || ((gMainWorkspace.f14ED == 0) && (gMainWorkspace.f10 != 0)))
  {
    sub_080C31E0(arg0, *((s32 *) (new_var + 0x24)));
  }
  else
  {
    releaseEntityIfOffscreen(arg0, r8);
  }
}

