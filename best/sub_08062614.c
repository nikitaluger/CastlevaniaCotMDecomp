extern void sub_0805FDF0(void);
extern void sub_0805FE28(s32, s32);
extern void sub_0805FE8C(s32, s32, s32);
extern void sub_0805FEB4(s32);
extern void sub_0805FEC8(u16);
extern u8 D_02021E90[];
extern u8 D_02025368[];

typedef struct {
    vu32 src;
    vu32 dst;
    vu32 cnt;
} Dma3;
#define DMA3 ((Dma3 *)0x040000D4)

void sub_08062614(void *arg0)
{
    u8 stack[0x144];
    u8 *s = D_02025368;
    u8 *g = D_02021E90;
    u8 *t;
    u8 *p;
    u16 *fill;
    u16 *base;
    u8 *adj;
    u32 i;
    u32 idx;
    u32 off;
    u32 zero;
    u16 val;
    u8 b;
    u8 z;
    s32 calc;
    u32 mask;

    p = g + 0x1360;
    z = 0;
    *p = z;
    *(u32 *)(stack + 0x140) = z;
    DMA3->src = (u32)(stack + 0x140);
    DMA3->dst = (u32)stack;
    DMA3->cnt = 0x85000050;
    (void)DMA3->cnt;

    i = 0;
    t = g;
    fill = (u16 *)(stack + 0xC0);
    do {
        *fill = (u16)(i + 0x41);
        fill++;
        i++;
    } while (i <= 0x1F);

    zero = 0;
    DMA3->src = (u32)stack;
    val = *(u16 *)(t + 0x1262);
    mask = 0xF8 << 5;
    mask &= val;
    DMA3->dst = (mask << 3) + 0x06000500;
    DMA3->cnt = 0x800000A0;
    (void)DMA3->cnt;

    DMA3->src = 0x08442650;
    DMA3->dst = 0x05000000;
    DMA3->cnt = 0x80000010;
    (void)DMA3->cnt;

    sub_0805FDF0();
    sub_0805FE28(0, 0x41);
    sub_0805FE8C(0, 1, 1);
    sub_0805FEB4(0);
    base = (u16 *)0x080DEA4C;
    idx = s[0x94];
    adj = (u8 *)base + 2;
    sub_0805FEC8(*(u16 *)(adj + (idx << 2)));

    off = 0x1443;
    b = t[off];
    calc = 0xF0 - (b << 3);
    calc = -(calc >> 1);
    off -= 0x91;
    *(s16 *)(t + off) = (s16)calc;
    t[0x13AF] = 0xFF;
    *(u16 *)((u8 *)arg0 + 2) |= 0x800;
    *(u16 *)((u8 *)arg0 + 0x22) = zero;
    *(u32 *)((u8 *)arg0 + 0x14) = 0x0806271D;
}
