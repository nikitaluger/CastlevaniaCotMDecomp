void sub_080AC9B4(u8, void *);
void sub_080C31E4(void *, void *, s32);

/* Script step: update the voice state from the data block, then advance the
 * current command once its marker reaches 0x78. */
void sub_080AC334(void *obj) {
    u8 *self = (u8 *)obj;
    u8 *data = *(u8 **)(self + 0x3C);
    sub_080AC9B4(*(u8 *)((u32 *)data + 0x91), data + 0x68);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x78) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
}
