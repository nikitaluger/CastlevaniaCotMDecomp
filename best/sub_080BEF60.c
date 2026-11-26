struct S_02021E90_b {
    u8 _0x000[0x125C];
    u32 v;
    u8 _pad0[0x1361 - 0x1260];
    u8 f1361;
    u8 _pad1[2];
    u8 b1364;
    u8 b1365;
    u8 b1366;
    u8 b1367;
};
extern struct S_02021E90_b gCameraState;

void sub_080BEF60(void) {
    u8 r2, r1;
    gCameraState.f1361 = 7;
    r2 = gCameraState.b1364;
    gCameraState.b1366 = r2;
    r1 = gCameraState.b1365;
    gCameraState.b1367 = r1;
    if (r2 == 0)
        *(vu8 *)0x04000005 = 0xE2;
    else
        *(vu8 *)0x04000005 = r2 - 1;
}
