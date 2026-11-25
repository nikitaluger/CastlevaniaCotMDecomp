static inline u8 zero8(void) { return 0; }

/* Configures an animation state from a 4-byte frame descriptor: copies the
 * frame word and mode into the state, forwards the second word to the owner
 * object, and flags an empty frame. */
void sub_08010D50(void *obj, void *anim, void *frameDesc, u8 mode)
{
  u32 frameWord = *((u16 *) frameDesc);
  u8 modeBits = mode;
  u32 zero = 0;
  char *descPtr;
  char *animPtr;
  *((u16 *) (((char *) anim) + 2)) = (u16)frameWord;
  *((u32 *) (((char *) anim) + 4)) = zero;
  *((u8 *) (((char *) anim) + 1)) = 1;
  *((u8 *) anim) = modeBits;
  *((u16 *) (((char *) obj) + 0x28)) = *((u16 *) ((descPtr = (char *) frameDesc) + 2));
  frameWord <<= 16;
  if (frameWord == 0)
  {
    *((u8 *) ((animPtr = (char *) anim) + 1)) = zero8();
    *((u8 *) anim) = (u8) (modeBits | 2);
  }
}
