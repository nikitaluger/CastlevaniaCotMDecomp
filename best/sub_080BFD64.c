extern u8 *sub_080BFBEE(u8 *, void *, u8 *);
void sub_080BFD64(void *arg0, void *arg1)
{
  u8 *p = *((u8 **) (((u8 *) arg1) + 0x40));
  u8 v = p[0];
  u8 new_var;
  u8 *np = p + 1;
  u8 *dst = sub_080BFBEE(((u8 *) 0x04000060) + v, arg1, np);
  *dst = new_var;
  new_var = v;
}

