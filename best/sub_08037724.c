void sub_080C2E68(void *dst, void *src, s32 len);

void sub_08037724(u8 *arg0, u8 *arg1) {
    u16 sp[16];
    u16 *sptr;
    u16 *p1;
    u32 idx;
    u32 t;
    sub_080C2E68(sp, (void *)0x080CEFD4, 0x20);
    sptr = sp;
    idx = ++arg1[8];
    idx = (idx << 24) >> 25;
    t = 0xF;
    p1 = &sptr[idx & t];
    t = 0x100;
    *(u16 *)(arg0 + 4) = *p1 + t;
    idx = idx + 8;
    p1 = &sptr[idx & 0xF];
    t += *p1;
    *(u16 *)(arg0 + 6) = t;
}
