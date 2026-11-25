/* Count the objects on the manager's list whose kind (the field at obj+4,
 * masked to 14 bits) equals id. */
s32 sub_0801686C(u16 id)
{
  s8 *manager;
  s32 count;
  void *node;
  count = 0;
  manager = (s8 *) ((void *) 0x020279D0);
  node = *((void **) (manager + ((unsigned int) 8)));
  if (node != NULL)
  {
    do
    {
      if ((0x3FFF & (*(*((u16 **) (((s8 *) (*((void **) (((s8 *) node) + 0)))) + 4))))) == ((s16) id))
      {
        count += 1;
      }
      node = *((void **) (((s8 *) node) + 4));
    }
    while (node != NULL);
  }
  return count;
}
