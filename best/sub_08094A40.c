extern void sub_080C2E68(void *a, void *b, u32 c);
extern s32 sub_08005820(s32);
extern s32 sub_0800583C(s32);
extern void sub_08091B80(s32, s32, s32, s32, s32);
extern void sub_080C31E0(void *, s32);

void sub_08094A40(void *arg0)
{
    u32 buffer[16];
    u16 *sp44;
    s32 *sp48;
    s32 temp_r0_3;
    s32 temp_r0_2;
    s32 temp_r1_2;
    s32 temp_r3;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r0;
    s32 var_r0;
    s32 var_r7;
    void *temp_r0p;
    void *temp_r1;
    void *temp_r2;

    temp_r2 = *(void **)((u8 *)arg0 + 0x38);
    sp44 = *(u16 **)((u8 *)arg0 + 0xAC);
    temp_r0p = *(void **)((u8 *)arg0 + 0x3C);
    temp_r1 = (u8 *)temp_r0p + 0x34;
    if ((s32) *(s16 *)((u8 *)temp_r1 + 0xC) <= 3) {
        *(u8 *)(*(u8 **)((u8 *)temp_r1 + 4) + 1) = 0;
        *(u8 *)((u8 *)temp_r2 + 0x2A) = 0xBF & *(u8 *)((u8 *)temp_r2 + 0x2A);
    }
    sub_080C2E68(buffer, (void *)0x0810087C, 0x40);
    var_r7 = 0;
    sp48 = (s32 *)((u8 *)buffer + 4);
    do {
        temp_r1_2 = (*(s16 *)((u8 *)temp_r1 + 0xC) * 2) + var_r7;
        var_r0 = temp_r1_2;
        if (temp_r1_2 < 0) {
            var_r0 = temp_r1_2 + 7;
        }
        temp_r0_2 = (temp_r1_2 - ((var_r0 >> 3) * 8)) * 8;
        temp_r4 = *(s32 *)((u8 *)buffer + temp_r0_2);
        temp_r5 = *(s32 *)((u32)sp48 + temp_r0_2);
        temp_r0 = sub_0800583C(0x40000);
        temp_r6 = *(s32 *)((u8 *)temp_r0p + 8);
        temp_r6 += temp_r0;
        temp_r4 = (temp_r4 << 0x13) + 0xFFF40000;
        temp_r6 += temp_r4;
        temp_r0 = sub_0800583C(0x40000);
        temp_r4_2 = *(s32 *)((u8 *)temp_r0p + 0xC);
        temp_r4_2 += temp_r0;
        temp_r5 = (temp_r5 << 0x13) + 0xFFFC0000;
        temp_r4_2 += temp_r5;
        temp_r3 = sub_08005820(0x2000) + 0x800;
        sub_08091B80(temp_r6, temp_r4_2, 0, temp_r3, 0x4000);
        var_r7 += 1;
    } while (var_r7 <= 1);
    temp_r0_3 = (u16) *(s16 *)((u8 *)temp_r1 + 0xC) - 1;
    *(s16 *)((u8 *)temp_r1 + 0xC) = temp_r0_3;
    if ((s32)(temp_r0_3 << 0x10) <= 0) {
        *sp44 |= 4;
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
    }
}
