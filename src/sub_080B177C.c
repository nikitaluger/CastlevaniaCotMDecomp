void sub_08005E80(s32);
void sub_08098664(s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Ensure the object is in animation mode 4; at script step 0x1E play sound
 * 0x186, clear the step and advance the script. */
void sub_080B177C(void *arg0)
{
  int soundId;
  s32 *stepTable;
  sub_08098664(*(s32 *)((u8 *)arg0 + 0x4C), 4, 0);
  soundId = 0x186;
  if (*(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) == 0x1E)
  {
    sub_08005E80(soundId);
    *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = 0;
    stepTable = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *stepTable);
  }
}
