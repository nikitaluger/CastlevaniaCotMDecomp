struct S_03000830 { u8 _0[4]; u16 f4; u16 f6; };
extern struct S_03000830 D_03000830;
struct Target { u8 _0; u8 f1; u8 _2[8]; u16 fA; u16 fC; };
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 D_02021E90;
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; };
extern struct S_02025FF0 D_02025FF0;
extern u32 sub_080133A4(s32, s32);
extern void *sub_0808E05C(s32, s32, u16, u16);
extern void sub_0809C744(u8);
extern void sub_0809C7B4(s32, s32, u16);
extern s32 _call_via_r1(s32, s32);

void sub_0809AAC8(u8 *arg0) {
    void *sp0;
    void *sp4;
    u16 *sp8;
    s32 temp_r0_3;
    s32 temp_r10;
    s32 var_r2_2;
    s32 var_r7;
    u32 var_r2;
    u32 var_r3;
    u32 i;
    void **var_r1;
    void **var_r4;
    void *temp_r1;
    u32 k;
    u8 *base;

    sp0 = *(void **)(arg0 + 0x38);
    temp_r1 = *(void **)(arg0 + 0x3C);
    sp4 = (u8 *)temp_r1 + 0x48;
    if (*(u8 *)(arg0 + 0x74) != 0) {
        D_03000830.f4 = 0x3F44;
        D_03000830.f6 = 0x60A;
    }
    *(u32 *)((u8 *)temp_r1 + 8) = *(u32 *)(arg0 + 0x4C);
    *(u32 *)((u8 *)temp_r1 + 0xC) = *(u32 *)(arg0 + 0x5C);
    {
        u8 temp_r1_2 = *(u8 *)(arg0 + 0x74);
        sp8 = (u16 *)(arg0 + 0x6C);
        if (*(s8 *)sp4 != temp_r1_2) {
            sub_0809C744(temp_r1_2);
            if (*(s8 *)sp4 == 2) {
                i = 0;
                var_r1 = (void **)((u8 *)sp4 + 4);
                do { *(u8 *)((u8 *)*var_r1 + 1) = 0; var_r1++; i++; } while (i <= 0x31);
            } else if (*(u8 *)(arg0 + 0x74) == 2) {
                i = 0;
                var_r1 = (void **)((u8 *)sp4 + 4);
                do { *(u8 *)((u8 *)*var_r1 + 1) = 1; var_r1++; i++; } while (i <= 0x31);
            }
            *(u8 *)sp4 = *(u8 *)(arg0 + 0x74);
        }
    }
    if (*(u16 *)((u8 *)sp4 + 2) != *sp8) {
        u32 r12, r7;
        s32 *cmd = (s32 *)0x08671BFC;
        var_r4 = (void **)((u8 *)sp4 + 4);
        temp_r10 = _call_via_r1(*sp8 + 0x4000, *cmd);
        temp_r0_3 = _call_via_r1(*sp8, *cmd);
        i = 0;
        var_r3 = temp_r0_3 * 4;
        var_r2 = temp_r10 * 4;
        r12 = temp_r0_3 * 8;
        r7 = temp_r10 * 8;
        do {
            (*(struct Target **)var_r4)->fA = var_r2 >> 16;
            {
                struct Target *tmp = *(struct Target **)var_r4;
                var_r4++;
                tmp->fC = var_r3 >> 16;
            }
            var_r3 += r12;
            var_r2 += r7;
            i++;
        } while (i <= 0x31);
        if (((*(u8 *)(arg0 + 2 * *(s16 *)(arg0 + 0x22) + 0x19) & 3) == 0) && *(u8 *)(arg0 + 0x74) == 2) {
            i = 0;
            var_r2_2 = temp_r0_3 * 4;
            var_r7 = temp_r10 * 4;
            while (i <= 0x9F) {
                if (sub_080133A4(*(s32 *)((u8 *)temp_r1 + 8) + var_r7, *(s32 *)((u8 *)temp_r1 + 0xC) + var_r2_2) != 0) {
                    sub_0808E05C(*(s32 *)((u8 *)temp_r1 + 8) + var_r7, *(s32 *)((u8 *)temp_r1 + 0xC) + var_r2_2, 6, 8);
                    break;
                }
                var_r2_2 += temp_r0_3 * 4;
                var_r7 += temp_r10 * 4;
                i++;
            }
        }
        *(u16 *)((u8 *)sp4 + 2) = *sp8;
    }
    sub_0809C7B4(*(s32 *)((u8 *)temp_r1 + 8), *(s32 *)((u8 *)temp_r1 + 0xC), *sp8);
    base = (u8 *)&D_02021E90;
    k = 0x1278;
    *(u32 *)((u8 *)sp0 + 0x14) = *(s32 *)((u8 *)temp_r1 + 8) - ((*(u32 *)(base + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000);
    k = 0x127C;
    *(u32 *)((u8 *)sp0 + 0x18) = *(s32 *)((u8 *)temp_r1 + 0xC) - ((*(u32 *)(base + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
}
