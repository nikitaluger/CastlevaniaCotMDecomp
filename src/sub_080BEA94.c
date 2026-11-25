/* An entry of the shared D_02021E90 state array. Each entry is 0x20 bytes:
 * a 16-bit flag word followed by command parameters. */
struct MenuEntry { u16 flags; u8 param[0x1E]; };
extern struct MenuEntry D_02021E90[];

/* Mark state entry 0x95 complete by setting its 0x2000 completion flag. */
void sub_080BEA94(void) {
    D_02021E90[0x95].flags |= (0x80 << 6);
}

/* Dispatch the command selected by state entry 0x9B from the jump table at
 * 0x0867078C; a zero parameter only toggles the DISPCNT bank bit. */
extern void sub_080C31DC(void *);
void sub_080BEAB0(void) {
    u8 *table = (u8 *)0x0867078C;
    if (D_02021E90[0x9B].param[0] == 0) {
        *(vu8 *)0x04000004 &= 0xDF;
    } else {
        *(vu8 *)0x04000004 |= 0x20;
        sub_080C31DC(*(void **)(table + D_02021E90[0x9B].param[0] * 4));
    }
}

/* Fill the 0x1000-word buffer whose address is held at 0x02021F44 with the
 * repeated halfword 0x017C, then upload the palette sheet at 0x0841FBA4. */
extern void sub_08097DF8(s32);
struct FillBufPtr { u8 pad[0x12B4]; u32 dst; };
extern struct FillBufPtr D_02021E90_2;
void sub_080BEA50(void) {
    u16 fill;
    vu32 *dma3 = (vu32 *)0x040000D4;
    fill = 0xBE << 1;
    dma3[0] = (u32)&fill;
    dma3[1] = *(u32 *)(0x02021E90 + 0x12B4);
    dma3[2] = 0x81001000;
    (void)dma3[2];
    sub_08097DF8(0x0841FBA4);
}

/* Dispatch the command selected by the byte at 0x02021F11 from the jump table
 * at 0x086707B0. */
struct SelByte { u8 pad[0x1361]; u8 param; };
extern struct SelByte D_02021E90_3;
void sub_080BEAF8(void) {
    u8 *table = (u8 *)0x086707B0;
    sub_080C31DC(*(void **)(table + D_02021E90_3.param * 4));
}
