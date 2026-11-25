/* Sets the periodic signal flag byte at offset +0x8C on a parts object. */
void sub_0809C5E4(void *parts) {
    *(s8 *)((s8 *)parts + 0x8C) = 1;
}
