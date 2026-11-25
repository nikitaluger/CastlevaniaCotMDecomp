/* Disable the three graphic frame entries pointed to by the slots at +0, +4
 * and +8 by clearing each entry's +1 flag byte. */
void sub_0803B1A4(void *arg0) {
    void **list = (void **)arg0;
    *(u8 *)((u8 *)list[0] + 1) = 0;
    *(u8 *)((u8 *)list[1] + 1) = 0;
    *(u8 *)((u8 *)list[2] + 1) = 0;
}
