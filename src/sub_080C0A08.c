/* If the multiboot handshake structure pointed to by 0x03007FF0 is valid,
 * write 0xB600 to two I/O registers, clear its flag byte and decrement its
 * magic word. */
void sub_080C0A08(void)
{
  u32 *mbInfo = *((u32 **) 0x03007FF0);
  u32 magic = mbInfo[0];
  if (magic != 0x68736D53)
  {
    vu16 *ioReg = (vu16 *) 0x040000C6;
    u32 val = 0xB600;
    ioReg[0] = (u16) 0xB600;
    ioReg = ioReg + 6;
    ioReg[0] = (u16) 0xB600;
    (void) ((vu8 *) mbInfo)[4];
    ((vu8 *) mbInfo)[4] = 0;
    mbInfo[0] = magic - 10;
  }
}
