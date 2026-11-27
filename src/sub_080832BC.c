extern void startEffectTimer(void *, s32, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern s32 sub_080C36E4(s32, s32);
extern u32 D_080E5E58[];
extern u32 D_080E5E88[];

/*
 * Initialises an entity's animation state and callback: clears its timers,
 * installs the callbacks and duration tables, then fires its effect and next
 * callback.
 */
void sub_080832BC(u8 *arg0)
{
  u8 *subObj = *((u8 **) (arg0 + 0x6C));
  void **ctxCallbacks;
  u8 *obj = subObj + 4;
  u8 *state;
  u8 *ctx = *((u8 **) (arg0 + 0x38));
  s32 zero = 0;
  u8 *paramPtr;
  u32 *durationTable12;
  u32 *durationTable7;
  *((s32 *) (obj + 0x2C)) = zero;
  *((s32 *) (obj + 0x30)) = zero;
  state = obj;
  *((s32 *) (state + 0x34)) = zero;
  *((s32 *) (state + 0x38)) = zero;
  *((s32 *) (state + 0x3C)) = zero;
  *((void **) (state + 0x18)) = *((void **) (arg0 + 0x24));
  *((void **) (arg0 + 0x24)) = (void *) 0x0808449D;
  *((void **) (ctx + 0x24)) = (void *) 0x084F9458;
  startEffectTimer(subObj + 0x20, 0, (void *) 0x084F9488);
  ctxCallbacks = (void **) (ctx + 0x14);
  durationTable12 = D_080E5E58;
  paramPtr = arg0 + 0x9C;
  *ctxCallbacks = (void *) durationTable12[sub_080C36E4(*((s32 *) paramPtr), 0x0C)];
  durationTable7 = D_080E5E88;
  *((void **) (ctx + 0x18)) = (void *) durationTable7[sub_080C36E4(*((s32 *) paramPtr), 0x07)];
  *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19)) = zero;
  {
    u32 *effectIds = (u32 *) 0x08671BB0;
    u8 *base18 = arg0 + 0x18;
 do { sub_080C31E4(base18, arg0 + 0x22, (void *) (*effectIds)); { s16 index = *((s16 *) (arg0 + 0x22)); (*((u8 *) (((index * 2) + arg0) + 0x19)))++; index = *((s16 *) (arg0 + 0x22)); base18 += index * 2; { u8 callbackIndex = *base18; void **callbackTable = *((void ***) (arg0 + 0x14)); sub_080C31E0(arg0, callbackTable[callbackIndex]); } } } while (0);
  }
}
