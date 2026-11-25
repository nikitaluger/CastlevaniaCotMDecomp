void sub_0802B178(void *a, void *b)
{
  u8 *new_var;
  u16 *data = (u16 *) 0x080CE9C0;
  u16 idx = *((u16 *) (((u8 *) a) + 0x28));
  void * volatile *pp;
  switch (idx)
  {
    break;
    case 10:
      data = (u16 *) 0x080CE9C8;

    case 13:
      data = (u16 *) 0x080CE9D0;
      break;

    case 16:

    case 20:
      data = (u16 *) 0x080CE9D8;
      break;

    case 0:
      data = (u16 *) 0x080CE9E0;

  }

  pp = (void * volatile *) (((u8 *) b) + 0x28);
  idx = 0x0C;
  *((u16 *) (((u8 *) (*pp)) + 0x06)) = data[0];
  *((u16 *) (((u8 *) (*pp)) + 0x08)) = data[1];
  new_var = (u8 *) (*pp);
  *((u16 *) (new_var + 0x0A)) = data[2];
  *((u16 *) (new_var + idx)) = data[3];
}

