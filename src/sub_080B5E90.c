s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);
void sub_080113A8(void *, void *);
void sub_08011EE8(void *, s32, s32);

/* Action-script object shared with the command handlers at 0x080B5EF0..:
 * 0x14 command-pointer table, 0x18 per-step command bytes, 0x22 step index,
 * 0x38 sprite, 0x3C work/position struct. */
struct ActionScript
{
  u8 _0x00[0x14];
  u32 commandTable;
  u8 _0x18[0x0A];
  s16 stepIndex;
  u32 field_0x24;
  u8 _0x28[0x10];
  u32 sprite;
  u32 work;
};

/* Wait for the current step's sprite animation to finish; when it has, step the
 * script forward, bump the new step's repeat counter and run its command
 * callback once, then refresh the sprite's screen position from the work
 * position and the camera. */
void sub_080B5E90(struct ActionScript *arg0)
{
  int cmdArrayOffset;
  int stepOffset;
  void *sprite = (void *) arg0->sprite;
  if (sub_08013B5C(sprite, (void *) arg0->work) == 0)
  {
    arg0->commandTable = 0x08670444;
    arg0->stepIndex += 1;
    *((u8 *) ((((u8 *) arg0) + (arg0->stepIndex * 2)) + 0x19)) += 1;
    cmdArrayOffset = 0x18;
    stepOffset = arg0->stepIndex * 2;
    sub_080C31E0(arg0, *((void **) ((((u32) (*((u8 *) ((((u8 *) arg0) + cmdArrayOffset) + stepOffset)))) * 4) + arg0->commandTable)));
    arg0->stepIndex -= 1;
  }
  sub_08013C8C(arg0, sprite);
}
