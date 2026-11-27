extern s32 scaleByRandom(s32);
extern s32 signOf(s32);
extern s32 sub_08014990(void *);
extern void sub_080C31E4(void *, void *, s32);

struct SpriteAttrs { u8 pad[2]; u16 flags; };

/* Script step: face the sprite toward the player, randomise two animation
 * timers, clear the step flag and advance this actor's script. */
void sub_0801A768(void *actor)
{
  u8 *self = (u8 *) actor;
  u8 *sprite = *((u8 **) (self + 0x38));
  int zeroWord;
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *animState = work + 0x48;
  u8 zeroByte;
  s32 *scriptTable;
  if ((*((s16 *) (animState + 0x12))) != 0)
  {
    {
      struct SpriteAttrs *attrs = (struct SpriteAttrs *)sprite;
      if (signOf(*((s32 *) (work + 8))) > 0)
        attrs->flags |= 0x10;
      else
        attrs->flags &= 0xFFEF;
    }
    *((u16 *) (animState + 0x1A)) = (u16) (scaleByRandom(0x29) + 0x64);
    zeroWord = 0;
    if (sub_08014990(sprite) > zeroWord)
      *((s32 *) (work + 0x10)) = 0x80 << 7;
    else
      *((s32 *) (work + 0x10)) = (s32) 0xFFFFC000;
    zeroByte = zeroWord;
    *((u16 *) (animState + 0x14)) = zeroWord;
    *((u16 *) (animState + 0x1C)) = (u16) (scaleByRandom(0x3D) + 0x3C);
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = zeroByte;
    scriptTable = (s32 *) 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
  }
}
