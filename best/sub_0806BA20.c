struct S_02025368 { u8 pad[0x3BE]; u16 w; };
struct S_02021E90 { u8 pad[0x146E]; u16 w; };
struct S_02025FF0_A { u8 pad[0x24]; u32 flag; u8 pad2[2]; u16 w; };
extern struct S_02025368 gGameStatus;
extern struct S_02021E90 gCameraState;
extern struct S_02025FF0_A gMainWorkspace;
extern u8 D_080E03A0[];

void sub_0806BA20(void *arg0, void *arg1, void *arg2) {
    u8 *p1 = (u8 *)arg1;
    u8 *p2 = (u8 *)arg2;
    struct S_02025368 *p = &gGameStatus;
    struct S_02025FF0_A *q = &gMainWorkspace;
    s32 v3;

    if (q->flag != 0) {
        if ((q->w & p->w) == 0)
            *(u32 *)(p1 + 0x50) = 1;
    } else {
        if ((gCameraState.w & p->w) == 0)
            *(u32 *)(p1 + 0x50) = 1;
    }
    v3 = *(s32 *)(p2 + 0x0C);
    if (v3 < 0 && *(u32 *)(p1 + 0x50) != 0) {
        u8 *tbl = D_080E03A0;
        v3 += *(u32 *)(tbl + *(u32 *)(p1 + 0x44) * 0x58) * 3;
        *(s32 *)(p2 + 0x0C) = v3;
    }
}
