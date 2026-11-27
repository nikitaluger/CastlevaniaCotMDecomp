extern s32 stepDelayTimer(void *arg0, void *arg1);
extern s32 setEntityForm(void *arg0, void *arg1, s32 arg2);
extern void sub_0806A884(void *arg0, void *arg1);
extern s32 syncViewPosition(void *arg0, void *arg1);
extern void resetActionResultState(void *arg0, void *arg1, void *arg2, void *arg3);
extern void sub_0806C6B0(void *arg0, void *arg1, void *arg2, void *arg3);
extern u32 sub_0806BCD8(void *arg0, void *arg1, void *arg2, void *arg3);
extern void sub_080C31E4(void *arg0, void *arg1, s32 arg2);
extern void sub_080C31E8(void *arg0, void *arg1, s32 arg2, void *arg3);
extern u8 D_080E03A0[];
extern void *gScriptStepCallbackTable;
extern void *gMenuScriptCallback;
void sub_080653B0(u8 *arg0)
{
  u8 *r7;
  u8 *r8;
  int new_var;
  u8 *r6;
  u8 *r5;
  r7 = *((u8 **) (arg0 + 0x6C));
  r8 = r7 + 4;
  r6 = *((u8 **) (arg0 + 0x38));
  r5 = r8;
  if (syncViewPosition(r8, r5) == 0)
  {
    s32 tr;
    u8 *r7p;
    resetActionResultState(arg0, r6, r5, r5);
    sub_0806A884(r6, r5);
    r7p = r7 + 0x2C;
    tr = stepDelayTimer(r7p, r6);
    if (tr == 0)
    {
      s32 idx;
      u8 *base;
      s32 val;
      void **pd;
      setEntityForm(r6, r5, 0x1C);
      stepDelayTimer(r7p, r6);
      base = D_080E03A0;
      idx = *((s32 *) (r5 + 0x44));
      new_var = idx * 0x58;
      {
        u8 *p = base + 0x20;
        val = *((s32 *) (p + new_var));
      }
      if ((*((u16 *) (r6 + 2))) & 0x10)
      {
        val = -val;
      }
      *((s32 *) (r5 + 8)) = val;
      *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19)) = (u8) tr;
      pd = &gScriptStepCallbackTable;
      sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *pd);
    }
    {
      u32 res;
      u8 *r7p2;
      res = sub_0806BCD8(arg0, r6, r8, r5);
      r7p2 = r8 + 0xC4;
      *((u32 *) r7p2) = (u16) res;
      if ((u16) res != 0)
      {
        void **pd2;
        stepDelayTimer(r8 + 0x28, r6);
        *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x17)) = 0;
        pd2 = &gMenuScriptCallback;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, *((u32 *) (r8 + 0xC4)), *pd2);
      }
    }
    sub_0806C6B0(arg0, r6, r8, r5);
  }
}
