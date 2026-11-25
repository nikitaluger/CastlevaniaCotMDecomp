void sub_08097EF4(s32, void *, s32, s32);
void sub_080B08C8(void);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Attack-step script callback: write two global parameters, destroy two child
 * objects, clear that entity type from the global list, load a palette via DMA,
 * then clear the script byte and dispatch the next handler. */
void sub_080ABB04(u8 *self) {
    u8 *work = (u8 *)*(u32 *)(self + 0x3C);
    u8 *aim = work + 0x48;
    u8 *sysRegs = (u8 *)0x03000830;
    s32 zero = 0;
    u16 reg2Value = 0xFD << 6;
    u8 byte95;
    u8 *child;
    void *paletteSrc;
    s32 *dispatchArg;

    *(u16 *)(sysRegs + 4) = reg2Value;
    byte95 = *(u8 *)(work + 0x95);
    *(u16 *)(sysRegs + 6) = byte95 | ((0x10 - byte95) << 8);
    child = *(u8 **)(work + 0x48);
    sub_080C31E0(child, *(void **)(child + 0x24));
    child = *(u8 **)(aim + 4);
    sub_080C31E0(child, *(void **)(child + 0x24));
    sub_080B08C8();
    paletteSrc = (void *)0x083F4B1C;
    sub_08097EF4(1, paletteSrc, 0, 1);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = zero;
    dispatchArg = (s32 *)0x08671BB4;
    sub_080C31E4(self + 0x18, self + 0x22, *dispatchArg);
}
