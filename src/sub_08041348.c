extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_080113A8(s32, void *);

/* Script-step handler: run the sprite animation, and when this command slot's
 * counter reaches 30, clear it and jump the script to the callback in the
 * 0x08671BD0 table. */
void sub_08041348(void *entity) {
    u8 *self = (u8 *)entity;
    s32 *scriptCb;
    sub_080113A8(*(s32 *)(self + 0x38), (u8 *)*(void **)(self + 0x3C) + 0x34);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x1E) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptCb = (s32 *)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 0, *scriptCb);
    }
}
