void sub_08011368(s32, void *, s32, s32);
void sub_080B9818(s32, s32);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);

void sub_080B80D4(void *arg0) {
    u8 *self = (u8 *)arg0;
    s16 idx = *(s16 *)(self + 0x22);
    u8 *p = self + idx * 2;
    if (*(u8 *)(p + 0x19) == 8) {
        s32 *litp;
        *(u8 *)(p + 0x17) = 0;
        litp = (s32 *)0x08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 1, *litp);
    }
}

/* Releases the entity's held part: resets the animator to frame 0, clears the
 * part frame fields, marks the linked pose state, then clears the script step
 * byte and advances to the next handler. */
void sub_080B7B28(void *entity) {
    u8 *self = (u8 *)entity;
    s32 sprite = *(s32 *)(self + 0x38);
    void *work = *(void **)(self + 0x3C);
    void *animState = (u8 *)work + 0x34;
    void *pose = (u8 *)work + 0x48;
    sub_08011368(sprite, animState, 0, 0);
    {
        u8 *part = *(u8 **)((u8 *)work + 0x28);
        u8 zero = 0;
        part[1] = zero;
        *(u8 *)(*(u8 **)((u8 *)pose + 4) + 1) = zero;
        sub_080B9818(*(s32 *)((u8 *)work + 0x48), *(s32 *)((u8 *)work + 8));
        *(u8 *)(self + (*(s16 *)(self + 0x22) * 2) + 0x19) = zero;
        {
            s32 *scriptCb = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptCb);
        }
    }
}
