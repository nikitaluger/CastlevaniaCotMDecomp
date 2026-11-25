struct GlobalState { u8 _pad[0x0C]; s32 field_0xC; };
void sub_080035E4(s32);
void sub_080158F4(void);
void sub_08016160(void);
void sub_08016530(void);
void sub_080C31E4(void *, void *, s32);
extern s32 D_08671BB0;
static inline u8 zero8(void) { u8 v = 0; return v; }
static inline u16 zero16(void) { u16 v = 0; return v; }

/* Reset global work/gfx state, then restart this actor's current action script. */
void sub_08006920(void *actor)
{
  void *self = actor;
  s32 *worldState = (s32 *) 0x02021E90;
  register u8 wordZero;
  register u16 byteZero;
  s32 dmaFillWord;
  volatile s32 *dma3;
  *((s32 *) (((s8 *) worldState) + 0x125C)) = -1;
  wordZero = zero8();
  dmaFillWord = wordZero;
  dma3 = (volatile s32 *) 0x040000D4;
  dma3[0] = (s32) (&dmaFillWord);
  dma3[1] = (s32) (((s8 *) worldState) + (0x93 << 5));
  dma3[2] = 0x85000040;
  sub_080035E4(dma3[2]);
  {
    u16 *gfxState = (u16 *) 0x03000830;
    byteZero = zero16();
    gfxState[2] = 0x00FF;
    gfxState[4] = 0x0010;
    sub_08016160();
    sub_080158F4();
    sub_08016530();
    ((struct GlobalState *) 0x02025FF0)->field_0xC = wordZero;
    {
      s32 actionIndex = *((s16 *) (((s8 *) self) + 0x22));
      *((u8 *) ((((s8 *) self) + (actionIndex * 2)) + 0x19)) = byteZero;
    }
  }
  {
    s32 *scriptTable = (s32 *) 0x08671BB0;
    void *actionList = ((s8 *) self) + 0x18;
    void *indexPtr = ((s8 *) self) + 0x22;
    sub_080C31E4(actionList, indexPtr, *scriptTable);
  }
}
