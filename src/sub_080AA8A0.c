extern s32 sub_080C31E0(s32 arg0, s32 arg1);
extern u8 D_08102178[];
/* Compute an entity's pose-based position offset from its facing angle,
 * writing the resulting x/y values into the output object. */
void sub_080AA8A0(void *obj, void *result)
{
  u8 *a0 = (u8 *) obj;
  u8 *a1 = (u8 *) result;
  s32 poseIndex;
  u8 *frameData;
  u32 poseCode;
  u32 halfTurn;
  poseIndex = 0;
  frameData = *((u8 **) ((*((u8 **) (a0 + 0x28))) + 0x3C));
  halfTurn = 0x8000;
  {
    u8 *frameInfo = frameData + 0x34;
    u32 *poseTable = *((u32 **) (frameInfo + 8));
    s32 frameIndex = (*((s16 *) (frameInfo + 0x0E))) + (*((u8 *) (frameInfo + 1)));
    u32 poseTableBase = *poseTable;
    u8 *frameEntry = (u8 *) (((frameIndex * 4) + poseTableBase) - 4);
    poseCode = *((u16 *) (frameEntry + 2));
  }
  if (poseCode <= 0x12)
  {
    switch (poseCode)
    {
      case 0:
        poseIndex = 0;
        break;

      case 3:
        poseIndex = 1;
        break;

      case 6:
        poseIndex = 2;
        break;

      case 12:
        poseIndex = 3;
        break;

      case 15:
        poseIndex = 4;
        break;

      case 18:
        poseIndex = 5;
        break;

      default:
        break;

    }

  }
  {
    u8 *motionState = *((u8 **) ((*((u8 **) (a0 + 0x28))) + 0x38));
    s32 localAngle;
    s32 *amplitude;
    s32 radius;
    s32 cosComponent;
    s32 sinComponent;
    if ((*((u16 *) (motionState + 2))) & 0x10)
    {
      s32 angle = *((u16 *) (motionState + 8));
      u8 *poseTableBase = D_08102178;
      s32 entryOffset = poseIndex * 8;
      u8 *entryData = poseTableBase + 4;
      localAngle = angle - (*((u32 *) (entryData + entryOffset)));
    }
    else
    {
      s32 angle = *((u16 *) (motionState + 8));
      u8 *poseTableBase = D_08102178;
      s32 entryOffset = poseIndex * 8;
      u8 *entryData = poseTableBase + 4;
      localAngle = halfTurn - (angle - (*((u32 *) (entryData + entryOffset))));
    }
    amplitude = (s32 *) 0x08671BFC;
    radius = poseIndex * 8;
    cosComponent = sub_080C31E0(localAngle + 0x4000, *amplitude);
    radius = (*((s32 *) (D_08102178 + radius))) >> 8;
    *((s32 *) (a1 + 8)) = (*((s32 *) (frameData + 8))) + (radius * (cosComponent >> 8));
    sinComponent = sub_080C31E0(localAngle, *amplitude);
    *((s32 *) (a1 + 0xC)) = (*((s32 *) (frameData + 0xC))) + (radius * (sinComponent >> 8));
  }
}
