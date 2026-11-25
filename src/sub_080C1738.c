/* Script reader: copy the next byte from the stream pointer at +0x40 into the
 * byte field at +0x26, then advance the pointer. */
void sub_080C1738(void *state)
{
    u8 *bytes;
    u8 **dataPtr = &((u8 *)bytes)[0x40];
    u8 byte = dataPtr[0][0];
    ((u8 *)bytes)[0x26] = byte;
    dataPtr[0] = (u8 *)((u32)dataPtr[0] + 1);
    bytes = (u8 *)state;
}
