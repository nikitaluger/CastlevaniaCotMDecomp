/* Refreshes an entity's animation and facing, then (when the global mode word
 * is active and the entity is near the player or flagged) clears the script's
 * action byte and advances to step 3. */
struct S_02025FF0
{
  u8 _0x000[0x3C];
  u16 modeWord;
};
extern struct S_02025FF0 gMainWorkspace;
void sub_080B37E0(void *arg0)
{
  u8 *self = (u8 *) arg0;
  s32 scriptTable;
  u8 *sprite = (u8 *) (*((u32 *) (self + 0x38)));
  u8 *work = (u8 *) (*((u32 *) (self + 0x3C)));
  u8 *animState = work + 0x34;
  setObjectAnimation(sprite, animState, 0, 1);
  advanceAnimTrack(sprite, animState);
  sub_080148D8(sprite, *((u32 *) (work + 0x08)));
  if ((gMainWorkspace.modeWord != 0) && ((sub_0801459C(work, 0x600000) != 0) || ((*((u16 *) work)) & 0x02)))
  {
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
    scriptTable = 0x08671BD0;
    sub_080C31E8(self + 0x18, self + 0x22, 3, *((s32 *) scriptTable));
  }
}
