/* Compute the checksum of a 0x3D0-byte save block: sum all its bytes, then
 * subtract the stored checksum byte at offset 9, leaving the sum of every
 * other byte. Used both to fill byte 9 and to validate a saved block. */
u8 sub_08010490(u8 *block) {
    u8 sum = 0;
    u8 *p = block;
    u32 i;
    for (i = 0; i <= 0x3CFu; i++) {
        sum = (u8)(sum + p[i]);
    }
    sum = (u8)(sum - block[9]);
    return sum;
}
