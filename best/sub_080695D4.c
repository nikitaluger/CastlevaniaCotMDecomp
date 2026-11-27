extern void playSound(s32);
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u8 D_080E068C[];
extern u8 *D_0866EB08[];
extern u32 gMainObjTimerCallbacks;
inline u8 inline_fn(u8 *arg0) { return *arg0; }
void sub_080695D4(u8 *arg0)
{
  u8 *sp0;
  void *r10;
  u8 *p94;
  u8 *p95;
  u8 *p96_1;
  u8 *p96_2;
  u8 *t5;
  s32 i;
  volatile char new_var2;
  u8 *new_var;
  s32 j;
  u8 *p18;
  u8 *p22;
  u8 temp;
  sp0 = (*((u8 **) (arg0 + 0x6C))) + 4;
  r10 = *((void **) (arg0 + 0x38));
  if (syncViewPosition(sp0, sp0) != 0) return;
  resetActionResultState(arg0, r10, sp0, sp0);
  p94 = gGameStatus + 0x94;
  p95 = gGameStatus + 0x95;
  p18 = arg0 + 0x18;
  p22 = arg0 + 0x22;
  t5 = (u8 *)(D_0866EB08[inline_fn(p94)] + inline_fn(p95) * 2);
  gMainWorkspace[0x14C6] = inline_fn(t5);
  gMainWorkspace[0x14C7] = inline_fn(t5 + 1);
  i = 0;
  if (D_080E068C[0] != *p94 || D_080E068C[1] != *p95) {
    do {
      i++;
      if (i > 4) i = 0;
    } while (D_080E068C[i * 4] != *p94 || D_080E068C[i * 4 + 1] != *p95);
  }
  j = i + 1;
  if (j > 4) j = 0;
  p96_1 = gGameStatus + 0x96;
  temp = p96_1[j];
  new_var = D_080E068C;
  new_var2 = temp == 0;
  if (new_var2) {
    do {
      j++;
      if (j > 4) j = 0;
    } while (p96_1[j] == 0);
  }
  p96_2 = gMainWorkspace;
  i = j;
  *p94 = D_080E068C[i * 4];
  *p95 = new_var[i * 4 + 1];
  t5 = (u8 *)(D_0866EB08[inline_fn(p94)] + inline_fn(p95) * 2);
  gMainWorkspace[0x14C4] = inline_fn(t5);
  gMainWorkspace[0x14C5] = inline_fn(t5 + 1);
  *(u32 *)(p96_2 + 0x14C8) = 0x780000;
  *(u32 *)(p96_2 + 0x14CC) = *(u32 *)(sp0 + 4);
  *(u32 *)(p96_2 + 0x14D0) = 0x780000 - *(u32 *)sp0;
  *(u32 *)(p96_2 + 0x14D4) = 0;
  *(u32 *)(p96_2 + 0x14B4) = 0x222;
  *(u32 *)(p96_2 + 0x1844) |= 0x6000000;
  *(u16 *)(p96_2 + 0x14D8) = 0xFFFE;
  playSound(0x1BA);
  sub_0806C6B0(arg0, r10, ((*((u8 **) (arg0 + 0x6C))) + 4), sp0);
  *(u8 *)(arg0 + *(s16 *)p22 * 2 + 0x19) = 0;
  sub_080C31E4(p18, p22, gMainObjTimerCallbacks);
}
