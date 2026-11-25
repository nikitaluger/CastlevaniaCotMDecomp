void sub_08020E78(void *arg0)
{
  s32 ctr = 2;
  u32 zero = 0;
  u32 dead;
  void **p;
  void *t;
  dead = 0;
  p = (*((void ***) (((u8 *) arg0) + 0x3C))) + 0x16;
  do
  {
    t = *p;
    if (t != NULL)
    {
      *((u16 *) (((u8 *) t) + 0x6C)) = (u16) ((*((u16 *) (((u8 *) t) + 0x6C))) | 2);
      *p = (void *) zero;
    }
    p++;
    ctr--;
  }
  while (ctr >= 0);
  (void) dead;
}

