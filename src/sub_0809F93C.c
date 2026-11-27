void sub_080A0250(s32);
void sub_080C31E4(void *, void *, s32);
extern u32 gScriptStepCallbackTable;

/* Set the work state flag at +0x97, finalize each of the six sub-objects
 * listed at +0x48 and mark every object in the +0x30 list at +0x9C, then reset
 * the script step and advance. */
void sub_0809F93C(u8 *arg0)
{
  u8 *work = *((u8 **) (arg0 + 0x3C));
  u32 i;
  s32 *p;
  void *q;
  u32 *resultTable;
  *((u8 *) (work + 0x97)) = 1;
  i = 0;
  p = (s32 *) (work + 0x48);
  do
  {
    sub_080A0250(*(p++));
    i++;
  }
  while (i <= 5);
  q = *((void **) (arg0 + 0x30));
  resultTable = &gScriptStepCallbackTable;
  if (q != NULL)
  {
    do
    {
      *((u8 *) (((u8 *) q) + 0x9C)) = 1;
      q = *((void **) (((u8 *) q) + 0x2C));
    }
    while (q != NULL);
  }
  *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19)) = 0;
  sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *resultTable);
}
