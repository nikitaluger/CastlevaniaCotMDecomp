extern u8 D_02025358[];
extern u8 gMainWorkspace[];
extern void (*gScriptStepCallbacks)(void *, void *, s32);
extern void stepDelayTimer(void *, s32);
extern void setEntityForm(void *, void *, s32);
extern s32 syncViewPosition(void *, void *);
extern void sub_0808B584(void *);
void sub_08062A90(void *arg0)
{
  int new_var2;
  u8 *g1;
  u8 *a;
  u8 *r4;
  u8 *r6;
  u8 *r8v;
  u8 *r5;
  u8 *sbv;
  s32 cnt;
  u8 *new_var;
  u8 *r6n;
  u8 *r8n;
  u8 *r3b;
  u8 *r1b;
  s16 idx;
  u8 *p;
  a = (u8 *) arg0;
  r4 = *((u8 **) (a + 0x6C));
  r6 = r4 + 4;
  do { r8v = *((u8 **) (a + 0x38)); } while (0);
  r5 = r6;
  sbv = D_02025358;
  *((s32 *) (r5 + 0x08)) = 0;
  *((s32 *) (r5 + 0x0C)) = 0;
  *((s32 *) (r5 + 0x64)) = 0x11;
  r6n = r5 + 0x60;
  *((s32 *) (r5 + 0x68)) = 1;
  *((s32 *) r6n) = 0;
  *((s32 *) (r5 + 0x4C)) = 0;
  new_var2 = 0x54;
  *((s32 *) (r5 + 0x50)) = 0;
  *((s32 *) (r5 + new_var2)) = 0;
  *((s32 *) (r4 + 0x88)) = 0;
  *((s32 *) (r5 + 0x70)) = 0;
  *((s32 *) (r5 + 0x74)) = 0;
  *((s32 *) (r4 + 0x8C)) = 0;
  *((s32 *) (r4 + 0x90)) = 0;
  *((s32 *) (r4 + 0x94)) = 0;
  *((s32 *) (r5 + 0x78)) = 0;
  *((s32 *) (r5 + 0x7C)) = 0;
  *((s32 *) (r4 + 0x84)) = 0;
  *((s32 *) (r5 + 0x58)) = 0;
  *((s32 *) (r5 + 0x5C)) = 0;
  *((s32 *) (r4 + 0x128)) = 0;
  *((s32 *) (r5 + 0x40)) = 1;
  *((s32 *) (r5 + 0x48)) = 0;
  *((s32 *) (r5 + 0x44)) = 0;
  *((s32 *) (r4 + 0xC4)) = 0;
  *((s32 *) (r4 + 0xCC)) = 0;
  g1 = gMainWorkspace;
  *((s32 *) (g1 + 0x1754)) = 0;
  *((u16 *) (g1 + 0x1506)) = 0;
  *((u16 *) (g1 + 0x1504)) = 0;
  *((u8 *) (g1 + 0x14ED)) = 0;
  *((s32 *) (g1 + 0x1818)) = 0;
  *((s32 *) (g1 + 0x181C)) = 0;
  *((u16 *) (g1 + 0x18BC)) = 0;
  p = r4 + 0xD4;
  cnt = 3;
  do
  {
 do { *((s32 *) p) = 0; *((s32 *) (p + 0x10)) = 0; } while (0);
    *((s32 *) (p + 0x20)) = 0;
    p += 4;
    cnt--;
  }
  while (cnt >= 0);
  setEntityForm(r8v, r6, 0);
  stepDelayTimer(r6 + 0x28, (s32) r8v);
  r4 = gMainWorkspace;
  new_var = r4;
  *((u32 *) (new_var + 0x1844)) |= 0x04000000;
  syncViewPosition(r6, r5);
  r6n = a + 0x18;
  r8n = a + 0x22;
  r3b = new_var + 0x1618;
  r1b = r4 + 0x1518;
  cnt = 0x3F;
  do
  {
    *((u32 *) r1b) = *((u32 *) r5);
    r1b += 4;
    *((u32 *) r3b) = *((u32 *) (r5 + 4));
    r3b += 4;
    cnt--;
  }
  while (cnt >= 0);
  *((s32 *) (r4 + 0x1718)) = 0;
  if (sbv[0x0C] != 0)
  {
    sub_0808B584(r5);
  }
  idx = *((s16 *) (a + 0x22));
  *((u8 *) ((((u32) a) + (idx * 2)) + 0x19)) = 0;
  gScriptStepCallbacks((void *) r6n, (void *) r8n, 4);
}
