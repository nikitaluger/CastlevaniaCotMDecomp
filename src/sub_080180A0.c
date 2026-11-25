void sub_080C31E4(void *, void *, void *);
void sub_080C31E8(void *, void *, void *, void *);
static inline u8 zero_b(void) { u8 v = 0; return v; }
static inline u16 zero_h(void) { u16 v = 0; return v; }
/* Play animation 5 on the parent; if the motion status byte has bit 2 set,
 * clear the animation state, clear the script step byte and advance the script. */
void sub_080180A0(void *arg0)
{
  u8 *script = arg0;
  void **advanceFunc;
  u32 parent = *((u32 *) (script + 0x38));
  u8 *motion = *((u8 **) (script + 0x3C));
  u8 *anim = motion + 0x34;
  u8 *state = motion + 0x48;
  sub_08011368(parent, motion + 0x34, 5, 0);
  if ((*((u8 *) anim)) & 2)
  {
    register u16 zeroHalf = zero_h();
    register u8 zeroByte = zero_b();
    *((u16 *) (state + 0x16)) = zeroHalf;
    *((u16 *) (state + 0x18)) = zeroHalf;
    ((u8 *) (script + ((*((s16 *) (script + 0x22))) * 2)))[0x19] = zeroByte;
    advanceFunc = (void **) 0x08671BB0;
    sub_080C31E4(script + 0x18, script + 0x22, *advanceFunc);
  }
}

void sub_08017D70(void *arg0);
void sub_08017E54(void *arg0);
