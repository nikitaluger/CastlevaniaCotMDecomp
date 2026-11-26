struct Sub08013B5C_28
{
  u8 unk0;
  u8 unk1;
};
struct Sub08013B5C
{
  u16 unk0;
  u8 pad2[0x1A];
  s16 unk1C;
  s16 unk1E;
  u8 pad20[8];
  struct Sub08013B5C_28 *unk28;
};
struct S_02025FF0_189C
{
  u8 _0[0x189C];
  u32 field189C;
};
extern struct S_02025FF0_189C gMainWorkspace;
s32 sub_08014090(s16);
void sub_08013FAC(struct Sub08013B5C *);
void sub_08014060(struct Sub08013B5C *);

/* Apply an object's display state to its sprite attributes: set the priority
 * or hidden top bits for a timed state, clear the sprite flag, drive the
 * state's countdown, and report whether the frame was handled so the caller
 * can skip its normal script step. */
s32 sub_08013B5C(u16 *spriteAttrs, struct Sub08013B5C *state)
{
  u16 stateFlags;
  stateFlags = state->unk0;
  if (!(stateFlags & 1))
  {
    if (stateFlags & 0xC)
    {
      u32 bit4;
      bit4 = 4;
      bit4 &= state->unk0;
      if (bit4)
      {
        if ((state->unk1E > 0x3C) || (!(gMainWorkspace.field189C & 2)))
        {
          *spriteAttrs = ((*spriteAttrs) & 0x0FFF) | 0xD000;
        }
      }
      else
      {
        if ((state->unk1E > 0x3C) || (!(gMainWorkspace.field189C & 2)))
        {
          *spriteAttrs = ((*spriteAttrs) & 0x0FFF) | 0xC000;
        }
      }
      if (state->unk28 != NULL)
      {
        state->unk28->unk1 &= 0xFE;
      }
    }
    if (sub_08014090(state->unk1C) == 1)
    {
      return 1;
    }
    if (state->unk0 & 0xC)
    {
      if (state->unk0 & 4)
      {
        sub_08013FAC(state);
      }
      else
      {
        sub_08014060(state);
      }
      return 1;
    }
    return 0;
  }
  return 0;
}
