extern void sub_080C2E68(void *, void *, u32);
extern void sub_080C31E0(void *);
extern void *spawnBudgetedEffect(void *, s32);

struct S_02025FF0_1874 { u8 _pad[0x1874]; u32 v; };
extern struct S_02025FF0_1874 gMainWorkspace;
extern u8 gCameraState[];

void sub_0808D690(u32 arg0, u32 *arg1, u32 arg2) {
    u32 v;
    switch (arg0) {
    case 0:
    case 2:
        v = *arg1;
        if (v < arg2) v = 0;
        else v -= arg2;
        *arg1 = v;
        break;
    case 1:
    case 3:
        v = *arg1 + arg2;
        if (v > (0xF0 << 16)) {
            *arg1 = 0xF0 << 16;
            break;
        }
        *arg1 = v;
        break;
    }
}

void sub_0808D640(void *arg0) {
    u8 sp0[4];
    u8 r4 = 0x30;
    u16 *p;
    s32 i;
    u32 mask = 0x80 << 6;
    sub_080C2E68(sp0, (void *)0x080F3E2C, 4);
    p = (u16 *)(gCameraState + (0x93 << 5));
    for (i = 0; i <= 3; i++) {
        if (!(mask & *p)) {
            r4 |= sp0[i];
        }
        p += 0x20;
    }
    *(u8 *)((u8 *)arg0 + 0x38) = r4;
}

void sub_0808D858(void *arg0) {
    if (*(s32 *)0x020213D8 == 0) {
        s32 v = (0x80 << 4) | *(u16 *)((u8 *)arg0 + 2);
        *(u16 *)((u8 *)arg0 + 2) = v;
        *(u32 *)((u8 *)arg0 + 0x14) = 0x0808D88D;
        *(u16 *)((u8 *)arg0 + 0x22) = 1;
        sub_080C31E0(arg0);
    }
}

void *sub_0808DBB4(s32 arg0, s32 arg1, u16 arg2) {
    void *r = spawnBudgetedEffect((void *)gMainWorkspace.v, 0x201);
    if (r != 0) {
        u8 *p;
        *(s32 *)((u8 *)r + 0x4C) = arg0;
        *(s32 *)((u8 *)r + 0x5C) = arg1;
        p = (u8 *)r + 0x6C;
        *(u16 *)p = arg2;
        *(u8 *)(p + 8) = 0;
        return r;
    }
    return NULL;
}
