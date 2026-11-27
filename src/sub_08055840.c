void sub_08011368(s32, void *, s32, s32);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, s32);
s16 sub_08014938(s32);
s16 getSpriteFacingSign(s32);

void sub_080554E4(void *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x3C);
    u16 *q = (u16 *)(p + 0x48);
    s32 zero = 0;
    void **pp;
    *(u32 *)(p + 0x14) = zero;
    *(u32 *)(p + 0x10) = zero;
    q[3] = 0x3C;
    ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = zero;
    pp = (void **)0x08671BB0;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*pp);
}

void sub_080553D4(void *arg0) {
    void *v38 = *(void **)((u8 *)arg0 + 0x38);
    u8 *p = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *r = p + 0x34;
    sub_08011368((s32)v38, r, 0x02, 0);
    if (2 & *r) {
        s32 zero = 0;
        void **pp;
        *(u16 *)(p + 4) = 0x200 | *(u16 *)(p + 4);
        ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = zero;
        pp = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*pp);
    }
}

void sub_08055840(void *arg0) {
    s32 v38 = *(s32 *)((u8 *)arg0 + 0x38);
    u8 *p = *(u8 **)((u8 *)arg0 + 0x3C);
    u16 *q = (u16 *)(p + 0x48);
    s32 zero = 0;
    void **pp;
    q[3] = 6;
    q[7] = sub_08014938(*(s32 *)(p + 8));
    q[6] = getSpriteFacingSign(v38);
    ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = zero;
    pp = (void **)0x08671BB0;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*pp);
}

void sub_08056DB0(void *arg0, void *arg1, void *arg2, s32 arg3) {
    s32 t = *(s32 *)((u8 *)arg2 + 0x14) + arg3;
    void **pp;
    *(s32 *)((u8 *)arg2 + 0x14) = t;
    pp = (void **)0x08671BFC;
    *(s32 *)((u8 *)arg1 + 8) = *(s32 *)((u8 *)arg0 + 0x4C) + ((*(s32 *)((u8 *)arg2 + 0x18) >> 8) * (sub_080C31E0(t + 0x4000, (s32)*pp) >> 8));
    *(s32 *)((u8 *)arg1 + 0xC) = *(s32 *)((u8 *)arg0 + 0x5C) - ((*(s32 *)((u8 *)arg2 + 0x18) >> 8) * (sub_080C31E0(*(s32 *)((u8 *)arg2 + 0x14), (s32)*pp) >> 8));
}
