/* Clears the two movement-state flag bytes at offsets +4 and +5. */
void sub_0803B0D0(void *moveState) {
    *(s8 *)((s8 *)moveState + 5) = 0;
    *(s8 *)((s8 *)moveState + 4) = 0;
}
