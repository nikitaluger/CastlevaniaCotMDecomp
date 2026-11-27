s32 isOutsideCameraBounds(s32 a, s32 b);
s32 updateObjectDisplayState(void *a, void *b);
void stepAnimationTrack(void *a, void *b);
void sub_08011EE8(void *a, s32 b, s32 c);
void sub_080C31E0(void *a, void *b);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Update one entity: bail out through its fail callback if it leaves the
 * active area or its display flags say so, otherwise advance its movement/
 * collision and convert its world position into camera-relative sprite coords. */
void sub_08059FF0(void *entity)
{
  void *sprite;
  void *body;
  u8 *anim;
  sprite = *((void **) (((u8 *) entity) + 0x38));
  body = *((void **) (((u8 *) entity) + 0x3C));
  anim = ((u8 *) body) + 0x34;
  if (isOutsideCameraBounds(*((s32 *) (((u8 *) body) + 0x08)), *((s32 *) (((u8 *) body) + 0x0C))) == 1)
  {
    goto end;
  }
  if (updateObjectDisplayState(sprite, body) != 0)
  {
    goto calc;
  }
  stepAnimationTrack(sprite, anim);
  sub_08011EE8(body, 0x2221, 0);
  if ((*((u16 *) (((u8 *) body) + 0x02))) & 4)
  {
    goto end;
  }
  if ((*((u8 *) ((((u8 *) entity) + ((*((s16 *) (((u8 *) entity) + 0x22))) * 2)) + 0x19))) > 0x14)
  {
    goto end;
  }
  goto calc;
  end:
  sub_080C31E0(entity, *((void **) (((u8 *) entity) + 0x24)));

  return;
  calc:
  {
    u8 *camTbl = gCameraState;
    u8 *frame = gMainWorkspace;
    u8 *camX;
    u8 *camY;
    unsigned short camIdx;
    frame = frame + 0x18A8;
    camIdx = (((u32) (*frame)) + 1) << 6;
    camX = camTbl + 0x1278;
    *((s32 *) (((u8 *) sprite) + 0x14)) = (*((s32 *) (((u8 *) body) + 0x08))) - ((s32) (((*((u32 *) (camX + camIdx))) + 0x8000) & 0xFFFF0000));
    camIdx = (((u32) (*frame)) + 1) << 6;
    camY = camTbl + 0x127C;
    *((s32 *) (((u8 *) sprite) + 0x18)) = (*((s32 *) (((u8 *) body) + 0x0C))) - ((s32) (((*((u32 *) (camY + camIdx))) + 0xFFFF8000) & 0xFFFF0000));
  }

}
