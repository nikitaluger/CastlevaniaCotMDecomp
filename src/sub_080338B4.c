extern void sub_080C31E4(void *, void *, s32);

/* Script-step handler: if the entity's hold flag at +0x7C is set, clear bit
 * 0x40 of the target sprite's +0x2A byte and leave the script where it is;
 * otherwise clear the current command slot's counter and advance the script. */
void sub_080338B4(void *entity) {
    u8 *self = (u8*)entity;
    u8 *target = *(u8**)(self + 0x38);
    if (self[0x7C] != 0) {
        target[0x2A] = (u8)(target[0x2A] & 0xBF);
        return;
    }
    self[*(s16*)(self+0x22)*2 + 0x19] = 0;
    {
        void **advanceCb = (void**)0x08671BC0;
        sub_080C31E4(self + 0x18, self + 0x22, (s32)*advanceCb);
    }
}
