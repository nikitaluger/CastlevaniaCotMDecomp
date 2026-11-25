void sub_080113A8(void *, void *);
void sub_0808D7BC(s32, s32, u32, u8);
void sub_080C31E0(void *, void *);

/* Step the entity's animation; when the track's spawn flag is set, clamp an
 * offset derived from the parent against a limit and spawn a scripted object
 * whose id is that clamped value, then run the entity's script callback. */
void sub_080A2308(void *entity)
{
  s32 delta;
  s32 current;
  s32 sum;
  s32 base;
  void *parent;
  void *animEntity;
  u8 *work;
  s32 track;
  s32 offset;
  u8 *animTrack;
  animEntity = *((void **) (((u8 *) entity) + 0x38));
  work = *((u8 **) (((u8 *) entity) + 0x3C));
  track = (s32) (work + 0x34);
  animTrack = *((u8 **) ((*((u8 **) (((u8 *) entity) + 0x28))) + 0x3C));
  sub_080113A8(animEntity, (void *) track);
  if (2 & (*((u8 *) ((s32) (work + 0x34)))))
  {
    parent = *((void **) (((u8 *) entity) + 0x28));
    track = *((s16 *) (((u8 *) parent) + 0x4C));
    offset = *((s16 *) (((u8 *) parent) + 0x54));
    current = *((s32 *) (animTrack + 0x18));
    sum = current + offset;
    base = current;
    delta = offset;
    if (((s32) track) < sum)
    {
      if (track)
      {
        delta = ((s32) track) - base;
      }
      else
      {
        delta = ((s32) track) - base;
      }
    }
    offset = (*((s32 *) (animTrack + 0x18)) = (s32) ((*((s32 *) (animTrack + 0x18))) + delta));
    sub_0808D7BC(*((s32 *) (work + 8)), (*((s32 *) (work + 0xC))) + 0x200000, (u32) delta, 2U);
    sub_080C31E0(entity, *((void **) (((u8 *) entity) + 0x24)));
  }
}
