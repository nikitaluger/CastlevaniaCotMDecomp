extern s32 nextRandomWord(void);
extern void setObjectAnimation(s32, s32, s32, s32);
extern s32 sub_0801459C(void *, s32);
extern void sub_080148D8(s32, s32);
extern void sub_080A17B0(s32, s32, void *);
extern s32 sub_080A17DC(s32, void *, s32, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 gScriptStepCallbacks[];
extern u32 gMenuScriptCallback[];

void sub_080A0FB0(void *arg0)
{
  s32 *var_r2;
  s32 temp_r0_2;
  s32 temp_r1;
  s32 temp_r7;
  s8 temp_r5_2;
  void *temp_r5;
  u8 *a;
  s32 idx, idx2, idx3, idx5;
  void *p8;
  s16 h;
  u8 b;
  s32 idx4;
  u32 base;
  u8 *off;
  u16 v;
  u8 zero;
  s32 tp34;
  void *tp48;
  u32 *pbd0g;
  u32 *pbd0e;

  a = (u8 *)arg0;
  temp_r7 = *((s32 *)(a + 0x38));
  temp_r5 = *((void **)(a + 0x3C));
  tp34 = ((s32)temp_r5) + 0x34;
  tp48 = (void *)(((u8 *)temp_r5) + 0x48);
  temp_r0_2 = *((s32 *)(a + 0x04));
  if (temp_r0_2 != 0) { *((s32 *)(a + 0x04)) = temp_r0_2 - 1; }
  if (sub_080A17DC(temp_r7, temp_r5, tp34, tp48, 0x6000) != 0)
  {
    temp_r1 = *((s32 *)(a + 0x04));
    if (temp_r1 == 0)
    {
      idx = *((s16 *)(a + 0x22));
      (((u8 *)a) + (idx * 2))[0x17] = (s8)temp_r1;
      var_r2 = (s32 *)gMenuScriptCallback;
      goto block_9;
    }
    if (sub_0801459C(temp_r5, 0x380000) != 0)
    {
      sub_080148D8(temp_r7, *((s32 *)((u8 *)temp_r5 + 8)));
      temp_r5_2 = (s8)(nextRandomWord() & 3);
      if (temp_r5_2 != 0)
      {
        setObjectAnimation(temp_r7, tp34, 0x0E, 0);
        p8 = *((void **)((u8 *)tp34 + 0x08));
        h = *((s16 *)((u8 *)tp34 + 0x0E));
        b = *((u8 *)tp34 + 0x01);
        idx4 = h + b;
        base = *((u32 *)p8);
        off = (u8 *)((idx4 * 4) + base - 4);
        v = *((u16 *)(off + 2));
        zero = 0;
        *((u16 *)((u8 *)tp48 + 0x14)) = v;
        idx2 = *((s16 *)(a + 0x22));
        (((u8 *)a) + (idx2 * 2))[0x19] = zero;
        pbd0g = gScriptStepCallbacks;
        sub_080C31E8(((u8 *)a) + 0x18, ((u8 *)a) + 0x22, 2, *pbd0g);
        return;
      }
      sub_080A17B0(temp_r7, tp34, tp48);
      idx3 = *((s16 *)(a + 0x22));
      (((u8 *)a) + (idx3 * 2))[0x19] = (u8)temp_r5_2;
      var_r2 = (s32 *)gScriptStepCallbacks;
      block_9:
      sub_080C31E8(((u8 *)a) + 0x18, ((u8 *)a) + 0x22, 3, *var_r2);
      return;
    }
  }
  if (*((u8 *)tp48 + 0x17) == 2)
  {
    sub_080148D8(temp_r7, *((s32 *)((u8 *)temp_r5 + 8)));
    sub_080A17B0(temp_r7, tp34, tp48);
    idx5 = *((s16 *)(a + 0x22));
    (((u8 *)a) + (idx5 * 2))[0x19] = 0;
    pbd0e = gScriptStepCallbacks;
    sub_080C31E8(((u8 *)a) + 0x18, ((u8 *)a) + 0x22, 3, *pbd0e);
  }
}
