struct S {
    u8 _0[0x1361];
    u8 f1361;
    u8 _1[2];
    u8 f1364; u8 f1365; u8 f1366; u8 f1367; u8 f1368; u8 f1369;
    u8 f136A; u8 f136B; u8 f136C; u8 f136D; u8 f136E; u8 f136F;
    u8 f1370; u8 f1371; u8 f1372; u8 f1373;
    u8 f1374; u8 f1375; u8 f1376; u8 f1377; u8 f1378; u8 f1379;
    u8 f137A; u8 f137B;
};
struct HW { u8 _0[0x20]; u16 f20; u8 _1[2]; u16 f24; u8 _2[2]; u16 f28; u8 _3[2]; u16 f2C; };
extern struct S D_02021E90;
extern struct HW D_03000830;
extern vu8 D_04000005;

/* Advance the scanline effect state: refresh the active step block, count down
 * its hold time, step the background scroll, copy the effect colors, and
 * program the VCOUNT compare register (0xE3 when idle). */
void sub_080BEC40(void) {
    u8 duration, hold;

    D_02021E90.f1361 = 2;
    duration = D_02021E90.f1364;
    D_02021E90.f1374 = duration;
    D_02021E90.f1375 = D_02021E90.f1366;
    D_02021E90.f1376 = D_02021E90.f1367;
    D_02021E90.f1377 = D_02021E90.f1368;
    D_02021E90.f1378 = D_02021E90.f1369;
    D_02021E90.f1379 = D_02021E90.f136A;
    D_02021E90.f137A = D_02021E90.f136B;
    D_02021E90.f137B = D_02021E90.f136C;
    hold = D_02021E90.f1365;
    if (hold != 0) {
        D_02021E90.f1365 = hold - 1;
    } else {
        D_02021E90.f1365 = duration;
        D_02021E90.f136E = D_02021E90.f136E + D_02021E90.f136A;
    }
    D_02021E90.f1370 = D_03000830.f20;
    D_02021E90.f1371 = D_03000830.f24;
    D_02021E90.f1372 = D_03000830.f28;
    D_02021E90.f1373 = D_03000830.f2C;
    D_02021E90.f136F = D_02021E90.f136E;
    D_02021E90.f136D = D_02021E90.f1375;
    if (D_02021E90.f136D == 0) {
        D_04000005 = 0xE3;
    } else {
        D_04000005 = D_02021E90.f136D - 1;
    }
}
