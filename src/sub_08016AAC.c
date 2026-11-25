extern void sub_080008A0(void *dst, u32 size);

/* Release an object's memory by zeroing its first 20 bytes. */
void sub_08016AAC(void *object) {
    sub_080008A0(object, 0x14);
}
