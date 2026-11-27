extern u8 gMenuState[];
static inline u8 *levelBase(u8 *b) { return b + 0x6F; }

/* Per-layer reveal step (layer = 0..3). While the countdown byte at +0x6B+layer
 * equals the layer's visible-tile count at +0xF3+layer and is nonzero, decrement
 * it; then, if the countdown has fallen below the layer's fade level at +0x6F
 * (signed) and that level is nonzero, drop the level by 8, clamping at 0. */
void sub_0800F370(u8 arg0)
{
  u8 layer;
  u8 *state;
  u8 *counters;
  u8 *visiblePtr;
  s32 countdown;
  s32 visible;
  s32 level;
  s32 rawLevel;
  u8 *levelPtr;
  layer = arg0;
  state = gMenuState;
  counters = state + 0x6B;
  countdown = *((s8 *) (counters + layer));
  visiblePtr = counters + 0x88;
  visible = *((u8 *) (visiblePtr + layer));
  if ((countdown == visible) && (((u8) countdown) != 0))
  {
    countdown--;
    *((s8 *) (counters + layer)) = countdown;
    levelPtr = levelBase(state) + layer;
    countdown <<= 24;
    countdown >>= 24;
    rawLevel = *((u8 *) levelPtr);
    level = *((s8 *) levelPtr);
    if ((countdown < level) && (level != 0))
    {
      rawLevel -= 8;
      *((u8 *) levelPtr) = rawLevel;
      if (((s8) rawLevel) < 0)
      {
        *((u8 *) levelPtr) = 0;
      }
    }
  }
}
