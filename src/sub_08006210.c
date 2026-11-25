/* Copy the 16-bit value at 0x0200A278 into the global's field at +0x14DE,
 * then set the adjacent field at +0x14E0 to 0x10. */
void sub_08006210(void) {
    u8 *base;
    u16 *src;
    u16 value;
    u32 firstOff, secondOff;

    base = (u8 *)0x02025FF0;
    src = (u16 *)0x0200A278;
    firstOff = 0x14DE;
    secondOff = 0xA7 << 5;
    value = *src;
    *(u16 *)(base + firstOff) = value;
    *(u16 *)(base + secondOff) = 0x10;
}
