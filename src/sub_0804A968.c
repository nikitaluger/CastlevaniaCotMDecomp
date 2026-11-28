struct MwFieldView {
    u8 _0[0x174C];
    s32 f174C;
    s32 f1750;
};
extern struct MwFieldView gMainWorkspace;

extern s32 sub_0801459C(void *, s32);
extern void setSpriteFlipForDirection(void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
void sub_0804A968(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *sprite = *((u8 **) (self + 0x38));
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *animState = work + 0x34;
  u8 *moveState = work + 0x48;
  u32 *scriptTable;
  u8 *actionList;
  u8 *scriptIndexPtr;
  if (sub_0801459C(work, 0x700000) == 0)
  {
    return;
  }
  if ((*((s32 *) (work + 0xC))) >= gMainWorkspace.f1750)
  {
    return;
  }
  *((u32 *) (work + 0x14)) = 0xC000;
  if ((*((s32 *) (work + 8))) > gMainWorkspace.f174C)
  {
    *((u32 *) (work + 0x10)) = 0xFFFFA000;
    *((u32 *) (moveState + 8)) = 0xFFFFFA00;
  }
  else
  {
    *((u32 *) (work + 0x10)) = 0x6000;
    *((u32 *) (moveState + 8)) = 0x600;
    *((u16 *) (sprite + 2)) |= 0x10;
  }
  setSpriteFlipForDirection(sprite, *((void **) (work + 0x10)));
  setAnimationFrame(sprite, animState, 2, 1);
  {
    s16 step = *((s16 *) (self + 0x22));
    *((u8 *) (step * 2 + self + 0x19)) = 0;
  }
  scriptTable = (u32 *) 0x08671BB0;
  actionList = self + 0x18;
  scriptIndexPtr = self + 0x22;
  sub_080C31E4(actionList, scriptIndexPtr, (void *) (*scriptTable));
  {
    s16 step = *((s16 *) (self + 0x22));
    (*((u8 *) (step * 2 + self + 0x19)))++;
    step = *((s16 *) (self + 0x22));
    actionList += step * 2;
    {
      u8 b = *actionList;
      void **tbl = (void **) *((u32 *) (self + 0x14));
      sub_080C31E0(self, tbl[b]);
    }
  }
}
