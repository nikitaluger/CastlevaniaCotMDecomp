extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u32 D_02027718;
void *allocEffectPart(void);
void cleanupFailedEffectSpawn(void *a);
s16 scalePercentSaturate16(u16 a, s32 b);
void startEffectTimer(void *a, s32 b, void *c);
void setDirectionVector(void *a, u8 b);
void *sub_08016A2C(void);
void sub_080C31E0(void *a, void *b);
void sub_080C31E4(void *a, void *b, s32 c);
extern s32 gMainObjTimerCallbacks[];
void sub_0807E710(void *arg0)
{
  u8 new_var3;
  u8 *base = *((u8 **) (((u8 *) arg0) + 0x6C));
  unsigned int new_var;
  u8 *p = base + 4;
  u8 *new_var2;
  u8 *dff0 = gMainWorkspace;
  u8 *cbase = gGameStatus;
  u8 *pcopy = base + 4;
  void *a;
  u8 *temp;
  int temp2;
  a = allocEffectPart();
  temp = base + 4;
  *((void **) (temp + 0x2C)) = a;
  if (0 == a)
  {
    cleanupFailedEffectSpawn(arg0);
    return;
  }
  *((u32 *) ((base + 4) + 0x30)) = (*((u32 *) ((base + 4) + 0x38)) = 0);
  *((u32 *) ((base + 4) + 0x34)) = 0;
  temp2 = (*((u8 *) (dff0 + 0x1510))) & 1;
  *((u32 *) ((base + 4) + 0x3C)) = 0;
  *((u8 *) ((*((u8 **) ((base + 4) + 0x2C))) + 1)) = temp2;
  *((u8 *) ((*((u8 **) ((base + 4) + 0x2C))) + 2)) = 2;
  *((u8 *) ((*((u8 **) ((base + 4) + 0x2C))) + 3)) = 8;
  *((u16 *) ((*((u8 **) (p + 0x2C))) + 4)) = *((u8 *) (cbase + 0x304));
  new_var2 = (*((u8 **) (p + 0x2C))) + 6;
  *((u16 *) ((*((u8 **) (p + 0x2C))) + 8)) = 4;
  *((u16 *) new_var2) = 4;
  *((u16 *) ((*((u8 **) (p + 0x2C))) + 0xA)) = 0;
  *((u16 *) ((*((u8 **) (p + 0x2C))) + 0xC)) = 0;
  *((u16 *) ((*((u8 **) (p + 0x2C))) + 0xE)) = scalePercentSaturate16(*((u16 *) (cbase + 0x2E2)), 0x47);
  *((u16 *) ((*((u8 **) (p + 0x2C))) + 0x16)) = 0x0F;
  *((u16 *) ((*((u8 **) (p + 0x2C))) + 0x18)) = 0x65;
  arg0 = p;
  arg0 = arg0 + 0x44;
  *((void **) ((*((u8 **) (p + 0x2C))) + 0x10)) = a;
  *((void **) (p + 0x18)) = *((void **) (((u8 *) arg0) + 0x24));
  *((void **) (((u8 *) arg0) + 0x24)) = (void *) 0x0808449D;
  new_var = 0x80;
  *((void **) (a + 0x24)) = (void *) 0x084E8090;
  startEffectTimer(base + 0x20, 0, (void *) 0x084E80F0);
  *((s32 *) (base + 4)) = *((s32 *) (((u8 *) arg0) + 0x7C));
  *((s32 *) (p + 4)) = (*((s32 *) (((u8 *) arg0) + 0x8C))) + ((s32) 0xFFFE0000);
  if ((*((s32 *) (base + 4))) > ((s32) D_02027718))
  {
    *((u16 *) (a + 2)) = (*((u16 *) (a + 2))) | 0x10;
    *((s32 *) (base + 4)) += (s32) 0xFFF60000;
  }
  else
  {
    *((u16 *) (a + 2)) = (*((u16 *) (a + 2))) & 0xFFEF;
    temp2 = (*((s32 *) (base + 4))); *((s32 *) (base + 4)) = temp2 + 0xA0000;
  }
  *((s32 *) (p + 0x40)) = 0x40000;
  *((u8 *) (p + 0x44)) = (u8) (((0 - ((*((u16 *) (a + 2))) & 0x10)) >> 31) & new_var);
  *((u8 *) (p + 0x45)) = 1;
  setDirectionVector(pcopy, *((u8 *) arg0));
  {
    void *r = sub_08016A2C();
    if (r == 0)
    {
      *((s32 *) (p + 0x48)) = 0x101;
    }
    else
    {
      if (1)
      {
        *((s32 *) (p + 0x48)) = 0;
      }
      if (arg0)
      {
        *((void **) (p + 0x4C)) = r;
        new_var3 = *((u8 *) (((u8 *) r) + 1));
        *((u8 *) (p + 0x50)) = new_var3;
      }
      else
      {
        *((void **) (p + 0x4C)) = r;
        new_var3 = *((u8 *) (((u8 *) r) + 1));
        *((u8 *) (p + 0x50)) = new_var3;
      }
    }
  }
  *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) = 0;
  new_var2 = (u32 *) gMainObjTimerCallbacks;
  {
    u8 *p18 = ((u8 *) arg0) + 0x18;
    u32 *wp = new_var2;
    new_var = 2;
    sub_080C31E4(p18, ((u8 *) arg0) + 0x22, *wp);
    {
      u8 *q = (u8 *) ((((u32) ((*((s16 *) (((u8 *) arg0) + 0x22))) * new_var)) + ((u32) arg0)) + 0x19);
      *q = (u8) ((*q) + 1);
      q = p18 + ((*((s16 *) (((u8 *) arg0) + 0x22))) * new_var);
      {
        void *tbl;
        new_var3 = *q;
        tbl = *((void **) (((u8 *) arg0) + 0x14));
        sub_080C31E0(arg0, *((void **) (((u8 *) tbl) + (new_var3 * 4))));
      }
    }
  }
}

