extern s32 updateObjectDisplayState(void *, void *);
extern void syncSpriteToWorldPosition(void *, void *);
extern void sub_080C31E0(void *, void *);
/* Positions a trail slot relative to its parent object, applies its display
 * state, and if that doesn't consume the frame switches it to the follow
 * script and runs its first step; finally refreshes the sprite coordinates. */
void sub_080B28FC(void *arg0)
{
  void *sprite;
  void *work;
  void *parentWork;
  s32 slot;
  s32 offset;
  sprite = *(void **)((u8 *)arg0 + 0x38);
  work = *(void **)((u8 *)arg0 + 0x3C);
  parentWork = *(void **)((u8 *)*(void **)((u8 *)*(void **)((u8 *)arg0 + 0x28) + 0x28) + 0x3C);
  slot = *(s32 *)((u8 *)arg0 + 0x4C);
  offset = ((slot * 8) - slot) << 0x13;
  *(u32 *)((u8 *)work + 8) = *(u32 *)((u8 *)parentWork + 8) + offset;
  *(u32 *)((u8 *)work + 0xC) = *(u32 *)((u8 *)parentWork + 0xC) + 0x2C0000;
  if (updateObjectDisplayState(sprite, work) == 0)
  {
    *(u32 *)((u8 *)arg0 + 0x14) = 0x0867031C;
    *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) + 1;
    {
      u8 *stepBase = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
      stepBase[0x19] = stepBase[0x19] + 1;
      {
        s32 stepOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        u8 *tableBase = (u8 *)arg0 + 0x18;
        u8 step = *(tableBase + stepOffset);
        void **stepTable = *(void **)((u8 *)arg0 + 0x14);
        void *handler = stepTable[step];
        sub_080C31E0(arg0, handler);
      }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) - 1;
  }
  syncSpriteToWorldPosition(arg0, sprite);
}
