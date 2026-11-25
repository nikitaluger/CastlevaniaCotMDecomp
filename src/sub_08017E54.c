void sub_08011368(s32, s32, s32, s32);
void sub_080C31E4(void *, void *, s32);
static inline u8 zero_b(void) { u8 v = 0; return v; }
static inline u16 zero_h(void) { u16 v = 0; return v; }

/* Script command: play animation 5 on the actor's sprite and set its vertical
 * velocity to 0xFFFFA000; when the animator's flag bit 2 is set, clear the two
 * attack counters and the current step flag, then advance the script. */
void sub_08017E54(void *actor) {
  u8 *self = actor;
  void **scriptTable;
  u32 sprite = *((u32 *) (self + 0x38));
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *animator = work + 0x34;
  u8 *attack = work + 0x48;
  sub_08011368(sprite, work + 0x34, 5, 0);
  *((u32 *) (work + 0x14)) = 0xFFFFA000;
  if ((*((u8 *) animator)) & 2) {
    register u16 zeroHalf = zero_h();
    register u8 zeroByte = zero_b();
    *((u16 *) (attack + 0x16)) = zeroHalf;
    *((u16 *) (attack + 0x18)) = zeroHalf;
    ((u8 *) (self + ((*((s16 *) (self + 0x22))) * 2)))[0x19] = zeroByte;
    scriptTable = (void **) 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
  }
}
