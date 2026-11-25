/* Add the 16-bit x/y/z triple `delta` into the triple at `pos` in place. */
inline int add_y(void *delta, void *pos)
{
  return (*((u16 *) (((s8 *) delta) + 2))) + (*((u16 *) (((s8 *) pos) + 6)));
}

void sub_08003A84(void *delta, void *pos)
{
  long add;
  add = *((u16 *) (((s8 *) pos) + 4));
  *((u16 *) (((s8 *) pos) + 4)) = (u16) ((*((u16 *) (((s8 *) delta) + 0))) + add);
  *((u16 *) (((s8 *) pos) + 6)) = (u16) add_y(delta, pos);
  add = *((u16 *) (((s8 *) pos) + 8));
  *((u16 *) (((s8 *) pos) + 8)) = (*((u16 *) (((s8 *) delta) + 4))) + add;
}
