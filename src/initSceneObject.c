extern void copyBytes(void *, void *, s32);
extern u8 gCameraState[];

/* Header of a scene object: bit 11 of the u16 flags at +0x02 marks it as set up. */
struct SceneObjectHeader { u8 pad[2]; u16 flags; };

/* Set up a scene object: DMA two graphics blocks into VRAM, seed display-state
 * slot 0x99 from a ROM template, initialise the shadow input/state block at
 * 0x02025FF0, and install the object's callbacks and counters. */
void initSceneObject(void *scene) {
    s32 zero = 0;
    *(s32 *)((u8 *)scene + 0x7C) = zero;
    *(s32 *)((u8 *)scene + 0x6C) = 0x17;
    *(s32 *)((u8 *)scene + 0x9C) = zero;
    *(s32 *)((u8 *)scene + 0x8C) = 0x1F;
    {
        volatile u32 *dma = (volatile u32 *)SCENE_OBJ_DMA_REG;
        dma[0] = SCENE_OBJ_GFX_A_SRC;
        dma[1] = SCENE_OBJ_GFX_A_DST;
        dma[2] = SCENE_OBJ_GFX_A_CTRL;
        (void)dma[2];
        dma[0] = SCENE_OBJ_GFX_B_SRC;
        dma[1] = SCENE_OBJ_GFX_B_DST;
        dma[2] = SCENE_OBJ_GFX_B_CTRL;
        (void)dma[2];
    }
    *(void **)((u8 *)scene + 0x5C) = *(void **)((u8 *)scene + 0x24);
    *(void **)((u8 *)scene + 0x24) = (void *)SCENE_OBJ_CLEANUP_CALLBACK;
    {
        u8 *stateBase = gCameraState;
        s32 stateSlot = SCENE_OBJ_STATE_SLOT;
        copyBytes((void *)(stateBase + stateSlot * 32), (void *)SCENE_OBJ_STATE_TEMPLATE, SCENE_OBJ_STATE_COPY_SIZE);
    }
    *(s32 *)((u8 *)scene + 0x3C) = zero;
    *(s32 *)((u8 *)scene + 0x4C) = zero;
    {
        u8 *inputBase = (u8 *)SCENE_OBJ_INPUT_BASE;
        u32 flagValue;
        u16 *flagDest;
        *(u32 *)(inputBase + 0x145C) = zero;
        *(u32 *)(inputBase + 0x1460) = zero;
        *(u32 *)(inputBase + 0x1464) = 0x03000000;
        *(u32 *)(inputBase + 0x1468) = 0x02000000;
        *(u32 *)(inputBase + 0x146C) = zero;
        *(u32 *)(inputBase + 0x1470) = 0x02800000;
        *(u32 *)(inputBase + 0x1474) = zero;
        *(u32 *)(inputBase + 0x1478) = 0x02000000;
        flagDest = (u16 *)(inputBase + 0x147C);
        flagValue = SCENE_OBJ_INPUT_FLAG;
        *flagDest = flagValue;
        *(u16 *)(inputBase + 0x147E) = flagValue;
        *(u32 *)(inputBase + 0x1480) = zero;
        *(u32 *)(inputBase + 0x1484) = zero;
        *(u32 *)(inputBase + 0x1488) = 0x03000000;
        *(u32 *)(inputBase + 0x148C) = 0x02000000;
        *(u32 *)(inputBase + 0x1490) = zero;
        *(u32 *)(inputBase + 0x1494) = 0x02800000;
        *(u32 *)(inputBase + 0x1498) = zero;
        *(u32 *)(inputBase + 0x149C) = 0x02000000;
        *(u16 *)(inputBase + 0x14A0) = flagValue;
        *(u16 *)(inputBase + 0x14A2) = flagValue;
    }
    ((struct SceneObjectHeader *)scene)->flags |= SCENE_OBJ_READY_FLAG;
    *(s16 *)((u8 *)scene + 0x22) = 0;
    *(s32 *)((u8 *)scene + 0x14) = SCENE_OBJ_UPDATE_HANDLER;
}
