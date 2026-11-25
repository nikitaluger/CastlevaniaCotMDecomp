extern s32 sub_08007D7C(s32, s32, s32);
extern s32 sub_08012DF4(s32, s32, s32, s32, s32 *, s32 *, s32);
struct R { u16 unk0; s32 unk4; s32 unk8; };
static inline s32 get_base(void) { u8 *p = (u8 *) 0x02025FF0; p += 0x18A8; return (s32) (((u32) (*p) << 6) + 0x02023130); }
void sub_08012870(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, struct R *arg6) {
    s32 spC; s32 sp10; volatile s32 sp14; s32 var_r0; s32 var_r0_2; s32 var_r2; s32 var_r3; s32 var_r5; s32 var_r6; u16 temp_r0; u16 temp_r1;
    sp14 = arg1; var_r5 = arg2; var_r6 = arg3; temp_r0 = (u16) arg5; arg6->unk0 = 0U;
    if (arg4 != 0) {
        if (sub_08012DF4(arg0, sp14 - arg4, var_r5, var_r6, &spC, &sp10, 0xA) == 1) {
            if ((var_r6 < 0) && (0xA & *(u16 *)(0x080CB278 + ((u32)(sub_08007D7C(get_base(), spC, sp10 + 0xFFFF0000) << 0x10) >> 0x0F)))) arg6->unk0 = (u16)(arg6->unk0 | 8);
            if (var_r5 > 0) { var_r0 = get_base(); var_r2 = 0x10000; goto block_9; }
            if (var_r5 < 0) { var_r0 = get_base(); var_r2 = 0xFFFF0000;
block_9:
                if (0xA & *(u16 *)(0x080CB278 + ((u32)(sub_08007D7C(var_r0, spC + var_r2, sp10) << 0x10) >> 0x0F))) arg6->unk0 = (u16)(1 | arg6->unk0); }
            var_r5 = spC - arg0; var_r6 = sp10 - (sp14 - arg4);
        }
    }
    if (sub_08012DF4(arg0, sp14, var_r5, var_r6, &spC, &sp10, (s32)temp_r0) != 0) {
        if (*(u16 *)(0x080CB278 + ((u32)(sub_08007D7C(get_base(), spC, sp10 + 0x10000) << 0x10) >> 0x0F)) & temp_r0) arg6->unk0 = (u16)(4 | arg6->unk0);
        if ((var_r6 < 0) && (*(u16 *)(0x080CB278 + ((u32)(sub_08007D7C(get_base(), spC, sp10 + 0xFFFF0000) << 0x10) >> 0x0F)) & temp_r0)) arg6->unk0 = (u16)(8 | arg6->unk0);
        if (var_r5 > 0) { var_r0_2 = get_base(); var_r3 = 0x10000; goto block_22; }
        if (var_r5 < 0) { var_r0_2 = get_base(); var_r3 = 0xFFFF0000;
block_22:
            if (*(u16 *)(0x080CB278 + ((u32)(sub_08007D7C(var_r0_2, spC + var_r3, sp10) << 0x10) >> 0x0F)) & ~8 & temp_r0) arg6->unk0 = (u16)(1 | arg6->unk0); }
        temp_r1 = arg6->unk0; if (!(9 & temp_r1)) arg6->unk0 = (u16)(4 | temp_r1);
    }
    arg6->unk4 = spC; arg6->unk8 = sp10;
}
