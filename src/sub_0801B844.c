void sub_080C31E4(void *, void *, void *);
static inline u8 zero_byte(void) { u8 v = 0; return v; }
static inline u16 zero_half(void) { u16 v = 0; return v; }

/* Advance the actor's model animation by 5 frames; if its restart flag is
 * set, clear the two timers and the script level's repeat counter and run
 * the handler at 0x08671BB0. */
void sub_0801B844(void *arg0)
{
  u8 *actor = arg0;
  void **handlerTable;
  u32 model = *((u32 *) (actor + 0x38));
  u8 *anim = *((u8 **) (actor + 0x3C));
  u8 *animFlags = anim + 0x34;
  u8 *timers = anim + 0x48;
  setAnimationFrame(model, anim + 0x34, 5, 0);
  if ((*((u8 *) animFlags)) & 2)
  {
    register u16 zeroH = zero_half();
    register u8 zeroB = zero_byte();
    *((u16 *) (timers + 0x16)) = zeroH;
    *((u16 *) (timers + 0x18)) = zeroH;
    ((u8 *) (actor + ((*((s16 *) (actor + 0x22))) * 2)))[0x19] = zeroB;
    handlerTable = (void **) 0x08671BB0;
    sub_080C31E4(actor + 0x18, actor + 0x22, *handlerTable);
  }
}
