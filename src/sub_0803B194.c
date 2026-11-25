/* Enable the three graphic frame entries pointed to by the slots at +0, +4
 * and +8 by setting each entry's +1 flag byte to 1. */
void sub_0803B194(void *arg0) {
    void **list = (void **)arg0;
    *(u8 *)((u8 *)list[0] + 1) = 1;
    *(u8 *)((u8 *)list[1] + 1) = 1;
    *(u8 *)((u8 *)list[2] + 1) = 1;
}
