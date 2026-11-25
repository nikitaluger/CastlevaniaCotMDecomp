extern void sub_0801165C(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/*
 * Step: integrates the entity's velocity (no gravity), and once its 16-frame
 * sub-state counter reaches 0x10, resets the counter and advances the command
 * script.
 */
void sub_080A918C(void *entity) {
    u8 *self = (u8 *)entity;
    sub_0801165C(*(void **)(self + 0x3C), 0);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x10) {
        s32 *scriptTable;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
}
