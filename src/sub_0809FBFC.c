void sub_080A0250(s32 subObj);
void sub_080C31E0(void *obj, s32 callback);

/* Finalize the sub-object held at +0x4C, then run the object's own cleanup
 * callback. */
void sub_0809FBFC(void *obj) {
    sub_080A0250(*(s32 *)((u8 *)obj + 0x4C));
    sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x24));
}
