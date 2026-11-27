extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern void _call_via_r1(void *, u32);
extern void _call_via_r2(void *, void *, u32);
void *allocEffectPart(void);

/* Set up a main object's effect: initialise its graphics-init words, register
 * the sprite with the global workspace, zero the work-state position words,
 * copy game-status parameters, allocate and fill two render layers, then
 * dispatch the current script step; on allocation failure call the object's
 * saved handler. */
void initMainObjectEffectGraphics(void *object)
{
  u8 *objBytes = (u8 *) object;
  struct MainObjectEffectWork *work = (struct MainObjectEffectWork *) (*((u32 *) (objBytes + 0x6C)));
  u8 *workBytes;
  u8 *gfxInit = ((u8 *) work) + 4;
  void *sprite = *((void **) (objBytes + 0x38));
  u8 *gameState = gGameStatus;
  s32 zero;
  u8 *workspace;
  u32 posXOffset;
  u32 posYOffset;
  struct MainObjectEffectLayer *layer;
  u32 *callback;
  workBytes = (u8 *) work;
  *((u32 *) (workBytes + 4)) = 0x780000;
  *((u32 *) (gfxInit + 4)) = 0x7F0000;
  workspace = gMainWorkspace;
  *((void **) (workspace + 0x171C)) = sprite;
  *((void **) (workspace + 0x1720)) = gfxInit;
  *((void **) (workspace + 0x1724)) = gfxInit;
  posXOffset = 0x8A << 1;
  *((u32 *) (((u8 *) work) + posXOffset)) = (zero = 0);
  posYOffset = 0x8C << 1;
  *((u32 *) (((u8 *) work) + posYOffset)) = zero;
  work->statusByte0 = gameState[0x3C4];
  work->statusByte1 = gameState[0x3C5];
  work->statusByte2 = gameState[0x3C6];
  layer = (struct MainObjectEffectLayer *) allocEffectPart();
  work->layer1 = layer;
  if (layer == 0)
  {
    if (work->layer1)
    {
      _call_via_r1(objBytes, (u32) (*((void **) (objBytes + 0x24))));
      return;
    }
    else
    {
      _call_via_r1(objBytes, (u32) (*((void **) (objBytes + 0x24))));
      return;
    }
  }
  layer->param2 = 1;
  work->layer1->param3 = 0x80;
  work->layer1->gfxA = 0;
  work->layer1->gfxB = 0xA;
  work->layer1->sprite = sprite;
  work->layer1->timer = 0x1E;
  layer = (struct MainObjectEffectLayer *) allocEffectPart();
  work->layer2 = layer;
  if (layer == 0)
  {
    if (work->layer2)
    {
      _call_via_r1(objBytes, (u32) (*((void **) (objBytes + 0x24))));
      return;
    }
    else
    {
      _call_via_r1(objBytes, (u32) (*((void **) (objBytes + 0x24))));
      return;
    }
  }
  work->layer2->active = 0;
  work->layer2->param2 = 1;
  work->layer2->param3 = 8;
  work->layer2->gfxA = 0;
  work->layer2->gfxB = *((u16 *) (gameState + (0xB8 << 2)));
  work->layer2->sprite = sprite;
  work->layer2->timer = 0x1E;
  work->layer2->tail = 0;
  *((u8 *) ((objBytes + ((*((s16 *) (objBytes + 0x22))) * 2)) + 0x19)) = 0;
  callback = (u32 *) MAIN_OBJ_TIMER_CALLBACK_TABLE;
  _call_via_r2(objBytes + 0x18, objBytes + 0x22, *callback);
}
