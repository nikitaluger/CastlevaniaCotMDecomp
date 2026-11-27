extern s32 stepDelayTimer(void *, void *);
extern void playSound(void);
extern s32 getTileTerrainB(s32, s32, s32);
extern s32 cullOffscreenEntity(void *, void *);
extern s32 checkGlobalStateChange(void *, void *, void *);
extern void setSpriteScreenPosition(void *, void *);
extern void spawnKind2CEntity(s32, s32, s32, s32);
extern void sub_0808DBF8(s32, s32, s32);
extern void sub_080C31E0(void *, s32);
struct T
{
  u8 _0[0x38];
  s32 f38;
  u8 _3C[4];
  u16 f40;
  u8 _42[2];
  s32 f44;
  s32 f48;
};
struct F0
{
  u8 _0[0x10];
  s32 f10;
  u8 _14[0x14ED - 0x14];
  u8 f14ED;
  u8 _14EE[0x173A - 0x14EE];
  u8 f173A;
  u8 _173B[0x18A8 - 0x173B];
  u8 f18A8;
  u8 _18A9[0x19];
  u16 f18C2;
};
extern struct F0 gMainWorkspace;
extern s32 gTilemapPages[];
void sub_0807699C(void *arg0)
{
  struct T *tbl;
  void *p6C;
  void *p6C4;
  void *p38;
  void *r4;
  s32 cnt;
  s32 v;
  int new_var;
  do { p6C = *((void **) (((u8 *) arg0) + 0x6C)); } while (0);
  do { p6C4 = ((u8 *) p6C) + 4; } while (0);
  p38 = *((void **) (((u8 *) arg0) + 0x38));
  r4 = p6C4;
  if (checkGlobalStateChange(arg0, p38, r4) != 0)
  {
    return;
  }
  tbl = (struct T *) (((u8 *) 0x080E51D4) + ((*((s32 *) (((u8 *) arg0) + 0x7C))) * 0x4C));
  cnt = (*((s32 *) (((u8 *) r4) + 0x54))) - 1;
  *((s32 *) (((u8 *) r4) + 0x54)) = cnt;
  if (cnt == 0)
  {
    goto fail;
  }
  v = (*((s32 *) (((u8 *) r4) + 0x0C))) + (*((s32 *) (((u8 *) r4) + 0x58)));
  *((s32 *) (((u8 *) r4) + 0x0C)) = v;
  new_var = 0x0C;
  if (v > 0x80000)
  {
    *((s32 *) (((u8 *) r4) + new_var)) = 0x80000;
  }
  *((s32 *) (((u8 *) p6C) + 4)) += *((s32 *) (((u8 *) r4) + 8));
  *((s32 *) (((u8 *) r4) + 4)) += *((s32 *) (((u8 *) r4) + 0x0C));
  if (((*((u16 *) (((u8 *) (*((void **) (((u8 *) r4) + 0x2C)))) + 0x14))) & 1) && (!((*((u16 *) (((u8 *) (*((void **) (((u8 *) r4) + 0x2C)))) + 0x14))) & 2)))
  {
    sub_0808DBF8(*((s32 *) (((u8 *) p6C) + 4)), *((s32 *) (((u8 *) r4) + 4)), 0);
    if (tbl->f38 != 0)
    {
      goto fail;
    }
  }
  *((u16 *) (((u8 *) (*((void **) (((u8 *) p6C4) + 0x2C)))) + 0x14)) = 0;
  if (tbl->f38 != 0)
  {
    if ((getTileTerrainB((0x02023130) + (((s32) gMainWorkspace.f18A8) << 6), *((s32 *) (((u8 *) r4) + 0)), *((s32 *) (((u8 *) r4) + 4))) << 16) != 0)
    {
      sub_0808DBF8(*((s32 *) (((u8 *) r4) + 0)), *((s32 *) (((u8 *) r4) + 4)), 0);
      if (tbl->f40 != 0)
      {
        playSound();
      }
      goto fail;
    }
  }
  *((u16 *) p38) = gMainWorkspace.f18C2;
  if (tbl->f44 >= 0)
  {
    if ((--(*((s32 *) (((u8 *) p6C4) + 0x5C)))) == 0)
    {
      if (((*((u16 *) (((u8 *) p38) + 2))) & 0x10) == 0)
      {
        do { do { spawnKind2CEntity(*((s32 *) (((u8 *) arg0) + 0x28)), tbl->f44 | 0x10000000, *((s32 *) (((u8 *) r4) + 0)), *((s32 *) (((u8 *) r4) + 4))); } while (0); } while (0);
      }
      else
      {
        do { do { spawnKind2CEntity(*((s32 *) (((u8 *) arg0) + 0x28)), tbl->f44 | 0x20000000, *((s32 *) (((u8 *) r4) + 0)), *((s32 *) (((u8 *) r4) + 4))); } while (0); } while (0);
      }
      *((s32 *) (((u8 *) p6C4) + 0x5C)) = tbl->f48;
    }
  }
  stepDelayTimer(((u8 *) p6C4) + 0x1C, p38);
  setSpriteScreenPosition(p38, r4);
  if ((gMainWorkspace.f173A == 0x1C) || ((gMainWorkspace.f14ED == 0) && (gMainWorkspace.f10 != 0)))
  {
    fail:
    sub_080C31E0(arg0, *((s32 *) (((u8 *) arg0) + 0x24)));

    return;
  }
  do { do { cullOffscreenEntity(arg0, p38); } while (0); } while (0);
}

