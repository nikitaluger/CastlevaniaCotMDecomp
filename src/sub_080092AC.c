void postDisplaySprite(u32, void *, u32, u32, u32);
s32 divideInt(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Darkens a sprite's 4x16 palette by the current script step's counter, uploads
 * it to palette RAM, and advances the step once the fade is complete. */
void sub_080092AC(void *entity) {
    void *gfxState;
    volatile u32 *dmaReg;
    u16 *palette;
    u32 colorMask;
    u32 row;
    u32 col;
    u32 nextRow;
    u16 *color;
    u16 *paletteBase;
    s32 *scriptStepPtr;

    gfxState = *(void **)((u8 *)entity + 0x3C);
    dmaReg = (volatile u32 *)0x040000D4;
    dmaReg[0] = 0x0865B220;
    dmaReg[1] = (u32)gfxState + 0x38;
    dmaReg[2] = 0x80000030;
    (void)dmaReg[2];
    dmaReg[0] = 0x080CA9FC;
    paletteBase = (u16 *)((u8 *)gfxState + 0x18);
    dmaReg[1] = (u32)paletteBase;
    dmaReg[2] = 0x80000002;
    (void)dmaReg[2];
    row = 0;
    palette = paletteBase;
    colorMask = 0x1F;
    do {
        u32 rowOffset;
        col = 0;
        rowOffset = row * 32;
        nextRow = ++row;
        color = (u16 *)(rowOffset + (u32)palette);
        do {
            u16 color16 = *color;
            u32 red = color16 & 0x1F;
            u32 shifted = (u32)color16 << 16;
            u32 green = (shifted >> 21) & colorMask;
            u32 blue = (shifted >> 26) & colorMask;
            u8 fade;
            fade = *(u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22)) * 2 + 0x19);
            red = red - divideInt(fade * red, 0x18);
            fade = *(u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22)) * 2 + 0x19);
            green = green - divideInt(fade * green, 0x18);
            fade = *(u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22)) * 2 + 0x19);
            blue = blue - divideInt(fade * blue, 0x18);
            red &= colorMask;
            green &= colorMask;
            green <<= 5;
            red |= green;
            blue &= colorMask;
            blue <<= 10;
            red |= blue;
            *color = (u16)red;
            color++;
            col++;
        } while (col <= 0x0F);
        row = nextRow;
    } while (row <= 0x03);
    postDisplaySprite(1, palette, 0x050000E0, 0x80, 0x10);
    {
        u32 slotOffset = (*(s16 *)((u8 *)entity + 0x22)) * 2;
        u8 *cmdSlot = (u8 *)(slotOffset + (u32)entity);
        if (cmdSlot[0x19] == 0x18) {
            cmdSlot[0x19] = 0;
            scriptStepPtr = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *scriptStepPtr);
        }
    }
}
