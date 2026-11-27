s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);

struct S_B53B8
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
 * the script handler table at 0x0867040C, bump the step index so its action byte
 * is advanced, dispatch that step's handler, then restore the index; finally
 * refresh the sprite's screen position. */
void sub_080B53B8(struct S_B53B8 *arg0)
{
  void *sprite = (void *) arg0->sprite;
  int stepBaseOffset;
  int stepScale;
  if (updateObjectDisplayState(sprite, (void *) arg0->work) == 0)
  {
    stepBaseOffset = 0x18;
    arg0->handlers = 0x0867040C;
    arg0->step += 1;
    stepScale = 2;
    *((u8 *) ((((u8 *) arg0) + (arg0->step * 2)) + 0x19)) += 1;
    sub_080C31E0(arg0, *((void **) (((*((u8 *) ((((u8 *) arg0) + stepBaseOffset) + (arg0->step * stepScale)))) * 4) + arg0->handlers)));
    arg0->step -= 1;
  }
  sub_08013C8C(arg0, sprite);
}
