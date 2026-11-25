/* Count the live objects of the given kind in the active-object list at
 * 0x020279D0+4: each node has an object pointer at +0 and the next node at +4,
 * and the object's +4 points at its u16 id (kinds are the id masked with 0x3FFF). */
s32 sub_08016830(u16 kind)
{
  s32 count;
  s8 *listBase;
  void *node;
  count = 0;
  listBase = (s8 *) ((void *) 0x020279D0);
  node = *((void **) (listBase + 4));
  if (node != NULL)
  {
    do
    {
      if ((0x3FFF & (*(*((u16 **) (((s8 *) (*((void **) (((s8 *) node) + 0)))) + 4))))) == ((s16) kind))
      {
        count += 1;
      }
      node = *((void **) (((s8 *) node) + 4));
    }
    while (node != NULL);
  }
  return count;
}
