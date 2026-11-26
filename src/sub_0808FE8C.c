extern void sub_080113A8(void *, void *);
extern s32 sub_0805F9B4(s32, s32);
extern u8 *sub_08016238(u8 *);
extern s32 sub_080C31E0(s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern s16 D_081003F0[];
extern u8 D_0866F948[];
struct SpriteFlag { u8 flag; };

/* Per-frame update: mark the sprite by camera visibility, resolve a pending hit
 * target, advance one script step, and refresh the sprite's screen position. */
void sub_0808FE8C(u8 *entity)
{
  u8 *sprite;
  u8 *state;
  u8 *animTrack;
  s32 outsideCamera;
  u8 *coordTable;
  u8 *xBase;
  u8 *cameraIndex;
  u32 coordOffset;
  u32 originX;
  u32 originY;
  u32 command;
  u8 *scriptBase;
  u32 originYRaw;
  u8 *t;
  s16 *targetList;
  s16 *listCursor;
  s32 hitId;
  s32 targetId;
  sprite = *((u8 **) (entity + 0x38));
  state = *((u8 **) (entity + 0x3C));
  animTrack = state + 0x20;
  {
    u8 *subObj = *((u8 **) (state + 4));
    u8 zero = 0;
    *((u8 *) (subObj + 1)) = zero;
  }
  outsideCamera = sub_0805F9B4(*((s32 *) (state + 0xC)), *((s32 *) (state + 0x10)));
  if (outsideCamera == 1)
  {
    ((struct SpriteFlag *) (sprite + 0x2A))->flag &= 0xBF;
  }
  else
  {
    ((struct SpriteFlag *) (sprite + 0x2A))->flag |= 0x40;
  }
  targetId = *((s16 *) (state + 0x16));
  scriptBase = entity + 0x18;
  if (targetId == 0)
  {
    *((u8 *) ((*((u8 **) (state + 4))) + 1)) = 4;
    t = sub_08016238(*((u8 **) (state + 4)));
    if (t != NULL)
    {
      targetList = D_081003F0;
      if ((*targetList) != 0)
      {
        do
        {
          hitId = *((s16 *) (t + 0x18));
          listCursor = targetList;
          do
          {
            if (hitId == (*targetList))
            {
              *((s16 *) (state + 0x16)) = 1;
              break;
            }
            listCursor++;
            targetList++;
          }
          while ((*listCursor) != 0);
        }
        while (0);
      }
    }
  }
  *((u32 *) (entity + 0x14)) = (u32) D_0866F948;
  *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) + 1;
  *((u8 *) (((u32) entity) + ((u32) (*((s16 *) (entity + 0x22)))) * 2 + 0x19)) = (*((u8 *) (((u32) entity) + ((u32) (*((s16 *) (entity + 0x22)))) * 2 + 0x19))) + 1;
  command = *((u8 *) (((u32) scriptBase) + ((u32) (*((s16 *) (entity + 0x22)))) * 2));
  sub_080C31E0((s32) entity, *((u32 *) ((*((u32 *) (entity + 0x14))) + (command * 4))));
  *((u16 *) (entity + 0x22)) = (*((u16 *) (entity + 0x22))) - 1;
  if (((*((u16 *) (entity + 2))) & 0x8000) == 0)
  {
    if ((*((s16 *) (state + 0x14))) == 1)
    {
      sub_080113A8(sprite, animTrack);
    }
    coordTable = gCameraState;
    cameraIndex = gMainWorkspace;
    cameraIndex += 0x18A8;
    coordOffset = (((u32) (*cameraIndex)) + 1) * 0x40;
    xBase = coordTable + 0x1278;
    originX = *((u32 *) (xBase + coordOffset));
    *((u32 *) (sprite + 0x14)) = (*((u32 *) (state + 0xC))) - ((originX + 0x8000) & 0xFFFF0000);
    coordOffset = (((u32) (*cameraIndex)) + 1) * 0x40;
    coordTable += 0x127C;
    originYRaw = *((u32 *) (coordTable + coordOffset));
    originY = originYRaw;
    *((u32 *) (sprite + 0x18)) = (*((u32 *) (state + 0x10))) - ((originY + 0xFFFF8000) & 0xFFFF0000);
  }
}
