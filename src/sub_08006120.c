extern u8 D_080C98C0[];     /* per-player "enabled" flags */
extern u8 D_0200A268[];     /* per-player "already started" flags */
extern u32 D_08106DCC[];    /* sound-player table, 3 words per slot */
extern u8 D_00000009[];     /* address 9 doubles as the slot count */
extern void sub_080C0B70(void *);   /* start a music/sound player */

/* Start every enabled sound player (D_080C98C0) that has not been started yet
 * (D_0200A268); a player whose status word at +4 already has bit 31 set is left
 * alone. */
void sub_08006120(void)
{
  u32 i;
  u32 *entry;
  u32 count;
  u16 n;
  i = 0;
  n = (u32)D_00000009;
  if (i < n)
  {
    count = n;
    entry = D_08106DCC;
    do
    {
      if (D_080C98C0[i] != 0)
      {
        u8 *started = &D_0200A268[i];
        u8 state = *started;
        if (state == 0)
        {
          s32 *player = (s32 *) (*entry);
          if (player[1] < 0)
          {
            *started = state;
          }
          else
          {
            sub_080C0B70((void *) player);
            *started = 1;
          }
        }
      }
      entry += 3;
      i++;
    }
    while (i < count);
  }
}
