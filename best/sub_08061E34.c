struct S_02027A00_61 { u8 pad[8]; u32 f8; u32 fC; u8 f10; u8 f11; };
extern struct S_02027A00_61 D_02027A00;
struct S_02021E90_61 { u8 pad[0x1278]; u32 v1278; u32 v127C; };
extern struct S_02021E90_61 D_02021E90;
struct S_02025368_61 { u8 pad[0xB0]; u32 words[8]; };
extern struct S_02025368_61 D_02025368;

s32 sub_08061E54(u8 *arg0) {
    u32 x = (u32)*(u8 *)(arg0 + 8) << 8;
    return (x - 2) << 8;
}

void sub_08061E34(void) {
    D_02027A00.f11 = 0;
    D_02021E90.v127C = 0x80 << 10;
    D_02027A00.f8 = 0x80 << 11;
    D_02027A00.fC = 0xA0 << 16;
}

void sub_08061E04(void) {
    D_02027A00.f10 = 0;
    D_02021E90.v1278 = 0xFFF00000;
    D_02027A00.f8 = 0xC0 << 12;
    D_02027A00.fC = 0xC4 << 16;
}

s32 sub_08061D74(u32 arg0) {
    if ((1u << (arg0 & 0x1F)) & D_02025368.words[arg0 >> 5]) return 1;
    return 0;
}
