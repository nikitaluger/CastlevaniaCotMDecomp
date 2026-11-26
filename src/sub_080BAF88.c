void sub_080BB984(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct S_02021E90_all {
    u8 _0x000[0x125C];
    u32 v;
    u8 _pad0[0x1361 - 0x1260];
    u8 f1361;
    u8 _pad1[2];
    u16 f1364;
    u16 f1366;
    u8 f1368;
    u8 f1369;
    u8 _pad2[0x1458 - 0x136A];
    u8 f1458;
};
extern struct S_02021E90_all gCameraState;

struct S_03000830 { u8 _0x000[4]; u16 a; u8 _pad[2]; u16 b; };
extern struct S_03000830 D_03000830;

/* Run one step of the entity's command script; command 0xF0 clears the current
 * command byte and reloads the script from the default command table. */
void sub_080BAF88(void *arg0) {
    u8 *obj = (u8 *)arg0;
    void *res = *(void **)(obj + 0x3C);
    sub_080BB984(res, (u8 *)res + 0x48);
    if (*(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) == 0xF0) {
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit;
            lit = (s32 *)0x08671BB0;
            sub_080C31E4(obj + 0x18, obj + 0x22, *lit);
        }
    }
}

void sub_080BEDBC(void) {
    gCameraState.f1361 = 3;
    gCameraState.f1364 = D_03000830.a;
    gCameraState.f1366 = D_03000830.b;
    gCameraState.f1368 = gCameraState.f1458;
    gCameraState.f1369 = 0x50;
    *(vu8 *)0x04000005 = 0xE3;
}

void sub_080BEE14(void) {
    gCameraState.f1361 = 3;
    gCameraState.f1364 = D_03000830.a;
    gCameraState.f1366 = D_03000830.b;
    gCameraState.f1368 = gCameraState.f1458;
    gCameraState.f1369 = 0x48;
    *(vu8 *)0x04000005 = 0xE3;
}

void sub_080BEF60(void) {
    u8 *base = (u8 *)&gCameraState;
    u32 r2;
    base[0x1361] = 7;
    r2 = base[0x1364];
    base[0x1366] = r2;
    base[0x1367] = base[0x1365];
    if ((r2 << 24) == 0)
        *(vu8 *)0x04000005 = 0xE2;
    else
        *(vu8 *)0x04000005 = r2 - 1;
}
