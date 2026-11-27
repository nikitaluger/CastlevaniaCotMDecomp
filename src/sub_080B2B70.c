extern s32 updateObjectDisplayState(void *, void *);
extern void sub_08013C8C(void *, void *);
extern void sub_080C31E0(void *, void *);

// Linked-object positioning step: copy the linked object's work position into
// our own with a scaled X shift and a fixed Y offset; if the timed display did
// not handle the frame, install a new handler table, bump and bump back the
// script step while dispatching its action, then apply the camera offset.
void sub_080B2B70(void *arg0)
{
  void *sprite;
  void *work;
  void *linkedWork;
  s32 xFactor;
  s32 xDelta;
  sprite = *(void **)((u8 *)arg0 + 0x38);
  work = *(void **)((u8 *)arg0 + 0x3C);
  linkedWork = *(void **)((u8 *)*(void **)((u8 *)*(void **)((u8 *)arg0 + 0x28) + 0x28) + 0x3C);
  xFactor = *(s32 *)((u8 *)arg0 + 0x4C);
  xDelta = ((xFactor * 8) - xFactor) << 0x13;
  *(u32 *)((u8 *)work + 8) = *(u32 *)((u8 *)linkedWork + 8) + xDelta;
  *(u32 *)((u8 *)work + 0xC) = *(u32 *)((u8 *)linkedWork + 0xC) + 0x2C0000;
  if (updateObjectDisplayState(sprite, work) == 0)
  {
    *(u32 *)((u8 *)arg0 + 0x14) = 0x08670328;
    *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) + 1;
    {
      u8 *p = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
      p[0x19] = p[0x19] + 1;
      {
        s32 idx2 = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        u8 *base = (u8 *)arg0 + 0x18;
        u8 b = *(base + idx2);
        void **tbl = *(void **)((u8 *)arg0 + 0x14);
        void *a = tbl[b];
        sub_080C31E0(arg0, a);
      }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) - 1;
  }
  sub_08013C8C(arg0, sprite);
}
