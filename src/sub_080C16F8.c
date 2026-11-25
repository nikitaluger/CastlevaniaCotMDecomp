/* Script reader: copy the next byte from the stream pointer at +0x40 into the
 * byte field at +0x2E, then advance the pointer. */
inline u32 read_ptr(u8 **dataPtr, int index)
{
  return (u32) dataPtr[index];
}

void sub_080C16F8(void *state)
{
  u8 *bytes;
  u8 **dataPtr = &bytes[0x40];
  u8 byte = dataPtr[0][0];
  bytes[0x2E] = byte;
  dataPtr[0] = (u8 *) (read_ptr(dataPtr, 0) + 1);
  bytes = (u8 *) state;
}
