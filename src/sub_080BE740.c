extern s32 scaleByRandom(s32);
extern void sub_080BE70C(s32, s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* Spawn a scatter object: derive two coordinates from a random roll and the
 * given kind, add the per-slot offsets from the two tables in gCameraState
 * indexed by (gMainWorkspace[0x18A8] + 1) << 6, then pass them to sub_080BE70C. */
void sub_080BE740(s32 arg0)
{
  s32 kind;
  char shiftBits;
  s32 roll; s32 scratch; s32 x; s32 y; s32 sum;
  u8 *tableBase; u8 *gameState; s32 slotByte; s32 slotOffset; int offsetBase; s32 ofsUninit;
  s32 *pX; s32 tableX; s32 *pY; s32 tableY;
  shiftBits = 8;
  kind = arg0;
  offsetBase = 0x80 << shiftBits;
  roll = scaleByRandom(0xC8 << 1);
  scratch = roll;
  if (scratch <= 0xEF)
  {
    scratch = scratch << 16;
    roll = kind * 7;
    roll = roll << 18;
    x = scratch - roll;
    y = (s32) 0xFFE40000;
  }
  else
  {
    scratch = scratch - 0xF0;
    roll = -1;
    x = (s32) 0xFFE40000;
    if (kind == roll) { x = 0x86 << 17; }
    if (kind || ofsUninit)
    {
      roll = scratch << 16;
      scratch = (s32) 0xFFE40000;
      y = roll + scratch;
    }
    else
    {
      roll = scratch << 16;
      scratch = (s32) 0xFFE40000;
      y = roll + scratch;
    }
  }
  roll = offsetBase;
  sum = x + roll;
  tableBase = gCameraState;
  gameState = gMainWorkspace;
  slotByte = gameState[0x18A8];
  slotByte = slotByte + 1;
  slotOffset = slotByte << 6;
  ofsUninit = 0x1278;
  pX = (s32 *) ((tableBase + ofsUninit) + slotOffset);
  tableX = *pX;
  x = sum + tableX;
  sum = y + ((s32) 0xFFFF8000);
  roll = 0x127C;
  pY = (s32 *) ((tableBase + roll) + slotOffset);
  tableY = *pY;
  y = sum + tableY;
  scratch = y;
  sub_080BE70C(x, y, kind);
}
