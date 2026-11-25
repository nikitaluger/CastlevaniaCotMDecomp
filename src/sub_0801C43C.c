void sub_0801C4BC(void *obj);
void sub_080C31E0(void *obj, s32 callback);

/* Detach the object from its parent and run its cleanup callback, taken from
 * its display state at +0x3C. */
void sub_0801C43C(void *obj) {
    void *state;

    state = *(void **)((u8 *)obj + 0x3C);
    sub_0801C4BC(obj);
    sub_080C31E0(obj, *(s32 *)((u8 *)state + 0x24));
}
