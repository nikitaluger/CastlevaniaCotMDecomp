extern u8 gGameStatus[];
struct S_02025FF0
{
  u8 _0[0x14ED];
  u8 f14ED;
  u8 _1[0x150C - 0x14EE];
  u32 f150C;
};
extern struct S_02025FF0 gMainWorkspace;
extern s32 D_080DFFB0[];

/* Advance a scrolling background by the per-room speed in D_080DFFB0,
 * limited to the remaining distance in gMainWorkspace.f150C. */
void advanceRoomScroll(u8 *self, s32 speedIndex)
{
  u8 *scroll = gGameStatus;
  u8 *speedTbl;
  s32 *pRemain;
  s32 colBase;
  s32 off;
  u16 *pPos;
  s16 room;

  if (*(u16 *)(self + 0x84) != 0)
  {
    return;
  }
  if (gMainWorkspace.f14ED == 0xA6)
  {
    pRemain = &gMainWorkspace.f150C;
    speedTbl = (u8 *) D_080DFFB0;
    colBase = speedIndex << 2;
    room = *(s16 *)(scroll + 0x8C);
    off = colBase + room * 20;
    if (*pRemain >= *(s32 *)(speedTbl + off))
    {
      *(s32 *)(scroll + 0x2CC) -= (*(s32 *)(speedTbl + off) * 5) << 16;
    }
    else
    {
      *(s32 *)(scroll + 0x2CC) -= (*pRemain * 5) << 16;
      pPos = (u16 *)(scroll + 0x2D4);
      off = colBase + (*(s16 *)(scroll + 0x8C)) * 20;
      *pPos -= *(s32 *)(speedTbl + off) - *pRemain;
    }
  }
  else
  {
    *(u16 *)(scroll + 0x2D4) -= D_080DFFB0[*(s16 *)(scroll + 0x8C) * 5 + speedIndex];
  }
}
