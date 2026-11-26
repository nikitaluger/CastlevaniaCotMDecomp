extern s32 sub_080C31E0(void *a, void *b);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Masks the gfx attributes, advances the script step and dispatches its handler,
 * then stores the actor's position relative to the current coordinate table. */
void sub_080A4DD0(void *arg0)
{
  void *gfx;
  void *actor;
  int stepIndex;
  u8 *coordTable;
  u8 *globals;
  u32 tableOffset;
  u8 *xTable;
  u8 *yTable;

  gfx = *((void **) (((u8 *) arg0) + 0x38));
  actor = *((void **) (((u8 *) arg0) + 0x3C));
  *((u16 *) gfx) = (u16) ((*((u16 *) gfx)) & 0x0FFF);
  *((void **) (((u8 *) arg0) + 0x14)) = (void *) 0x0866FF4C;
  *((u16 *) (((u8 *) arg0) + 0x22)) = (u16) ((*((u16 *) (((u8 *) arg0) + 0x22))) + 1);
  {
    u8 *step = (u8 *) ((((s32) (*((s16 *) (((u8 *) arg0) + 0x22)))) * 2) + ((u32) arg0));
    step[0x19] = (u8) (step[0x19] + 1);
  }
  stepIndex = ((s32) (*((s16 *) (((u8 *) arg0) + 0x22)))) * 2;
  {
    u8 *steps = ((u8 *) arg0) + 0x18;
    s32 stepOffset = stepIndex;
    u8 handlerIdx = *(steps + stepOffset);
    u8 **handlerTable = *((u8 **) (((u8 *) arg0) + 0x14));
    sub_080C31E0(arg0, (s32) handlerTable[handlerIdx]);
  }
  *((u16 *) (((u8 *) arg0) + 0x22)) = (u16) ((*((u16 *) (((u8 *) arg0) + 0x22))) - 1);
  coordTable = gCameraState;
  globals = gMainWorkspace;
  globals += 0x18A8;
  tableOffset = (((u32) (*globals)) + 1) * 0x40;
  xTable = coordTable + 0x1278;
  *((s32 *) (((u8 *) gfx) + 0x14)) = (*((s32 *) (((u8 *) actor) + 0x08))) - (((*((s32 *) (xTable + tableOffset))) + 0x8000) & 0xFFFF0000);
  tableOffset = (((u32) (*globals)) + 1) * 0x40;
  yTable = coordTable + 0x127C;
  *((s32 *) (((u8 *) gfx) + 0x18)) = (*((s32 *) (((u8 *) actor) + 0x0C))) - (((*((s32 *) (yTable + tableOffset))) + 0xFFFF8000) & 0xFFFF0000);
}
