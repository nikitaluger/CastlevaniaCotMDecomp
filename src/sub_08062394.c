extern void sub_08062418(u8, u8);

struct S_02021E90 {
    u8 _0[0x1262];
    u16 gfxFlags;
    u8 _1[0x1443 - 0x1264];
    u8 gfxIndex;
};
extern struct S_02021E90 D_02021E90;

struct S_02027A00 {
    u8 _0[0xD8];
    u16 stateFlag;
    u8 counter;
    u8 gfxIndex;
    u8 kind;
    u8 index;
};
extern struct S_02027A00 D_02027A00;

extern volatile u32 D_040000D4[];

// Sets up a DMA copy of graphics data into VRAM, runs the graphics loader and records the new state.
void sub_08062394(u8 kind, u8 index) {
    struct S_02021E90 *p;
    D_040000D4[0] = 0x08442570;
    p = &D_02021E90;
    D_040000D4[1] = 0x06000440 + ((p->gfxFlags & 0x1F00) << 3);
    D_040000D4[2] = 0x80000060;
    (void)D_040000D4[2];
    sub_08062418(kind, index);
    D_02027A00.counter = 0;
    D_02027A00.kind = kind;
    D_02027A00.index = index;
    D_02027A00.stateFlag = 0xF0;
    D_02027A00.gfxIndex = p->gfxIndex;
}
