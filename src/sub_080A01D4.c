/* Return the signed status byte at +0x7C of the given object. */
s8 sub_080A01D4(void *obj) {
    return (s8) *(u8 *)((s8 *)obj + 0x7C);
}
