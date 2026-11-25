extern void sub_08014588(s32 arg0, s32 arg1);
extern u32 D_081018F0[];
struct FrameEntry
{
  u16 unk_0x00;
  u16 id;
};
inline int addOffsets(int arg0, int arg1)
{
  return arg0 + arg1;
}

/* Copies the 8-byte pose record for `entityId` from D_081018F0 into `dst`; the
 * record is the default one, or the variant selected by the entity's current
 * animation frame (0x5E -> variant 1, 0x8F -> variant 2). */
void sub_0809C618(s32 entityId, void *anim, s32 dst)
{
  s32 pose = 0;
  u32 frameTable = *((u32 *) (((u8 *) anim) + 8));
  s32 frameIndex = ((s32) (*((s16 *) (((u8 *) anim) + 0xE)))) + ((s32) (*((u8 *) (((u8 *) anim) + 1))));
  u32 entries = *((u32 *) frameTable);
  struct FrameEntry *frame = (struct FrameEntry *) (((frameIndex * 4) + entries) - 4);
  u16 frameId = frame->id;
  s32 caseValue;
  caseValue = 0x2F;
  if (frameId == caseValue)
  {
    goto done;
  }
  if (frameId <= caseValue)
  {
    goto done;
  }
  caseValue = 0x4B;
  if (frameId == caseValue)
  {
    goto done;
  }
  if (frameId <= caseValue)
  {
    goto done;
  }
  caseValue = 0x5E;
  if (frameId == caseValue)
  {
    goto poseOne;
  }
  if (frameId <= caseValue)
  {
    goto done;
  }
  caseValue = 0x8F;
  if (frameId == caseValue)
  {
    goto poseTwo;
  }
  goto done;
  poseOne:
  pose = 1;

  goto done;
  poseTwo:
  pose = 2;

  done:
  sub_08014588(dst, addOffsets(pose * 0x18, ((u32) D_081018F0) + (entityId * 8)));

}
