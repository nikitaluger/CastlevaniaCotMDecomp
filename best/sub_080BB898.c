void sub_080BB898(void **ptr_array) {
    u32 i;
    void **p;
    i = 0;
    while (i <= 4) {
        p = ptr_array + i;
        *(u8 *)((u8 *)*p + 1) = 1;
        i++;
    }
}
