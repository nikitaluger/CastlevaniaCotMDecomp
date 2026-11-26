extern s32 sub_080067B8(s32, s32);
extern void sub_080C31E0(void *, s32);

struct S_02025368_CADC { u8 _0[0x3CF]; u8 v3CF; };
extern struct S_02025368_CADC gGameStatus;

struct S_02025FF0_CADC {
    u8 _0[0x1848];
    u32 v1848;
    u8 _1[0x18C5 - 0x184C];
    u8 v18C5;
    u8 v18C6;
};
extern struct S_02025FF0_CADC gMainWorkspace;

/* Copies a 64-byte palette block from 0x050001E0 to 0x050002C0 over DMA. If
 * the slot-15 animation clamped, it marks a byte in gGameStatus with 3, clears
 * two flag fields in gMainWorkspace and aborts the object's current script. */
void sub_0808CADC(void *arg0) {
    u8 *obj = (u8 *)arg0;
    struct S_02025368_CADC *state = &gGameStatus;
    s32 result;
    vu32 *dma;
    u32 src;

    result = sub_080067B8(0xF, 0xF);
    dma = (vu32 *)0x040000D4;
    src = 0x050001E0;
    dma[0] = src;
    dma[1] = src + 0xE0;
    dma[2] = 0x80000010;
    (void)dma[2];
    if (result != 0) {
        u8 *flagAddr = (u8 *)state + 0x3CF;
        u8 zero = 0;
        *flagAddr = 3;
        gMainWorkspace.v1848 &= 0xB241FFFF;
        gMainWorkspace.v18C6 = zero;
        gMainWorkspace.v18C5 = zero;
        sub_080C31E0(obj, *(s32 *)(obj + 0x24));
    }
}
