extern void copyBytes(void *, void *, s32);
extern u8 gCameraState[];

/* Header of a scene object: bit 11 of the u16 flags at +0x02 marks it as set up. */
struct SceneObjectHeader { u8 pad[2]; u16 flags; };

/* Set up a scene object: DMA two graphics blocks into VRAM, seed display-state
 * entry 0x99 from a ROM table, initialise the shadow register block at
 * 0x02025FF0, and install the object's callbacks and counters. */
void sub_080BDE00(void *scene) {
    s32 zero = 0;
    *(s32 *)((u8 *)scene + 0x7C) = zero;
    *(s32 *)((u8 *)scene + 0x6C) = 0x17;
    *(s32 *)((u8 *)scene + 0x9C) = zero;
    *(s32 *)((u8 *)scene + 0x8C) = 0x1F;
    {
        volatile u32 *dmaReg = (volatile u32 *)0x040000D4;
        dmaReg[0] = 0x085127E0;
        dmaReg[1] = 0x0600C000;
        dmaReg[2] = 0x80001000;
        (void)dmaReg[2];
        dmaReg[0] = 0x0851ACBC;
        dmaReg[1] = 0x0600F700;
        dmaReg[2] = 0x80000480;
        (void)dmaReg[2];
    }
    *(void **)((u8 *)scene + 0x5C) = *(void **)((u8 *)scene + 0x24);
    *(void **)((u8 *)scene + 0x24) = (void *)0x080BE215;
    {
        u8 *entry = gCameraState;
        s32 entryIndex = 0x99;
        copyBytes((void *)(entry + entryIndex * 32), (void *)0x08102FFC, 0x40);
    }
    *(s32 *)((u8 *)scene + 0x3C) = zero;
    *(s32 *)((u8 *)scene + 0x4C) = zero;
    {
        u8 *regBase = (u8 *)0x02025FF0;
        u32 wordFlag;
        u16 *flagPtr;
        *(u32 *)(regBase + 0x145C) = zero;
        *(u32 *)(regBase + 0x1460) = zero;
        *(u32 *)(regBase + 0x1464) = 0x03000000;
        *(u32 *)(regBase + 0x1468) = 0x02000000;
        *(u32 *)(regBase + 0x146C) = zero;
        *(u32 *)(regBase + 0x1470) = 0x02800000;
        *(u32 *)(regBase + 0x1474) = zero;
        *(u32 *)(regBase + 0x1478) = 0x02000000;
        flagPtr = (u16 *)(regBase + 0x147C);
        wordFlag = 0x1000;
        *flagPtr = wordFlag;
        *(u16 *)(regBase + 0x147E) = wordFlag;
        *(u32 *)(regBase + 0x1480) = zero;
        *(u32 *)(regBase + 0x1484) = zero;
        *(u32 *)(regBase + 0x1488) = 0x03000000;
        *(u32 *)(regBase + 0x148C) = 0x02000000;
        *(u32 *)(regBase + 0x1490) = zero;
        *(u32 *)(regBase + 0x1494) = 0x02800000;
        *(u32 *)(regBase + 0x1498) = zero;
        *(u32 *)(regBase + 0x149C) = 0x02000000;
        *(u16 *)(regBase + 0x14A0) = wordFlag;
        *(u16 *)(regBase + 0x14A2) = wordFlag;
    }
    ((struct SceneObjectHeader *)scene)->flags |= 0x800;
    *(s16 *)((u8 *)scene + 0x22) = 0;
    *(s32 *)((u8 *)scene + 0x14) = 0x080BDF45;
}
