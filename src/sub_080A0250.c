extern void sub_080C31E0(void *, s32);

/* Finalize one sub-object: if its flag byte at +0x6C is clear, hand it and the
 * value saved at +0x24 to the release handler; otherwise mark it released (4). */
void sub_080A0250(void *obj) {
    u8 *self = (u8 *)obj;

    if (self != NULL) {
        if (*(u8 *)(self + 0x6C) == 0) {
            sub_080C31E0(obj, *(s32 *)(self + 0x24));
            return;
        }
        *(u8 *)(self + 0x6C) = 4U;
    }
}
