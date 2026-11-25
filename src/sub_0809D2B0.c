void sub_08005E80(s32);
void sub_08014588(void *, s32);
void sub_0809E300(void *, void *, void *);
void sub_080A0340(s32, s32);
void sub_080C31E4(void *, void *, s32);

struct GfxScale { u8 _pad[4]; u16 scale; };

/* Enemy actor step: mark the work state, set sprite flags and scale, copy
 * animation parameters from a table, apply a target status and animation
 * frame, load resource 0x187, then clear the script byte and dispatch. */
void sub_0809D2B0(void *actor)
{
  u8 *self = (u8 *) actor;
  u8 *gfx = *((u8 **) (self + 0x38));
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *anim = work + 0x34;
  u8 *state = work + 0x48;
  u8 *flagByte;
  s32 flagsWithBit;
  int zero;

  *((u8 *) (work + 0x89)) = 1;
  flagByte = (u8 *)(gfx + 0x2A);
  flagsWithBit = 0x40 | *flagByte;
  *flagByte = (u8)flagsWithBit;
  zero = 0;
  ((struct GfxScale *)gfx)->scale = 0x900;
  *((u16 *) (gfx + 6)) = 0x80;
  *((u8 *) (*((u8 **) (work + 0x28)) + 1)) = zero;
  sub_08014588(*((void **) (work + 0x28)), 0x081019A4);
  sub_080A0340(*((s32 *) (state + 0x20)), 1);
  sub_0809E300(gfx, anim, state);
  sub_08005E80(0x187);
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = zero;
  {
    s32 *handlerTable = (s32 *) 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
  }
}
