extern void sub_080111C4(void *ptr);

/* Free the model object referenced by the given sprite's +0x24 field. */
void sub_08011650(void *sprite) {
    sub_080111C4(*(void **)((s8 *)sprite + 0x24));
}
