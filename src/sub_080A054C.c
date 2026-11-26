extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Set or clear this object's visibility bit in the coordinate table: kind 0
 * only sets it; otherwise clear it, then store the object's camera-relative X
 * and Y (from the current camera index) back into the table. */
void sub_080A054C(unsigned long kind, s32 worldX, s32 worldY)
{
  u16 screenX;
  u32 worldXU;
  u32 tableOffset = 0x1278;
  u32 camValue;
  if (kind == 0)
  {
    u8 *coordTable = gCameraState;
    volatile u16 *p = (volatile u16 *) (coordTable + (0x97 << 5));
    u16 oldBits = *p;
    *p = oldBits | (0x80 << 6);
    return;
  }
  else
  {
    u8 *coordTable = gCameraState;
    *((volatile u16 *) (coordTable + (0x97 << 5))) &= 0xDFFF;
    {
      u32 cameraOffset;
      u8 *cameraIndex = gMainWorkspace;
      cameraIndex = cameraIndex + 0x18A8;
      cameraOffset = ((*cameraIndex) + 1) << 6;
      {
        camValue = *((u32 *) ((coordTable + tableOffset) + cameraOffset));
        worldXU = (u32) worldX;
        screenX = (worldXU - ((camValue + 0x8000) & 0xFFFF0000)) >> 16;
        tableOffset += 0x9C;
        *((volatile u16 *) (coordTable + tableOffset)) = screenX;
        *((volatile u32 *) (coordTable + 0x130C)) = worldY;
      }
    }
  }
}
