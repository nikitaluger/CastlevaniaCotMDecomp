s32 sub_08013B5C(void *, void *);
void sub_080C31E0(void *, void *);

struct ScriptEntity
{
  u8 _0x00[0x14];
  u32 handlerTable;
  u8 _0x18[0x0A];
  s16 step;
  u32 field_0x24;
  u8 _0x28[0x10];
  u32 sprite;
  u32 work;
};

/* Script command: once the sprite's display-state handler stops consuming the
 * frame, switch to handler table 0x0866FE74, bump the action byte of the next
 * script step, dispatch that step's handler and restore the step. */
void sub_080A2000(struct ScriptEntity *arg0)
{
  int byteBase;
  int stepOffset;
  if (sub_08013B5C((void *)arg0->sprite, (void *)arg0->work) == 0)
  {
    arg0->handlerTable = 0x0866FE74;
    arg0->step += 1;
    *((u8 *) ((((u8 *) arg0) + (arg0->step * 2)) + 0x19)) += 1;
    byteBase = 0x18;
    stepOffset = arg0->step * 2;
    sub_080C31E0(arg0, *((void **) ((((u32) (*((u8 *) ((((u8 *) arg0) + byteBase) + stepOffset)))) * 4) + arg0->handlerTable)));
    arg0->step -= 1;
  }
}
