void sub_0806C5EC(void*, void*, void*, void*);
void sub_0806C6B0(void*, void*, void*, void*);
void sub_080C31E4(void *, void *, void *);
extern vu32 gMainWorkspace[];
extern u8 gCameraState[];
extern u32 gMainObjTimerCallback[];

struct Arg69 {
    u8 pad0[0x18];
    u32 f18;
    u8 pad1[0x6];
    s16 f22;
    u8 pad2[0x14];
    u32 f38;
    u8 pad3[0x30];
    u8 *f6C;
};
struct Regs { u8 pad[4]; u16 reg; };
struct Args { void *a; void *b; };

void sub_08069BE8(struct Arg69 *arg0) {
    u16 pal[16];
    volatile struct Args args;
    void *sp20;
    u16 *src;
    u16 *dst;
    s32 factor;
    s32 cnt;
    s32 i;
    volatile u32 *dma;
    u32 off3 = 0x12BC;
    u32 maskG, maskB;
    u32 *table;

    args.a = arg0->f6C + 4;
    args.b = (void *)arg0->f38;
    sp20 = args.a;
    sub_0806C5EC(arg0, args.b, sp20, sp20);

    do { cnt = --gMainWorkspace[0x52A]; } while (0);

    maskG = 0x3E0;
    maskB = 0x7C00;
    do { cnt = cnt; } while (0);
    src = (u16 *)0x08521F10;
    i = 15;
    dst = pal;
    do {
        u16 c = *src;
        u32 r = c & 0x1F;
        u32 g = (maskG & c) >> 5;
        u32 b = (maskB & c) >> 10;
        u32 g5, b10;
        r = (r * (u32)cnt) >> 4;
        do { g = (g * (u32)cnt) >> 4; } while (0);
        do { b = (b * (u32)cnt) >> 4; } while (0);
        if (r > 0x1F) r = 0x1F;
        if (g > 0x1F) g = 0x1F;
        if (b > 0x1F) b = 0x1F;
        g5 = g << 5;
        b10 = b << 10;
        *dst++ = r + g5 + b10;
        src++;
        i--;
    } while (i >= 0);

    dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)pal;
    dma[1] = 0x05000140;
    dma[2] = 0x80000010;
    (void)dma[2];

    if (gMainWorkspace[0x52A] == 0) {
        *(u32 *)(gCameraState + off3) = 0;
        ((struct Regs *)0x03000830)->reg = 0xBF;
        gMainWorkspace[0x52B] = 4;
        *(u8 *)((u8 *)arg0 + arg0->f22 * 2 + 0x19) = 0;
        table = gMainObjTimerCallback;
        sub_080C31E4(&arg0->f18, &arg0->f22, (void *)table[0]);
    }
    sub_0806C6B0(arg0, args.b, args.a, sp20);
}
