/* Sets the one-shot signal flag byte at offset +0x7C on a parts/effect object. */
void sub_0809C5F4(void *parts) {
    *(s8 *)((s8 *)parts + 0x7C) = 1;
}
