extern void sub_08001480(void *, int);
extern void sub_08001738(s32);
extern void sub_08006234(void);
extern void sub_0808BB54(void);
extern u8 sub_0808CB58(void);
extern void sub_080C31E4(void *, void *, u32);
extern u8 D_02025368[];
extern u8 D_02025FF0[];
/* Sound-command slots in IWRAM. */
struct SoundCmd { u8 _pad[4]; u16 id; u16 mode; u16 counter; };
extern struct SoundCmd D_03000830;
static inline u32 decrementCounter(s32 dummy, struct SoundCmd *p) {
  u32 v = p->counter;
  v -= 2;
  p->counter = v;
  return v;
}
/*
 * Advances the main object: updates the global object trees, handles a pending
 * scene/sound state change, then dispatches the object's step script.
 */
void sub_08006E0C(void *obj)
{
  u8 *objPtr;
  u8 *gameState;
  u8 *state;
  u32 sh;
  u32 stateWord;
  u32 stateWordAddr;
  s32 *sp;
  u8 *flagPtr;
  u8 inputCode;
  u8 *inputFlagPtr;
  s16 stepIndex;
  u8 *addr;
  u32 *pB0;
  objPtr = (u8 *) obj;
  gameState = D_02025368;
  state = D_02025FF0;
  sub_08001738(*((s32 *) (state + 0x1854)));
  sub_08001738(*((s32 *) (state + 0x1860)));
  sp = (s32 *) (state + 0x1894);
  *sp += 1;
  sub_08001738(*((s32 *) (state + 0x1888)));
  if ((*((u32 *) (state + 0x14C0)) & 0x40000000) == 0)
  {
    sh = decrementCounter(0, &D_03000830);
    sh = sh << 16;
    if (sh != 0) goto L6F04;
  }
  stateWord = *((u32 *) (state + 0x14C0));
  if (stateWord == 0)
  {
    D_03000830.id = *((u16 *) (state + 0x176A));
    D_03000830.mode = *((u16 *) (state + 0x176C));
    D_03000830.counter = *((u16 *) (state + 0x176E));
  }
  else
  {
    u16 *d = (u16 *) (gameState + 0x94);
    if ((*d) == 0x0200) sub_0808BB54();
  }
  L6EAE:
  {
    u32 r1 = (u32) D_02025FF0;
    stateWordAddr = r1 + 0x14C0;
    *((u32 *) stateWordAddr) = 0;
    flagPtr = (u8 *) (r1 + 0x18C4);
  }
  if ((*flagPtr) == 0xFF)
  {
    sub_08006234();
    *flagPtr = 0;
  }
  inputCode = sub_0808CB58();
  inputFlagPtr = gameState + 0x9B;
  inputFlagPtr = inputFlagPtr + inputCode;
  if ((*inputFlagPtr) == 0)
  {
    *inputFlagPtr = 1;
    sub_08001480(objPtr, 0x13);
  }
  stepIndex = *((s16 *) (objPtr + 0x22));
  addr = (u8 *)((stepIndex * 2) + (u32)objPtr) + 0x19;
  *addr = 0;
  pB0 = (u32 *) 0x08671BB0;
  sub_080C31E4(objPtr + 0x18, objPtr + 0x22, *pB0);
  L6F04:
  return;
}
