void sub_080BB8AC(void **ptr_array) {
    u32 i = 0;
    do {
        void *p = ptr_array[i];
        *(u8 *)((u8 *)p + 1) = 0;
        i++;
    } while (i <= 4);
}
