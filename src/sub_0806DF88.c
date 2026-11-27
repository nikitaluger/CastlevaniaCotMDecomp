extern s32 stepDelayTimer(void *, void *);
extern s32 startEffectTimer(void *, s32, void *);
extern void sub_0806E154(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern u8 D_080E01A0[];
extern void *gScriptStepCallbackTable;
struct P38 { u8 _0[4]; u16 f4; u16 f6; u16 f8; };

/*
 * Applies an effect configuration to a spawned entity: copies the table entry
 * selected by the entity's id into its context/state, installs the effect
 * callback, starts the timer, then fires the entity's effect and callback.
 */
void sub_0806DF88(u8 *arg0)
{
  u8 *subObj;
  u8 *obj;
  u8 *ctx;
  u8 *config;
  u32 idx;
  u8 *base18;
  void **effectIds;
  s16 index;
  s32 zero;
  subObj = *((u8 **) (arg0 + 0x6C));
  obj = subObj + 4;
  ctx = *((u8 **) (arg0 + 0x38));
  idx = (*((u32 *) (arg0 + 0x7C))) & 0xFFFF;
  config = D_080E01A0 + (idx << 5);
  *((u32 *) (ctx + 0x1C)) = *((u32 *) (config + 0x1C));
  *((u32 *) (obj + 0x18)) = *((u32 *) (arg0 + 0x24));
  *((void **) (arg0 + 0x24)) = &sub_0806E154;
  *((u32 *) (subObj + 4)) = *((u32 *) (arg0 + 0x8C));
  *((u32 *) (obj + 4)) = *((u32 *) (arg0 + 0x9C));
  *((u32 *) (ctx + 0x24)) = *((u32 *) (config + 0x0C));
  startEffectTimer(subObj + 0x24, 0, *((void **) (config + 0x10)));
  stepDelayTimer(subObj + 0x24, ctx);
  *((u32 *) (obj + 0x10)) = *((u32 *) (config + 0x14));
  ((struct P38 *)ctx)->f4 = 0x100;
  ((struct P38 *)ctx)->f6 = 0x100;
  ((struct P38 *)ctx)->f8 = 0;
  zero = 0;
  index = *((s16 *) (arg0 + 0x22));
  *((u8 *) ((arg0 + (index * 2)) + 0x19)) = zero;
  effectIds = &gScriptStepCallbackTable;
  base18 = arg0 + 0x18;
  sub_080C31E4(base18, arg0 + 0x22, *effectIds);
  index = *((s16 *) (arg0 + 0x22));
  *((u8 *) ((arg0 + (index * 2)) + 0x19)) += 1;
  index = *((s16 *) (arg0 + 0x22));
  base18 = base18 + (index * 2);
  sub_080C31E0(arg0, *((void **) ((*((u8 **) (arg0 + 0x14))) + ((*((u8 *) base18)) * 4))));
}
