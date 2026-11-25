void sub_080AC9B4(u8, void *);
void sub_080C31E4(void *, void *, s32);
void sub_0808BBAC(s32, s32, s32);
void _0808D0A4(s32);
void sub_08005E80(s32);
void sub_080B0974(void *);

void sub_080AC278(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *r1 = *(void **)(self + 0x3C);
    sub_080AC9B4(*(u8 *)((u32 *)r1 + 0x91), (u8 *)r1 + 0x68);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x3C) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
}

void sub_080AC334(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *r1 = *(void **)(self + 0x3C);
    sub_080AC9B4(*(u8 *)((u32 *)r1 + 0x91), (u8 *)r1 + 0x68);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x78) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
}

void sub_080AC428(void *arg0) {
    s32 *new_var;
    *((s16 *) 0x05000000) = 0x7FFF;
    sub_0808BBAC(1, 8, 1);
    _0808D0A4(0x10);
    sub_08005E80(0x17E);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    new_var = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *new_var);
}

/* On script action 0x1E: flag the work's linked object, enable all sound
 * channels, queue the (1, 8, 1) request, clear the action byte and advance
 * the script. */
void sub_080AC87C(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *work = *(void **)(self + 0x3C);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x1E) {
        sub_080B0974(*(void **)((u8 *)work + 0xC8));
        *(s16 *)0x05000000 = 0x7FFF;
        sub_0808BBAC(1, 8, 1);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
}
