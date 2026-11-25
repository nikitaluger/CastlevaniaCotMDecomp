void sub_080C31E0(void *obj, s32 callback);

/* Once the object's mode byte at +0x6C has reached 3, run its cleanup callback. */
void sub_0809EEA8(void *obj) {
    if (*(u8 *)((u8 *)obj + 0x6C) == 3) {
        sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x24));
    }
}
