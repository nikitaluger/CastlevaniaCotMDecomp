extern u32 gMainObjTimerCallbacks;
void clearActorPool(void);
void decompressToVram(const void *src, void *dst);
void postDisplaySprite(s32 a, const void *src, void *dst, s32 c, s32 d);
u8 *createChildObject(void *arg0, s32 idx);
s32 isResourceLoaded(void);
void stopAllSounds(void);
void setSoundMode(s32 mode);
void playSound(s32 sound);
typedef void (*Func2)(void *, void *);

extern struct LevelLoadCameraState gCameraState;

/* Load a level scene: reset view state and graphics mode, clear and refill
 * VRAM/palette memory, spawn the scene's two child objects, reset sound and
 * invoke the scene setup callback. */
void loadLevelScene(void *scene)
{
    struct LevelLoadCameraState *cam = &gCameraState;
    u32 zero;
    u16 fillWord;
    volatile u32 *dmaReg;
    u8 *child;
    u8 *stepTimer;
    u32 scrollOffset;
    u16 mode;
    cam->f125C = 0;
    mode = *(volatile u16 *)LEVEL_GFX_MODE_REG;
    mode &= 0xF0FF;
    zero = 0;
    *(volatile u16 *)LEVEL_GFX_MODE_REG = mode + zero;
    cam->f1260 = 0xD8 << 8;
    cam->f1320 = 0;
    cam->f12E0 = 0;
    cam->f12A0 = 0;
    cam->f1262 = 0x88;
    scrollOffset = LEVEL_SCROLL_X_OFFSET;
    *((u32 *)((u8 *)cam + scrollOffset + 4)) = 0;
    *((u32 *)((u8 *)cam + scrollOffset)) = 0;
    clearActorPool();
    fillWord = 0;
    dmaReg = (volatile u32 *)LEVEL_DMA3_REG;
    dmaReg[0] = (u32)&fillWord;
    dmaReg[1] = 0x06000000;
    dmaReg[2] = 0x8100C000;
    dmaReg[2];
    decompressToVram((void *)LEVEL_TILES_VRAM_C000, (void *)0x0600C000);
    decompressToVram((void *)LEVEL_TILES_VRAM_0, (void *)0x06000000);
    postDisplaySprite(1, (void *)LEVEL_PALETTE_DATA, (void *)0x05000000, 0x200, 0x10);
    decompressToVram((void *)LEVEL_TILES_VRAM_10000, (void *)0x06010000);
    postDisplaySprite(1, (void *)LEVEL_PALETTE_EXTRA, (void *)0x050002A0, 0x40, 0x10);
    *(u8 *)((u8 *)scene + 0x5C) = 2;
    child = createChildObject(scene, 0x16);
    *(u8 *)(child + 0x3C) = 0;
    child = createChildObject(scene, 0x16);
    *(u8 *)(child + 0x3C) = 1;
    if (isResourceLoaded() == 0)
    {
        stopAllSounds();
        setSoundMode(0xC0000);
        playSound(1);
    }
    *(u32 *)((u8 *)scene + 4) = 0;
    { s16 objIndex = *(s16 *)((u8 *)scene + 0x22);
      u32 byteOffset = objIndex * 2;
      stepTimer = (u8 *)(byteOffset + (u32)scene) + 0x19; }
    *stepTimer = zero;
    ((Func2)gMainObjTimerCallbacks)((u8 *)scene + 0x18, (u8 *)scene + 0x22);
}
