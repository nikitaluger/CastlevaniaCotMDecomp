extern s32 sub_08014990(void *);
extern void sub_0808DBB4(s32, s32, s32);
extern void setAnimationFrame(s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_080CEA40[];
extern u8 D_080CEAA8[];
extern u8 D_080CEAE0[];
extern u32 gScriptStepCallbackTable;

void sub_0802C6D4(void *arg0, void *arg1, s32 arg2) {
    u8 *base;
    s32 idx;
    s32 r4;
    s32 r5;
    base = D_080CEA40;
    idx = arg2 * 8;
    r4 = *(u32 *)(base + idx);
    base += 4;
    r5 = *(u32 *)(base + idx);
    if (sub_08014990(arg0) > 0) {
        r4 = -r4;
    }
    sub_0808DBB4(((s32 *)arg1)[2] + r4, ((s32 *)arg1)[3] + r5, 8);
}

void sub_0802D2E8(void *arg0, void *arg1, s32 arg2) {
    u8 *base;
    s32 idx;
    s32 r4;
    s32 r5;
    base = D_080CEAA8;
    idx = arg2 * 8;
    r4 = *(u32 *)(base + idx);
    base += 4;
    r5 = *(u32 *)(base + idx);
    if (sub_08014990(arg0) > 0) {
        r4 = -r4;
    }
    sub_0808DBB4(((s32 *)arg1)[2] + r4, ((s32 *)arg1)[3] + r5, 8);
}

/* Spawn a falling effect (initial X velocity 8) at arg1's position plus the
 * 16.16 offset D_080CEAE0[arg2]; mirror the X offset when arg0 faces that way. */
void sub_0802DEA8(void *arg0, void *arg1, s32 arg2) {
    u8 *table;
    s32 idx;
    s32 dx;
    s32 dy;
    table = D_080CEAE0;
    idx = arg2 * 8;
    dx = *(u32 *)(table + idx);
    table += 4;
    dy = *(u32 *)(table + idx);
    if (sub_08014990(arg0) > 0) {
        dx = -dx;
    }
    sub_0808DBB4(((s32 *)arg1)[2] + dx, ((s32 *)arg1)[3] + dy, 8);
}

void sub_0802A4E0(void *arg0) {
    u8 *p = (u8 *)arg0;
    s32 v38 = *(s32 *)(p + 0x38);
    u8 *q = *(u8 **)(p + 0x3C);
    u8 *r4 = q + 0x34;
    void **pp;

    setAnimationFrame(v38, r4, 0x0D, 0);
    if (*r4 & 2) {
        if (sub_08014990(v38) > 0) {
            *(s32 *)(q + 0x10) = 0x8000;
        } else {
            *(s32 *)(q + 0x10) = (s32)0xFFFF8000;
        }
        *(u8 *)(p + *(s16 *)(p + 0x22) * 2 + 0x19) = 0;
        pp = (void **)0x08671BB0;
        sub_080C31E4(p + 0x18, p + 0x22, (s32)*pp);
    }
}
