extern s32 sub_080141AC(void *, void *);
extern s32 sub_08013B5C(void *, void *);
extern void sub_080C31E0(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866DDFC[];
/* Updates the entity's pose and script, then applies table-driven coordinate
 * offsets to its owner's fields. */
void sub_0803677C(u8 *entity)
{
  u32 tableX;
  u32 tableY;
  u8 *ownerRef;
  u8 *data;
  unsigned int index2;
  u8 *posePtr;
  ownerRef = *((u8 **) (entity + 0x38));
  data = *((u8 **) (entity + 0x3C));
  if (sub_080141AC(ownerRef, data) == 1)
  {
    sub_080C31E0(entity, *((void **) (entity + 0x24)));
    return;
  }
  posePtr = entity + 0x22;
  if (sub_08013B5C(ownerRef, data) == 0)
  {
    s16 poseIndex;
    s32 byteOffset;
    u8 *poseBase;
    *((u32 *) (entity + 0x14)) = (u32) D_0866DDFC;
    *((u16 *) posePtr) = (*((u16 *) posePtr)) + 1;
    poseIndex = *((s16 *) posePtr);
    *((u8 *) ((entity + (poseIndex * 2)) + 0x19)) += 1;
    poseIndex = *((s16 *) posePtr);
    byteOffset = poseIndex * 2;
    poseBase = entity + 0x18;
    sub_080C31E0(entity, *((void **) ((*((u32 *) (entity + 0x14))) + ((2 * (*((u8 *) (poseBase + byteOffset)))) * 2))));
    *((u16 *) posePtr) = (*((u16 *) posePtr)) - 1;
  }
  {
    u8 *pt = gCameraState;
    u8 *pb = gMainWorkspace;
    u8 *pt1;
    u32 idx;
    u32 v1;
    pb += 0x18A8;
    idx = (((u32) (*pb)) + 1) << 6;
    pt1 = pt + 0x1278;
    v1 = *((u32 *) (pt1 + idx));
    tableX = v1;
    *((u32 *) (ownerRef + 0x14)) = (*((u32 *) (data + 0x08))) - ((tableX + 0x8000) & 0xFFFF0000);
    index2 = (1 + ((u32) (*pb))) << 6;
    idx = index2;
    pt += 0x127C;
    v1 = (tableY = *((u32 *) (pt + idx)));
    *((u32 *) (ownerRef + 0x18)) = (*((u32 *) (data + 0x0C))) - ((v1 + 0xFFFF8000) & 0xFFFF0000);
  }
}
