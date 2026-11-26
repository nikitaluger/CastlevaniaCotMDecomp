struct GameState
{
  u8 pad0[0x24];
  u32 mode;
  u16 pad28;
  u16 faceFlags;
};
struct MoveTableEntry { u8 pad[8]; s32 value; u8 rest[0x4C]; };
extern struct GameState gMainWorkspace;
extern struct MoveTableEntry D_080E03A0[];
extern u16 gCameraState[];

/* Write a facing-dependent table value to the output: the right flag gives
 * +value and clears the flag, the left flag gives -value and sets it. Returns
 * 1 on a match and 0 otherwise. */
s32 sub_08068704(void *selfArg, void *srcArg, void *outArg)
{
  u8 *self = (u8 *) selfArg;
  u8 *src = (u8 *) srcArg;
  u8 *out = (u8 *) outArg;
  struct GameState *gs;
  u32 mode;
  u16 flags;
  u32 newFlags;
  *((u32 *) (out + 8)) = 0;
  mode = gMainWorkspace.mode;
  gs = &gMainWorkspace;
  if (mode != 0)
  {
    if (gs->faceFlags & 0x10) goto right;
    goto check20;
  }
  else if (!(gCameraState[0x146E / 2] & 0x10)) goto check20;
  right:
  *((s32 *) (out + 8)) = D_080E03A0[*((u32 *)(src + 0x44))].value;
  *((u16 *) (self + 2)) &= 0xFFEF;
  return 1;
  check20:
  if (gs->mode != 0)
  {
    if (gs->faceFlags & 0x20) goto left;
    goto ret0;
  }
  else if (!(gCameraState[0x146E / 2] & 0x20)) goto ret0;
  left:
  *((s32 *) (out + 8)) = -D_080E03A0[*((u32 *)(src + 0x44))].value;
  flags = *((u16 *) (self + 2));
  newFlags = 0x10;
  newFlags |= flags;
  *((u16 *) (self + 2)) = newFlags;
  return 1;
  ret0:
  return 0;
}
