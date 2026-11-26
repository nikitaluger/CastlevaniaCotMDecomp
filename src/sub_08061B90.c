struct S_02025368
{
  u8 _0[0x94];
  u8 patternIndex;
  u8 patternOffset;
  u8 _1[0xAC - 0x96];
  u16 placedCount;
};
extern struct S_02025368 gGameStatus;
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u32 D_0866EB08[];
s32 sub_08061C9C(s32, s32);
void sub_08061D30(s32, s32);

/* Procedural decoration: at a fixed-point map position, look up a tile offset from
   the active pattern, mark it in the occupancy bitmap if the tile is free, and
   count successful placements. */
void sub_08061B90(s32 x, s32 y)
{
  u8 **pfPtr;
  struct S_02025368 *state = &gGameStatus;
  if ((x >= 0) && (y >= 0))
  {
    u8 *coordTable = gCameraState;
    u8 *roomIdx = gMainWorkspace;
    u32 tableIdx;
    roomIdx += 0x18A8;
    tableIdx = (((u32) (*roomIdx)) + 1) << 6;
    coordTable += tableIdx;
    {
      s32 maxX = (*((s16 *) (coordTable + 0x1270))) << 21;
      if (x < maxX)
      {
        s32 maxY = (*((s16 *) (coordTable + 0x1272))) << 21;
        if (y < maxY)
        {
          u32 tileTableBase = (u32) D_0866EB08;
          u8 *patternPtr = ((u8 *) state) + 0x94;
          u32 *tileList = (u32 *) (((*patternPtr) << 2) + tileTableBase);
          u8 tileOffset;
          u8 *tilePair;
          s32 tileX;
          patternPtr++;
          tileOffset = *(*(pfPtr = &patternPtr));
          tilePair = ((u8 *) (*tileList)) + (tileOffset << 1);
          tileX = (x >> 24) + tilePair[0];
          y = (y >> 24) + tilePair[1];
          if (sub_08061C9C(tileX, y) == 0)
          {
            sub_08061D30(tileX, y);
            if (sub_08061C9C(tileX, y) != 0)
            {
              state->placedCount += 1;
            }
          }
        }
      }
    }
  }
}
