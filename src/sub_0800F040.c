extern u8 D_02025368[];
extern u16 D_080CFF2A[];
extern void sub_0800EB44(u16, s32, s32);

/* Loads the three characters' equipped-item tiles into their VRAM slots.
 * Each slot reads an equipment id from the game state; id 0 uses the blank
 * graphic (0x809A), otherwise D_080CFF2A maps the id to a tile index. */
void sub_0800F040(void)
{
  u8 *state = (u8 *) 0x02025368;
  u8 itemId;
  u8 *slot;

  slot = state + 0x306;
  if (*slot != 0)
  {
    sub_0800EB44(D_080CFF2A[*slot], 0x80 << 2, 0xA0 << 1);
  }
  else
  {
    sub_0800EB44(0x809A, 0x80 << 2, 0xA0 << 1);
  }

  slot = state + 0x307;
  itemId = *slot;
  if (itemId != 0)
  {
    sub_0800EB44(D_080CFF2A[itemId], 0x20B, 0xA0 << 1);
  }
  else
  {
    sub_0800EB44(0x809A, 0x20B, 0xA0 << 1);
  }

  slot = state + (0xC2 << 2);
  if (*slot != 0)
  {
    sub_0800EB44(D_080CFF2A[*slot], 0x216, 0xA0 << 1);
  }
  else
  {
    sub_0800EB44(0x809A, 0x216, 0xA0 << 1);
  }
}
