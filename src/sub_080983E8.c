/* Undo the temporary +8 applied to the sprite attribute's high nibble: keep
 * the low 12 bits and subtract 8 from bits 12..15. */
void sub_080983E8(u16 *attr) {
    u16 value;

    value = *attr;
    *attr = (0xFFF & value) | (((value >> 0xC) - 8) << 0xC);
}
