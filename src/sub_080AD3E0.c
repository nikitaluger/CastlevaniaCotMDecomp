s32 updateObjectDisplayState(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
void _call_via_r1(void *, void *);

struct S_AD3E0
{
  u8 _00[0x14];
  u32 handlers;
  u8 _18[0x0A];
  s16 step;
  u8 _24[0x14];
  u32 sprite;
  u32 work;
};

/* If the sprite's timed display did not consume this frame, switch the entity to
 * the script handler table at 0x08670190, bump the step index so its action byte
 * is advanced, dispatch that step's handler, then restore the index; finally
 * refresh the sprite's screen position. */
void sub_080AD3E0(struct S_AD3E0 *arg0)
{
  int stepScale;
  void *sprite = (void *) arg0->sprite;
  int stepBaseOffset;
  struct S_AD3E0 *self;
  u8 *new_var3;
  self = arg0;
  if (updateObjectDisplayState(sprite, (void *) self->work) == 0)
  {
    stepBaseOffset = 0x18;
    self->handlers = 0x08670190;
    self->step += 1;
    ;
    *((u8 *) ((((u8 *) self) + (self->step * 2)) + 0x19)) += 1;
    _call_via_r1(self, *((void **) (((*((u8 *) ((((u8 *) self) + stepBaseOffset) + (self->step * (stepScale = 2))))) * 4) + self->handlers)));
    self->step -= 1;
  }
  syncSpriteToWorldPosition(self, sprite);
}
