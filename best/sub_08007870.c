typedef struct { u8 _0[0x18]; u8 f18[0x0A]; s16 f22; } Arg0;
extern void updateObjectTree(void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern u8 gMainWorkspace[];
extern u16 D_085244B4[];
extern u32 gScriptStepCallbacks[];
void sub_08007870(Arg0 *arg0)
{
    u16 buf[16];
    u8 *base, *base2;
    u32 factor, m1, m2;
    u16 *src, *dst;
    s32 i;
    base = gMainWorkspace;
    updateObjectTree(*(void **)(base + 0x1854));
    updateObjectTree(*(void **)(base + 0x1860));
    (*(u32 *)(base + 0x1894))++;
    updateObjectTree(*(void **)(base + 0x1888));
    (*(u32 *)(base + 0x14A8))++;
    m1 = 0x3E0;
    m2 = 0x7C00;
    base2 = base;
    dst = buf;
    src = D_085244B4;
    factor = *(u32 *)(base + 0x14A8);
    for (i = 0xF; i >= 0; i--) {
        u16 c;
        u32 r;
        u32 g;
        u32 b;
        c = *src;
        r = c & 0x1F;
        g = (c & m1) >> 5;
        b = (m2 & c) >> 10;
        r = (r * factor) >> 4;
        g = (g * factor) >> 4;
        b = (b * factor) >> 4;
        do { do { do { if (r > 0x1F) r = 0x1F; } while (0); } while (0); } while (0);
        if (g > 0x1F) g = 0x1F;
        if (b > 0x1F) b = 0x1F;
        g <<= 5;
        b <<= 10;
        *dst = (u16)((r + g) + b);
        dst++;
        src++;
    }
    {
        vu32 *dma;
        dma = (vu32 *)0x040000D4;
        dma[0] = (u32)buf;
        dma[1] = 0x05000140;
        dma[2] = 0x80000010;
        (void)dma[2];
    }
    if (*(u32 *)(base2 + 0x14A8) > 0x7F) {
        *(u32 *)(base2 + 0x14B8) = (*(u32 *)(base2 + 0x14B4) & 0xF) | 0x80;
        do { updateObjectTree(*(void **)(base2 + 0x185C));
        updateObjectTree(*(void **)(base2 + 0x1860));
        (*(u32 *)(base2 + 0x1894))++;
        { vu16 *io;
 io = (vu16 *)0x03000830; io[2] = 0xBF; io[4] += 0x10; }
        sub_080C31E0(*(void **)(base2 + 0x1858), *(void **)(*(u32 *)(base2 + 0x1858) + 0x24));
        sub_080C31E0(*(void **)(base2 + 0x1868), *(void **)(*(u32 *)(base2 + 0x1868) + 0x24)); } while (0);
        sub_080C31E0(*(void **)(base2 + 0x186C), *(void **)(*(u32 *)(base2 + 0x186C) + 0x24));
        sub_080C31E0(*(void **)(base2 + 0x1870), *(void **)(*(u32 *)(base2 + 0x1870) + 0x24));
        sub_080C31E0(*(void **)(base2 + 0x1874), *(void **)(*(u32 *)(base2 + 0x1874) + 0x24));
        sub_080C31E0(*(void **)(base2 + 0x1878), *(void **)(*(u32 *)(base2 + 0x1878) + 0x24));
        sub_080C31E0(*(void **)(base2 + 0x187C), *(void **)(*(u32 *)(base2 + 0x187C) + 0x24));
        sub_080C31E0(*(void **)(base2 + 0x1880), *(void **)(*(u32 *)(base2 + 0x1880) + 0x24));
        sub_080C31E0(*(void **)(base2 + 0x1888), *(void **)(*(u32 *)(base2 + 0x1888) + 0x24));
        *((u8 *)arg0 + 2 * arg0->f22 + 0x19) = 0;
        sub_080C31E8(arg0->f18, &arg0->f22, 1, (void *)gScriptStepCallbacks);
    }
}
