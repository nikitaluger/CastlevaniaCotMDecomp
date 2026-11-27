/* Action-script object shared with the command handlers at 0x080BCE20..:
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
s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080C31E0(void *, void *);

/* Wait for the current step's sprite animation to finish; when it has, step the
 * script forward, bump the new step's repeat counter and run its command
 * callback once, then refresh the sprite's screen position. (Script table
 * 0x086706F8.) */
void sub_080BCDC0(struct ActionScript *arg0)
{
  int cmdArrayOffset;
  int stepOffset;
  void *sprite = (void *) arg0->sprite;
  if (updateObjectDisplayState(sprite, (void *) arg0->work) == 0)
  {
    arg0->commandTable = 0x086706F8;
    arg0->stepIndex += 1;
    *((u8 *) ((((u8 *) arg0) + (arg0->stepIndex * 2)) + 0x19)) += 1;
    cmdArrayOffset = 0x18;
    stepOffset = arg0->stepIndex * 2;
    sub_080C31E0(arg0, *((void **) ((((u32) (*((u8 *) ((((u8 *) arg0) + cmdArrayOffset) + stepOffset)))) * 4) + arg0->commandTable)));
    arg0->stepIndex -= 1;
  }
  sub_08013C8C(arg0, sprite);
}

/* Same "advance the script when the current animation ends" handler for the
 * companion script table 0x08670708. */
void sub_080BD290(struct ActionScript *arg0)
{
  int cmdArrayOffset;
  int stepOffset;
  void *sprite = (void *) arg0->sprite;
  if (updateObjectDisplayState(sprite, (void *) arg0->work) == 0)
  {
    arg0->commandTable = 0x08670708;
    arg0->stepIndex += 1;
    *((u8 *) ((((u8 *) arg0) + (arg0->stepIndex * 2)) + 0x19)) += 1;
    cmdArrayOffset = 0x18;
    stepOffset = arg0->stepIndex * 2;
    sub_080C31E0(arg0, *((void **) ((((u32) (*((u8 *) ((((u8 *) arg0) + cmdArrayOffset) + stepOffset)))) * 4) + arg0->commandTable)));
    arg0->stepIndex -= 1;
  }
  sub_08013C8C(arg0, sprite);
}
