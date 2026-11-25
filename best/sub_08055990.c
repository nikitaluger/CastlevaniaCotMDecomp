extern u16 D_080CFB70[];
struct Inner_55990
{
  u8 pad[6];
  u16 a;
  u16 b;
  u16 c;
  u16 d;
};
struct Outer_55990
{
  u8 pad[0x28];
  struct Inner_55990 * volatile ptr;
};
void sub_08055990(void *arg0, void *arg1)
{
  struct Outer_55990 *new_var;
  struct Inner_55990 *d;
  arg1 = (u8 *) D_080CFB70;
  switch (*((u16 *) (((u8 *) arg0) + 0x28)))
  {
    case 0:
      arg1 += 8;
      break;

    case 3:
      arg1 += 0x10;
      break;

  }

  new_var = (struct Outer_55990 *) arg1;
  d = new_var->ptr;
  d->a = *((u16 *) (arg1 + 0));
  d = ((struct Outer_55990 *) arg1)->ptr;
  d->b = *((u16 *) (arg1 + 2));
  d = ((struct Outer_55990 *) arg1)->ptr;
  d->c = *((u16 *) (arg1 + 4));
  ;
  ((struct Outer_55990 *) arg1)->ptr->d = *((u16 *) (arg1 - (-6)));
}

