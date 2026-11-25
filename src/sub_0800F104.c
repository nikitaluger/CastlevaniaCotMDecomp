extern void sub_0800F124(s32 slot);

/* Rebuild all four menu/inventory slots (0 through 3). */
void sub_0800F104(void) {
    sub_0800F124(0);
    sub_0800F124(1);
    sub_0800F124(2);
    sub_0800F124(3);
}
