s32 sub_080C31E0(void *, s32);

/* Fading bloom effect: widen the sprite's X scale by 0x20 each frame while
 * shrinking its Y scale by 2 (floor 0x80), push it left with a constant
 * horizontal acceleration, and once the step value reaches 0x80 clear the
 * sprite's active bit and advance the state. */
void sub_0808EA70(void *arg0)
{
  s32 scaleY;
  s32 *motion;
  void *self;
  void *sprite;

  sprite = *((void **) (((u8 *) (*((void **) (((u8 *) arg0) + 0x28)))) + 0x38));
  motion = *((s32 **) (((u8 *) arg0) + 0x3C));
  *((u16 *) (((u8 *) sprite) + 4)) = (u16) ((*((u16 *) (((u8 *) sprite) + 4))) + 0x20);
  scaleY = (*((u16 *) (((u8 *) sprite) + 6))) - 2;
  scaleY = scaleY;
  *((u16 *) (((u8 *) sprite) + 6)) = scaleY;
  if (((s32) ((s16) scaleY)) <= 0x80)
  {
    *((u16 *) (((u8 *) sprite) + 6)) = 0x80U;
  }
  *motion += 0xFFFFC000;
  self = arg0;
  if ((*((s16 *) (((u8 *) self) + 0x22))) == 0x80)
  {
    *((u8 *) (((u8 *) sprite) + 0x2A)) = (u8) (0xBF & (*((u8 *) (((u8 *) sprite) + 0x2A))));
    sub_080C31E0(self, *((s32 *) (((u8 *) self) + 0x24)));
  }
}
