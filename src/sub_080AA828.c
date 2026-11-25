extern void sub_080AA8A0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/*
 * Step: updates the attached object through the common helper, and once its
 * 12-frame sub-state counter is used up, resets the counter and advances the
 * command script.
 */
void sub_080AA828(void *entity) {
    u8 *self = (u8 *)entity;
    void *attached = *(void **)(self + 0x3C);

    sub_080AA8A0(entity, attached);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0xC) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *scriptTable = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
        }
    }
}
