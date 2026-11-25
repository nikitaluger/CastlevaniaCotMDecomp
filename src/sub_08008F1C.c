void sub_080C31E4(void *, void *, s32);

/* Script delay of 60 frames: once the current command's step counter reaches
 * 0x3C, reset it and dispatch the entity's next script command. */
void sub_08008F1C(void *arg0) {
    u8 *self = (u8 *)arg0;
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x3C) {
        s32 *table;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        table = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *table);
    }
}
