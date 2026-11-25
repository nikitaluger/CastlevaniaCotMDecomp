/* Advance a scripted effect: run the current script opcode, shift the
 * position-history trails and record the new position, then copy trail
 * positions into the linked follow objects. */
unsigned int sub_080C31E0(void *, s32);
extern s32 D_0866D9D4[];

void sub_08027234(void *arg0)
{
  u8 *effect = arg0;
  u8 *fxState;
  u8 *state48;
  s32 scriptTable;
  s32 offset;
  u8 *stepPtr;
  u8 opcode;
  s32 i;
  u8 *xTrail;
  u8 *yTrail;
  u8 *cursor;
  s32 remaining;
  s32 position;
  u8 *linked;
  u16 *yTrail2;

  fxState = *((u8 **) (effect + 0x3C));
  state48 = fxState + 0x48;
  *((s32 *) (effect + 0x14)) = (s32) D_0866D9D4;
  *((u16 *) (effect + 0x22)) = (*((u16 *) (effect + 0x22))) + 1;
  offset = *((s16 *) (effect + 0x22));
  offset = offset << 1;
  offset = offset + (u32) effect;
  *((u8 *) (offset + 0x19)) = (*((u8 *) (offset + 0x19))) + 1;
  offset = (*((s16 *) (effect + 0x22))) << 1;
  stepPtr = effect + 0x18;
  stepPtr += offset;
  opcode = *stepPtr;
  scriptTable = *((s32 *) (effect + 0x14));
  sub_080C31E0(effect, *((s32 *) ((opcode << 2) + scriptTable)));
  *((u16 *) (effect + 0x22)) = (*((u16 *) (effect + 0x22))) - 1;
  i = 4;
  xTrail = fxState + 0x5C;
  yTrail = fxState + 0x66;
  cursor = fxState + 0x62;
  do
  {
    remaining = i - 1;
    *((u16 *) (cursor + 2)) = *((u16 *) (cursor + 0));
    *((u16 *) (cursor + 0xC)) = *((u16 *) (cursor + 0xA));
    cursor -= 2;
    i = remaining;
  }
  while (remaining > 0);
  offset = remaining << 1;
  {
    u8 *xSlot = xTrail + offset;
    position = *((s32 *) (fxState + 0x08));
    if (position < 0)
    {
      position += 0xFFFF;
    }
    *((u16 *) xSlot) = (u16) (position >> 16);
  }
  {
    u8 *ySlot = yTrail + offset;
    position = *((s32 *) (fxState + 0x0C));
    if (position < 0)
    {
      position += 0xFFFF;
    }
    *((u16 *) ySlot) = (u16) (position >> 16);
  }
  linked = *((u8 **) (effect + 0x30));
  yTrail2 = (u16 *) (state48 + 0x22);
  if (linked != 0)
  {
    {
      u16 xVal = *((u16 *) (state48 + 0x18));
      u8 *destX = linked + 0x4C;
      *((u16 *) destX) = xVal;
      {
        u16 yVal = *yTrail2;
        u8 *destY = destX + 8;
        *((u16 *) destY) = yVal;
      }
    }
    linked = *((u8 **) (linked + 0x30));
    if (linked != 0)
    {
      u16 nextX = *((u16 *) (state48 + 0x1C));
      u8 *nextDestX = linked + 0x4C;
      *((u16 *) nextDestX) = nextX;
      {
        u16 nextY = *((u16 *) (state48 + 0x26));
        u8 *nextDestY = nextDestX + 8;
        *((u16 *) nextDestY) = nextY;
      }
    }
  }
}
