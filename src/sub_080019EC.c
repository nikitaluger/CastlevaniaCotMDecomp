extern void sub_08001978(void *actor);

/* Script command: run the wait-then-advance step only while the current
 * step's flag (self+0x19 + step*2) has bit 0 clear. */
void sub_080019EC(void *arg0)
{
  u8 flag;
  flag = *((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19));
  if (!(flag & 1))
  {
    sub_08001978(arg0);
  }
}
