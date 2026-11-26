/* Loads the graphics needed by the current scene: depending on the scene id in the global
 * state it issues one or two DMA2 transfers from a ROM descriptor table, then sets up the
 * camera/scroll state and spawns the scene's effect objects. */
extern s32 sub_080014D0(s32, s32);
extern s32 sub_0806A884(void *, void *);
extern u8 D_02025FF0[];
extern u8 gCameraState[];

struct FlagsAt2 { u16 pad; u16 flags; };
struct FlagsAt1260 { u8 pad[0x1260]; u16 flags; };

/* Each 12-byte descriptor is (source, destination, length); the length is halved and
 * ORed with the DMA repeat-enable bit. A call submits two consecutive descriptors. */
#define DMA2(dmaRegs, desc) do { \
    (dmaRegs)[0] = (desc)[0]; (dmaRegs)[1] = (desc)[1]; \
    (dmaRegs)[2] = (((s32)((desc)[2] + ((desc)[2] >> 31))) >> 1) | 0x80000000; (void)(dmaRegs)[2]; \
    (dmaRegs)[0] = (desc)[3]; (dmaRegs)[1] = (desc)[4]; \
    (dmaRegs)[2] = (((s32)((desc)[5] + ((desc)[5] >> 31))) >> 1) | 0x80000000; (void)(dmaRegs)[2]; \
} while (0)

void loadSceneGraphics(void) {
    u8 *state = D_02025FF0;
    u32 *desc;
    switch (*(s32 *)&state[0x10]) {
    case 6: {
        vu32 *dmaRegs;
        desc = (u32 *)0x080E5F44;
        dmaRegs = (vu32 *)0x040000D4;
        DMA2(dmaRegs, desc);
        break;
    }
    case 15: {
        vu32 *dmaRegs;
        desc = (u32 *)0x080E5F74;
        dmaRegs = (vu32 *)0x040000D4;
        DMA2(dmaRegs, desc);
        desc += 6;
        DMA2(dmaRegs, desc);
        *(u32 *)(*(u32 *)&state[0x1720]) = 0x880000;
        *(u32 *)(*(u32 *)&state[0x1720] + 4) = 0xC70000;
        desc = (u32 *)&state[0x171C];
        sub_0806A884(*(void **)desc, *(void **)&state[0x1720]);
        sub_080014D0(*(s32 *)&state[0x1864], 0x7B);
        sub_080014D0(*(s32 *)&state[0x1864], 0x7C);
        sub_080014D0(*(s32 *)&state[0x1864], 0x81);
        ((struct FlagsAt2 *)*desc)->flags |= 0x10;
        ((struct FlagsAt1260 *)gCameraState)->flags |= 0x2000;
        break;
    }
    case 1: {
        vu32 *dmaRegs;
        desc = (u32 *)0x080E5EFC;
        dmaRegs = (vu32 *)0x040000D4;
        DMA2(dmaRegs, desc);
        desc += 6;
        DMA2(dmaRegs, desc);
        state[0x18B0] = 0;
        state[0x18B4] = 0;
        *(u32 *)(*(u32 *)&state[0x1720]) = 0xFFC00000;
        *(u32 *)(*(u32 *)&state[0x1720] + 4) = 0x7F0000;
        sub_0806A884(*(void **)&state[0x171C], *(void **)&state[0x1720]);
        *(u32 *)&state[0x20] = 3;
        sub_080014D0(*(s32 *)&state[0x1864], 0x7B);
        sub_080014D0(*(s32 *)&state[0x1864], 0x7C);
        sub_080014D0(*(s32 *)&state[0x1864], 0x7D);
        sub_080014D0(*(s32 *)&state[0x1864], 0x7E);
        break;
    }
    }
}
