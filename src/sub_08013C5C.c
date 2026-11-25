/* Give the sprite the entity's high-nibble flag value (its palette/variant:
 * work->f22 + 8) while keeping the low 12 bits (tile index), and mark the
 * entity's linked sub-object (+0x28) as active. */
void sub_08013C5C(void *entity, u16 *sprite)
{
  u16 newFlags;
  void *work;
  void *subObj;
  work = *((void **) (((s8 *) entity) + 0x3C));
  subObj = *((void **) (((s8 *) work) + 0x28));
  if (subObj != NULL)
  {
    newFlags = 5 | (*((u8 *) (((s8 *) subObj) + 1)));
    *((u8 *) (((s8 *) subObj) + 1)) = (u8) newFlags;
  }
  *sprite = (0xFFF & (*sprite)) | (((*((u16 *) (((s8 *) work) + 0x22))) + 8) << 0xC);
}
