extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern s32 D_080DFF9C[];
extern s32 D_080DFFB0[];
extern u32 gScriptStepCallbacks;
s32 sub_08084500(void *a, void *b, void *c, void *d);
void sub_080C31E8(void *a, void *b, s32 c, u32 d);
void *sub_0806D24C(s32 arg0, s32 arg1, u32 arg2, s32 arg3);
void sub_08084AD0(void *a);
void setEntityForm(void *a, void *b, s32 c);
void sub_08085440(void *a, void *b, void *c, s32 d);
s32 sub_0806B3E8(void *a, void *b, void *c, void *d)
{
  u8 *new_var;
  u8 *r5 = a;
  int new_var4;
  void *r10 = b;
  u8 *r6 = (u8 *) c;
  u8 *new_var5;
  u8 *new_var3;
  s32 new_var2;
  u8 *r9 = gGameStatus;
  int temp;
  if ((*((u32 *) (r6 + 0x9C))) != 4)
  {
    u8 *p25 = gMainWorkspace;
    if ((*((u32 *) (p25 + 0x24))) != 0)
    {
      if (((*((u16 *) (p25 + 0x28))) & (*((u16 *) (r9 + 0x3BC)))) == 0)
      {
        if (new_var)
        {
          goto ret0;
        }
        else
        {
          goto ret0;
        }
      }
    }
    else
    {
      u8 *p21 = gCameraState;
      temp = (*((u16 *) (p21 + 0x146C))) & (*((u16 *) (r9 + 0x3BC)));
      if (new_var2 = temp == 0)
      {
        goto ret0;
      }
    }
    *((u32 *) (r6 + 0xC4)) = (new_var2 = (u16) sub_08084500(r5, r10, r6, (void *) d));
    if (new_var2 != 0)
    {
      s16 idx = *((s16 *) (r5 + 0x22));
      *((u8 *) ((r5 + (idx * 2)) + 0x19)) = 0;
      { u32 *fp = &gScriptStepCallbacks; sub_080C31E8(r5 + 0x18, 0x22 + r5, new_var2, *fp); }
      return 2;
    }
    if ((*((u32 *) (r6 + 0x48))) == 1)
    {
      u8 *r7 = r9 + 0x2D8;
      new_var2 = *r7;
      new_var4 = 1;
      if (new_var2 != 0)
      {
        s32 val = (*((s16 *) (r9 + 0x2D4))) + (*((s32 *) (gMainWorkspace + 0x150C)));
        u8 bval = *r7;
        u32 r4 = ((u32) (bval - new_var4)) * 4;
        s16 s1 = *((s16 *) (r9 + 0x8C));
        u32 off = r4 + ((u32) (((s1 * 4) + s1) * 4));
        if (val >= D_080DFFB0[off >> 2])
        {
          void *res = sub_0806D24C((s32) r5, 0x25, 7, D_080DFF9C[r4 >> 2]);
          if (res != 0)
          {
            *((u16 *) (((u8 *) res) + 0x7C)) = bval;
            *((u16 *) (((u8 *) res) + 0x84)) = new_var2;
            new_var3 = (new_var = r5);
            new_var5 = r6;
            sub_08084AD0(r5);
            setEntityForm(r10, new_var5, 0x18);
            *((u32 *) (((u8 *) d) + 8)) = 0;
            {
              s16 idx = *((s16 *) (new_var3 + 0x22));
              *((u8 *) ((new_var + (idx * 2)) + 0x19)) = 0;
            }
            { u32 *fp = &gScriptStepCallbacks; sub_080C31E8(new_var + 0x18, new_var + 0x22, 0x10, *fp); }
            return 2;
          }
        }
      }
    }
    *((u32 *) (new_var5 + 0x48)) = 0;
    *((u32 *) (new_var5 + 0x70)) = new_var4;
    sub_08085440(new_var, r10, r6, 9);
    *((u32 *) (((u8 *) d) + 8)) = 0;
    {
      u8 *p130 = *((u8 **) (new_var5 + 0x130));
      *((u16 *) (p130 + 0x0E)) = *((u16 *) (r9 + 0x2E0));
      p130 = *((u8 **) (r6 + 0x130));
      *((u16 *) (p130 + 0x16)) = 0x1E;
    }
    {
      s16 idx = *((s16 *) (new_var + 0x22));
      *((u8 *) ((new_var + (idx * 2)) + 0x19)) = 0;
    }
    { u32 *fp = &gScriptStepCallbacks; sub_080C31E8(new_var + 0x18, new_var + 0x22, 9, *fp); }
    return new_var4;
  }
 ret0:
  return 0;
}
