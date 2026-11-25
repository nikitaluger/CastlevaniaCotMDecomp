/* Draws the status HUD: two fixed-point gauges rendered as digit sprites, a name/icon
 * plate, and a timed message banner. */
struct S_02021E90 { u8 _0[8]; u32 flags; u8 _0C[0x1256]; u16 gfxTileBase; };
struct S_02027A00 { u8 _0[0xD8]; u16 bannerTimer; u8 bannerState; };
extern struct S_02021E90 D_02021E90;
extern struct S_02027A00 D_02027A00;
extern u8 D_080DD2DC[];
extern u8 D_080DBE28[];
volatile int sub_08000E98(void *a, void *b, void *c, u32 d, u32 e);
void sub_08062484(void);
s32 sub_080C2F20(s32, s32);
void sub_08062118(void) {
    s32 *stats = (s32 *)0x02025368;
    s32 value, value2, percent;
    u8 *iconIndex;
    value = stats[0xB1]; if (value < 0) value = 0;
    percent = sub_080C2F20(100 * ((u32)value >> 8), stats[0xB2] >> 8);
    sub_08000E98((void*)1, (void*)(0x080DBE58 + percent*26), (void*)(((D_02021E90.gfxTileBase & 0x1F00) << 3) + 0x06000002), 0x1A, 0x10);
    if (*(u8*)((u8*)stats + 0x2DA) == 0 || (D_02021E90.flags & 0x10)) sub_08000E98((void*)1, (void*)0x08442438, (void*)0x05000020, 0x20, 0x10);
    else sub_08000E98((void*)1, (void*)0x08442498, (void*)0x05000020, 0x20, 0x10);
    value2 = stats[0xB3]; if (value2 < 0) value2 = 0;
    percent = sub_080C2F20(100 * ((u32)value2 >> 8), stats[0xB4] >> 8);
    sub_08000E98((void*)1, (void*)(0x080DC89A + percent*26), (void*)(((D_02021E90.gfxTileBase & 0x1F00) << 3) + 0x06000042), 0x1A, 0x10);
    if (*(u8*)((u8*)stats + 0x2DB) == 0 || (D_02021E90.flags & 0x10)) sub_08000E98((void*)1, (void*)0x08442458, (void*)0x05000040, 0x20, 0x10);
    else sub_08000E98((void*)1, (void*)0x084424B8, (void*)0x05000040, 0x20, 0x10);
    sub_08000E98((void*)1, (void*)(D_080DD2DC + *(s16*)((u8*)stats + 0x2D4) * 6), (void*)(((D_02021E90.gfxTileBase & 0x1F00) << 3) + 0x06000086), 6, 0x10);
    iconIndex = (u8*)&stats[0xB6];
    sub_08000E98((void*)1, (void*)(*iconIndex * 8 + D_080DBE28), (void*)(((D_02021E90.gfxTileBase & 0x1F00) << 3) + 0x06000080), 4, 0x10);
    sub_08000E98((void*)1, (void*)(*iconIndex * 8 + (D_080DBE28 + 4)), (void*)(((D_02021E90.gfxTileBase & 0x1F00) << 3) + 0x060000C0), 4, 0x10);
    if (D_02027A00.bannerTimer != 0) {
        if (D_02027A00.bannerState == 0) {
            sub_08062484();
            D_02027A00.bannerState = 1;
            D_02027A00.bannerTimer -= 1;
            if (D_02027A00.bannerTimer == 0) { D_02027A00.bannerState = 0; sub_08000E98((void*)1, (void*)0x08442570, (void*)(((D_02021E90.gfxTileBase & 0x1F00) << 3) + 0x06000440), 0xC0, 0x10); }
        } else {
            D_02027A00.bannerTimer -= 1;
            if (D_02027A00.bannerTimer == 0) { D_02027A00.bannerState = 0; sub_08000E98((void*)1, (void*)0x08442570, (void*)(((D_02021E90.gfxTileBase & 0x1F00) << 3) + 0x06000440), 0xC0, 0x10); }
        }
    }
}
