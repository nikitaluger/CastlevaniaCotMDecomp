void sub_080C31E0(void *, s32);

/* Nudge a linked object's sprite position by (-0x30, +8); once both
 * coordinates have passed 0x100, clamp them to 0x100 and dispatch the
 * object's stored callback. */
void sub_0809F38C(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *linked = *(void **)(self + 0x28);
    u8 *pos = *(u8 **)((u8 *)linked + 0x38);
    *(u16 *)(pos + 0x04) -= 0x30;
    linked = (void *)*(vu32 *)(self + 0x28);
    pos = *(u8 **)((u8 *)linked + 0x38);
    *(u16 *)(pos + 0x06) += 0x08;
    linked = (void *)*(vu32 *)(self + 0x28);
    pos = *(u8 **)((u8 *)linked + 0x38);
    if ((s16)*(u16 *)(pos + 0x04) <= 0x100 && (s16)*(u16 *)(pos + 0x06) > 0xFF) {
        *(u16 *)(pos + 0x04) = 0x100;
        linked = (void *)*(vu32 *)(self + 0x28);
        {
            u8 *pos2 = *(u8 **)((u8 *)linked + 0x38);
            *(u16 *)(pos2 + 0x06) = 0x100;
        }
        sub_080C31E0(arg0, *(s32 *)(self + 0x24));
    }
}
