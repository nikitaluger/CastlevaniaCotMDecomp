/* Set the signed status byte at +0x7C of the given object (paired with sub_080A01D4). */
void sub_080A01CC(void *obj, s8 status) {
    *(s8 *)((s8 *)obj + 0x7C) = status;
}
