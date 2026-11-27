extern void *createChildObject(s32, s32);
extern void sub_0800EC20(s32);
extern void sub_0800ECF8(void);
extern void sub_0800EDAC(s32);
extern void sub_0800EF3C(s32);
extern void sub_0800F040(void);
extern void sub_0800F104(void);
extern void sub_0800F1D8(u8, s32);
extern void sub_0800F3C8(u8, s32);
extern u8 gCameraState[];
extern u8 gMenuState[];

void sub_0800D4BC(s32 arg0)
{
    u32 i;
    s32 zero;
    s32 clearZero = 0;
    u8 *base_1;
    u8 *base_2;
    u8 *base_3;
    void **entry;

    base_1 = gMenuState;
    base_1[0x69] = clearZero;
    i = 0;
    base_1 += 0x48;
    do {
        *(u32 *)base_1 = clearZero;
        base_1 += 4;
        i++;
    } while (i <= 6);

    i = 0;
    base_2 = gMenuState;
    entry = (void **)(base_2 + 0x4C);
    for (; i <= 3; i++) {
        entry[0] = createChildObject(arg0, 0x1B);
        ((u8 *)entry[0])[0x3C] = 1;
        ((u8 *)entry++[0])[0x44] = i;
    }

    i = 0;
    base_3 = gMenuState;
    entry = (void **)(base_3 + 0x5C);
    for (; i <= 1; i++) {
        entry[0] = createChildObject(arg0, 0x1B);
        ((u8 *)entry[0])[0x3C] = 3;
        ((u8 *)entry++[0])[0x44] = i;
    }

    zero = 0;
    sub_0800F104();
    sub_0800F1D8(gMenuState[0x6A], 0);
    sub_0800F1D8(gMenuState[0x6A], 1);
    sub_0800F3C8(gMenuState[0x69], 0);
    sub_0800F040();
    sub_0800EF3C(0xFF);

    gCameraState[0xA3 << 5] = zero;
    gCameraState[0x1464] = 0x60;
    gCameraState[0x1462] = 0xF0;
    gCameraState[0x1466] = 0x80;
    gCameraState[0x1468] = 0x3F;
    gCameraState[0x146A] = 0x3D;
    sub_0800ECF8();
    sub_0800EDAC(1);
    sub_0800EC20(0x060072B2);
}
