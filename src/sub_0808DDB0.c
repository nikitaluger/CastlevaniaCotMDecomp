s32 sub_080113A8(void *, void *);
s32 sub_080C31E0(void *, void *);
struct ScrollState
{
  u8 _pad[0x18A8];
  u8 cameraIndex;
};
extern struct ScrollState gMainWorkspace;
extern u8 gCameraState[];

/* Reposition a sprite from the camera-scroll table: read the scroll index at
 * gMainWorkspace+0x18A8, index the x/y offset tables (+0x1278/+0x127C) by
 * (index+1)*64, subtract the rounded values from the entity's x/y, then tick
 * the animation and switch the state handler when animation flag 2 is set. */
void sub_0808DDB0(void *entity)
{
  void *self = entity;
  void *sprite;
  void *animState;
  u8 *coordTable;
  u8 *xTable;
  u8 *yTable;
  int indexAgain;
  u32 coordOffset;
  s32 tableValue;
  sprite = *((void **) (((u8 *) self) + 0x38));
  animState = *((void **) (((u8 *) self) + 0x3C));
  coordTable = gCameraState;
  coordOffset = (gMainWorkspace.cameraIndex + 1) << 6;
  xTable = coordTable + 0x1278;
  tableValue = *((s32 *) (xTable + coordOffset));
  *((s32 *) (((u8 *) sprite) + 0x14)) = (*((s32 *) (((u8 *) self) + 0x4C))) - ((s32) ((tableValue + 0x8000) & 0xFFFF0000));
  indexAgain = (gMainWorkspace.cameraIndex + 1) << 6;
  coordOffset = indexAgain;
  yTable = coordTable + 0x127C;
  ;
  *((s32 *) (((u8 *) sprite) + 0x18)) = (*((s32 *) (((u8 *) self) + 0x5C))) - ((s32) (((*((s32 *) (yTable + coordOffset))) + 0xFFFF8000) & 0xFFFF0000));
  sub_080113A8(sprite, animState);
  if ((*((u8 *) animState)) & 2)
  {
    sub_080C31E0(self, *((void **) (((u8 *) self) + 0x24)));
  }
}
