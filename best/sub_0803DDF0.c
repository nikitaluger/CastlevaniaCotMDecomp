extern u16 D_080CF3C4[];
extern u16 D_080CF3CC[];
extern u16 D_080CF3D4[];
void sub_0803DDF0(void *arg0, void *arg1)
{
  u16 *new_var;
  u8 *new_var2;
  u16 *table = D_080CF3C4;
  u32 idx = (*((u16 *) (((u8 *) arg0) + 0x28))) - 8;
  switch (idx)
  {
    case 0:

    case 3:

    case 6:

    case 12:

    case 15:

    case 18:
      table = D_080CF3CC;
      break;

    case 9:
      table = D_080CF3D4;
      break;

  }

  new_var2 = (u8 *) (*((void * volatile *) (((u8 *) arg1) + 0x28)));
  *((u16 *) (new_var2 + 6)) = table[0];
  *((u16 *) (new_var2 + 8)) = table[1];
  new_var = table;
  *((u16 *) (((u8 *) (*((void * volatile *) (((u8 *) arg1) + 0x28)))) + 10)) = new_var[2];
  *((u16 *) (((u8 *) (*((void * volatile *) (((u8 *) arg1) + 0x28)))) + 12)) = table[3];
}

