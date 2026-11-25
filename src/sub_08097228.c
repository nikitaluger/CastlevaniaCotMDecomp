extern void sub_0801604C(s32 obj);

/* Callback wrapper: forward the object pointer in the second argument to
 * sub_0801604C; the first argument is unused. */
void sub_08097228(s32 unused, s32 object) {
    sub_0801604C(object);
}
