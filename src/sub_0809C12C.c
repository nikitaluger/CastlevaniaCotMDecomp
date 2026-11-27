s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);
s8 scaleByRandom(s32);
void loadEffectPalette(u32, void *);
extern void sub_0809BEE8(void);

struct S_0807B12C
{
  u8 _0x00[0x14];
  u32 handlers;
  u8 _0x18[0x0A];
  s16 step;
  u32 field_0x24;
  u8 _0x28[0x10];
  u32 sprite;
  u32 work;
};

/* If the sprite's timed display did not consume this frame, switch the entity to
 * the script handler table at 0x0866FC8C, bump the step index so its action byte
 * is advanced, dispatch that step's handler, then restore the index; finally
 * refresh the sprite's screen position. */
void sub_0809C12C(struct S_0807B12C *arg0)
{
  int stepBaseOffset;
  int stepOffset;
  void *sprite = (void *) arg0->sprite;
  if (updateObjectDisplayState(sprite, (void *) arg0->work) == 0)
  {
    arg0->handlers = 0x0866FC8C;
    arg0->step += 1;
    *((u8 *) ((((u8 *) arg0) + (arg0->step * 2)) + 0x19)) += 1;
    stepBaseOffset = 0x18;
    stepOffset = arg0->step * 2;
    sub_080C31E0(arg0, *((void **) ((((u32) (*((u8 *) ((((u8 *) arg0) + stepBaseOffset) + stepOffset)))) * 4) + arg0->handlers)));
    arg0->step -= 1;
  }
  sub_08013C8C(arg0, sprite);
}
