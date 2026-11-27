extern s32 sub_080C31E0(s32 arg0, s32 arg1);
extern u8 gPosePlacementTable[];
/* Compute an entity's pose-based position offset from its facing angle, writing
 * the resulting 16.16 X/Y into outPosition+8 and outPosition+0xC. */
void computePosePlacementOffset(void *entity, void *outPosition)
{
  u8 *entityBytes = (u8 *) entity;
  u8 *outBytes = (u8 *) outPosition;
  s32 pose;
  u8 *frameData;
  u32 poseCode;
  u32 halfTurn;
  pose = 0;
  frameData = *((u8 **) ((*((u8 **) (entityBytes + 0x28))) + 0x3C));
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
        pose = 0;
        break;

      case 3:
        pose = 1;
        break;

      case 6:
        pose = 2;
        break;

      case 12:
        pose = 3;
        break;

      case 15:
        pose = 4;
        break;

      case 18:
        pose = 5;
        break;

      default:
        break;

    }

  }
  {
    u8 *motionState = *((u8 **) ((*((u8 **) (entityBytes + 0x28))) + 0x38));
    s32 localAngle;
    s32 *trigFuncSlot;
    s32 radius;
    s32 cosine;
    s32 sine;
    if ((*((u16 *) (motionState + 2))) & 0x10)
    {
      s32 angle = *((u16 *) (motionState + 8));
      u8 *poseEntryBase = gPosePlacementTable;
      s32 entryOffset = pose * 8;
      u8 *entryData = poseEntryBase + 4;
      localAngle = angle - (*((u32 *) (entryData + entryOffset)));
    }
    else
    {
      s32 angle = *((u16 *) (motionState + 8));
      u8 *poseEntryBase = gPosePlacementTable;
      s32 entryOffset = pose * 8;
      u8 *entryData = poseEntryBase + 4;
      localAngle = halfTurn - (angle - (*((u32 *) (entryData + entryOffset))));
    }
    trigFuncSlot = (s32 *) 0x08671BFC;
    radius = pose * 8;
    cosine = sub_080C31E0(localAngle + 0x4000, *trigFuncSlot);
    radius = (*((s32 *) (gPosePlacementTable + radius))) >> 8;
    *((s32 *) (outBytes + 8)) = (*((s32 *) (frameData + 8))) + (radius * (cosine >> 8));
    sine = sub_080C31E0(localAngle, *trigFuncSlot);
    *((s32 *) (outBytes + 0xC)) = (*((s32 *) (frameData + 0xC))) + (radius * (sine >> 8));
  }
}
