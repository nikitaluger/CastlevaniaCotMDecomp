extern void *D_020202A8;
void sub_080008A0(void *, s32);

/* Unlink the given object from the global object list and free it. */
void unlinkAndFreeObject(void *arg0) {
    void *entry = arg0;
    void *cur = D_020202A8;
    void *prev = NULL;

    if (cur != NULL) {
        do {
            if (cur == entry) goto found;
            prev = cur;
            cur = *(void **)((u8 *)cur + 0x20);
        } while (cur != NULL);
    }
    return;
found:
    *(u8 *)cur &= 0x7F;
    if (prev == NULL) {
        D_020202A8 = *(void **)((u8 *)cur + 0x20);
    } else {
        *(void **)((u8 *)prev + 0x20) = *(void **)((u8 *)cur + 0x20);
    }
    sub_080008A0(cur, 0x34);
}
