extern s32 sub_08014990(void *);
extern void sub_0808DBB4(s32, s32, s32);
extern u8 D_080CE9F8[];

/* Spawn a falling effect (initial X velocity 8) at arg1's position plus the
 * 16.16 offset D_080CE9F8[arg2]; mirror the X offset when arg0 faces that way. */
void sub_0802BA40(void *arg0, void *arg1, s32 arg2) {
    u8 *table;
    s32 idx;
    s32 dx;
    s32 dy;
    table = D_080CE9F8;
    idx = arg2 * 8;
    dx = *(u32 *)(table + idx);
    table += 4;
    dy = *(u32 *)(table + idx);
    if (sub_08014990(arg0) > 0) {
        dx = -dx;
    }
    sub_0808DBB4(((s32 *)arg1)[2] + dx, ((s32 *)arg1)[3] + dy, 8);
}

extern u16 D_080CE974[];

void sub_0802A7A4(void *arg0, void *arg1) {
    u16 *r4 = D_080CE974;
    if ((u32)(u16)((u16)((u16 *)arg0)[0x14] - 0x1E) <= 4U) {
        u8 *p = *(u8 **)((s8 *)arg1 + 0x28);
        p[1] = (u8)(0xFA & p[1]);
    }
    if ((u32)(u16)((u16)((u16 *)arg0)[0x14] - 0x0E) <= 0xCU) {
        r4 = D_080CE974 + 0x10;
    }
    ((u16 *)*(u32 **)((s8 *)arg1 + 0x28))[3] = r4[0];
    ((u16 *)*(u32 **)((s8 *)arg1 + 0x28))[4] = r4[1];
    ((u16 *)*(u32 **)((s8 *)arg1 + 0x28))[5] = r4[2];
    ((u16 *)*(u32 **)((s8 *)arg1 + 0x28))[6] = r4[3];
}

extern void sub_080C31E4(void *, void *, s32);
extern u32 gMainObjTimerCallback;

void sub_0802A6CC(void *arg0) {
    void *r4 = *(void **)((s8 *)arg0 + 0x3C);
    setAnimationFrame(*(s32 *)((s8 *)arg0 + 0x38), (s8 *)r4 + 0x34, 5, 0);
    if (2 & *(u8 *)((s8 *)r4 + 0x34)) {
        *(u8 *)((s8 *)arg0 + (s32)(s16)((u16 *)arg0)[0x11] * 2 + 0x19) = 0;
        sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, gMainObjTimerCallback);
    }
}
