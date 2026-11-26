/* Step an actor's action script: clear a state flag, invoke the handler selected
 * by the script from the table at self+0x14, then rebuild two position fields
 * from the room coordinate table. */
extern s32 sub_080C31E0(void *a, void *b);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

void sub_080B1EF8(void *actor)
{
  void *state;
  void *work;
  int scriptOffset;
  u8 *coordTable;
  u8 *indexPtr;
  u32 coordOffset;
  u8 *xBase;
  u8 *yBase;
  state = *((void **) (((u8 *) actor) + 0x38));
  work = *((void **) (((u8 *) actor) + 0x3C));
  *((u16 *) state) = (u16) ((*((u16 *) state)) & 0x0FFF);
  *((void **) (((u8 *) actor) + 0x14)) = (void *) 0x086702EC;
  *((u16 *) (((u8 *) actor) + 0x22)) = (u16) ((*((u16 *) (((u8 *) actor) + 0x22))) + 1);
  {
    u8 *p = (u8 *) ((((s32) (*((s16 *) (((u8 *) actor) + 0x22)))) * 2) + ((u32) actor));
    p[0x19] = (u8) (p[0x19] + 1);
  }
  scriptOffset = ((s32) (*((s16 *) (((u8 *) actor) + 0x22)))) * 2;
  {
    u8 *scriptData = ((u8 *) actor) + 0x18;
    s32 offset = scriptOffset;
    u8 handlerIndex = *(scriptData + offset);
    u8 **handlerTable = *((u8 **) (((u8 *) actor) + 0x14));
    sub_080C31E0(actor, (s32) handlerTable[handlerIndex]);
  }
  *((u16 *) (((u8 *) actor) + 0x22)) = (u16) ((*((u16 *) (((u8 *) actor) + 0x22))) - 1);
  coordTable = gCameraState;
  indexPtr = gMainWorkspace;
  indexPtr += 0x18A8;
  coordOffset = (((u32) (*indexPtr)) + 1) * 0x40;
  xBase = coordTable + 0x1278;
  *((s32 *) (((u8 *) state) + 0x14)) = (*((s32 *) (((u8 *) work) + 0x08))) - (((*((s32 *) (xBase + coordOffset))) + 0x8000) & 0xFFFF0000);
  coordOffset = (((u32) (*indexPtr)) + 1) * 0x40;
  yBase = coordTable + 0x127C;
  *((s32 *) (((u8 *) state) + 0x18)) = (*((s32 *) (((u8 *) work) + 0x0C))) - (((*((s32 *) (yBase + coordOffset))) + 0xFFFF8000) & 0xFFFF0000);
}
