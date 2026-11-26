struct S_02021E90_370 {
    u8 pad0[0x143C];
    u8 f143C;
    u8 pad1[7];
    u8 f1444;
    u8 pad2[0xF];
    u32 f1454;
    u8 pad3[4];
    u8 f145C;
};
extern struct S_02021E90_370 gCameraState;

void sub_08060370(void) {
    u8 t;
    gCameraState.f1454 += 1;
    t = gCameraState.f145C | 4;
    gCameraState.f145C = t;
    if (t & 2) {
        gCameraState.f145C = t & 0xFD;
        gCameraState.f143C = gCameraState.f1444;
    }
}
