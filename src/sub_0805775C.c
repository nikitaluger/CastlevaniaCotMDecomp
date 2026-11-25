void sub_080C31F4(void *);
void sub_0805779C(void);

/* Copy the source object's four trail entries (words at +0x5C/+0x6C and a
 * halfword at +0x7C) into the effect's entry tables, then install the
 * follow-up update callback and restart the object's script. */
void sub_0805775C(void *arg0)
{
  u8 *obj = (u8 *) arg0;
  void *work = *((void **) (obj + 0x3C));
  u32 i = 0;
  void (*nextUpdate)(void) = sub_0805779C;
  u16 *half = (u16 *) (((u8 *) work) + 0x24);
  u32 *word = (u32 *) (((u8 *) work) + 4);
  do
  {
    u8 *source = (u8 *)*(vu32 *)(obj + 0x28);
    word[0] = *((u32 *) (source + 0x5C));
    word[4] = *((u32 *) (source + 0x6C));
 do { *half = (u16) (*((u32 *) (source + 0x7C))); } while (0);
    half++;
    word++;
    i++;
  }
  while (i <= 3);
  *((u32 *) (obj + 0x14)) = (u32) nextUpdate;
  *((u16 *) (obj + 0x22)) = 1;
  sub_080C31F4(obj);
}
