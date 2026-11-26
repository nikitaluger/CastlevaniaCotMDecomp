extern void *D_0866CF38[];
extern u8 gCameraState[];
extern void decompressToVram(u32 *arg0, void *arg1);
extern volatile int postDisplaySprite(void *a, void *b, void *c, u32 d, u32 e);
extern u8 sub_0806DDF4(void);

/* Load one of four graphics sets into VRAM according to the current state's
 * type, then retint four sprite attributes to point at the loaded tiles. */
void sub_0800EC20(u16 *arg0) {
    u32 gfxIndex;
    u32 typeCode;
    u8 *base;
    void *p;
    u32 shift;
    u32 i;
    gfxIndex = 0;
    typeCode = sub_0806DDF4();
    switch (typeCode) {
    case 2: gfxIndex = 1; break;
    case 1: gfxIndex = 2; break;
    case 4: gfxIndex = 3; break;
    case 3: gfxIndex = 4; break;
    }
    p = D_0866CF38[gfxIndex];
    base = gCameraState;
    decompressToVram((u32 *)p, (void *)(0x06003DE0 + ((*(u16 *)(base + 0x1262) & 0xC) << 12)));
    shift = (*(u16 *)(base + 0x1262) & 0xC) << 12;
    postDisplaySprite((void *)1, (void *)(0x06003DE0 + shift), (void *)(0x06005F60 + shift), 0x80, 0x10);
    for (i = 0; i < 4; i++) {
        if (gfxIndex != 0) {
            *arg0 = (*arg0 & 0x0FFF) | (0xC0 << 7);
        } else {
            *arg0 = (*arg0 & 0x0FFF) | (0xA0 << 7);
        }
        arg0++;
    }
}
