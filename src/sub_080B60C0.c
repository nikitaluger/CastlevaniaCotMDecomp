extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void sub_080B74C4(void);
extern void sub_080B74F0(void);
extern void _call_via_r1(void *, s32);
extern void _call_via_r2(void *, void *, s32);
static inline u8 zero8(void) { u8 v = 0; return v; }
static inline u16 zero16(void) { u16 v = 0; return v; }

/* Initialize an actor's work buffers and dispatch its first action-script handler. */
void sub_080B60C0(u8 *self)
{
  void *work = allocSpriteObject();
  register u8 zeroByte;
  register u16 zeroHalf;
  if (work == 0)
  {
    _call_via_r1(self, *((s32 *) (self + 0x24)));
    return;
  }
  *((void **) (self + 0x38)) = work;
  allocWorkSlot(self, 0, 0x48, 0);
  if ((*((void **) (self + 0x3C))) == 0)
  {
    _call_via_r1(self, *((s32 *) (self + 0x24)));
    return;
  }
  {
    u8 *flags = ((u8 *) work) + 0x2A;
    u8 newFlags = *flags & 0xBF;
    zeroByte = zero8();
    *flags = newFlags;
    {
      u8 *state = *((u8 **) (self + 0x3C));
      zeroHalf = zero16();
      *((u16 *) (state + 0x1C)) = 0x66;
      sub_080B74C4();
      sub_080B74F0();
      *((u8 *) (self + 0x4C)) = (u8) zeroHalf;
      *((u32 *) (self + 0x5C)) = 0x20000;
      *((u32 *) (self + 0x6C)) = zeroByte;
      *((u16 *) (self + 0x02)) = (u16) (0x1000 | (*((u16 *) (self + 0x02))));
      *((u8 *) (self + ((*((s16 *) (self + 0x22))) * 2) + 0x19)) = (u8) zeroHalf;
      {
        const u32 *lit = (const u32 *) 0x08671BB0;
        u8 *script = self + 0x18;
        _call_via_r2(script, self + 0x22, *lit);
        *((u8 *) (self + ((*((s16 *) (self + 0x22))) * 2) + 0x19)) += 1;
        script = script + (2 * (*((s16 *) (self + 0x22))));
        _call_via_r1(self, *((u32 *) ((*((u32 *) (self + 0x14))) + ((*((u8 *) script)) * 4))));
      }
    }
  }
}
