struct AngleState { u8 pad[0xE]; s16 angle; };
struct AngleEntry { u16 pad; u16 diff; };

inline u16 getAngleDiff(s32 *arg0, s32 arg1)
{
  return ((struct AngleEntry *)arg0)[arg1 - 1].diff;
}

/* Computes a direction-signed spawn offset from an angle-difference table and applies
 * it to a base position, storing the raw angle on the output entity. */
void sub_0809C318(void *out, void *source, void *base, void *angleState, s32 rawAngle)
{
  u16 angle = (u16) rawAngle;
  s32 bucket = 0;
  s32 dir;
  s32 flipMask;
  s32 wordOffset;
  u16 angleDiff;
  u8 *stateBytes;
  s32 *ptrTable;
  s32 angleIdx;
  s32 *diffTable;
  u32 *offsetTable;
  if (out != 0)
  {
    *((u16 *) (((u8 *) out) + 0x7C)) = angle;
    flipMask = (*((u16 *) (((u8 *) source) + 0x02))) & 0x10;
    dir = -1;
    if (flipMask)
    {
      dir = 1;
    }
    *((s32 *) (((u8 *) out) + 0x6C)) = dir;
    stateBytes = (u8 *) angleState;
    ptrTable = *((s32 **) (stateBytes + 0x08));
    angleIdx = ((struct AngleState *)stateBytes)->angle + *((u8 *) (stateBytes + 0x01));
    diffTable = ptrTable[0];
    angleDiff = getAngleDiff(diffTable, angleIdx);
    switch (angleDiff)
    {
      case 0: break;
      case 0x09: bucket = 1; break;
      case 0x12: bucket = 2; break;
      case 0x1C: bucket = 3; break;
      case 0x25: bucket = 4; break;
      case 0x2F: bucket = 5; break;
      case 0x39: bucket = 6; break;
      case 0x43: bucket = 7; break;
      case 0x4B: bucket = 8; break;
      case 0x54: bucket = 9; break;
      case 0x5E: bucket = 0xA; break;
      case 0x8F: bucket = 0xB; break;
    }

    offsetTable = (u32 *) 0x08101890;
    wordOffset = bucket * 8;
    *((s32 *) (((u8 *) out) + 0x4C)) = (*((s32 *) (((u8 *) base) + 0x08))) + ((*((s32 *) (((u8 *) offsetTable) + wordOffset))) * (*((s32 *) (((u8 *) out) + 0x6C))));
    offsetTable += 1;
    *((s32 *) (((u8 *) out) + 0x5C)) = (*((s32 *) (((u8 *) base) + 0x0C))) + (*((s32 *) (((u8 *) offsetTable) + wordOffset)));
  }
}
