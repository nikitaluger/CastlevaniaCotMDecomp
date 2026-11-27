extern void clearActorPool(void);
extern void postDisplaySprite(s32, const void *, u32, s32, s32);
extern s32 decompressToVram(void *, void *);
extern s32 _call_via_r2(void *, void *, s32);
extern u32 gMainObjTimerCallbacks;
extern u8 gCameraState[];
extern vu16 gCrossfadeGfxState;
extern vu32 D_040000D4[];

/* Rebuild the main object's graphics: reset the camera's background and scroll
 * state, clear the actor pool and VRAM, load sprite tiles and palettes for the
 * object's kind, then dispatch its next script step. */
void initMainObjectGraphics(u8 *obj) {
    u16 zeroWord;
    u16 *mapPtr;
    u16 *dstPtr;
    vu32 *dma3;
    u8 *camera = gCameraState;
    u32 *callback;

    *(u32 *)(camera + CAMERA_MO_STATE_WORD) = 0;
    gCrossfadeGfxState = gCrossfadeGfxState & 0xF0FF;
    mapPtr = (u16 *)(camera + CAMERA_MO_MAP_BASE);
    {
        u32 mapBase = 0xD800;
        *mapPtr = mapBase;
    }
    mapPtr = (u16 *)(0x99 << 5);
    dstPtr = (u16 *)(camera + (u32)mapPtr);
    *dstPtr = 0;
    mapPtr = (u16 *)((u32)mapPtr - 0x40);
    dstPtr = (u16 *)(camera + (u32)mapPtr);
    *dstPtr = 0;
    mapPtr = (u16 *)((u32)mapPtr - 0x40);
    dstPtr = (u16 *)(camera + (u32)mapPtr);
    *dstPtr = 0;
    *(u16 *)(camera + CAMERA_MO_MAP_CONTROL) = 8;
    {
        u32 *scrollX = (u32 *)(camera + CAMERA_MO_SCROLL_X);
        u32 *scrollY = (u32 *)(camera + CAMERA_MO_SCROLL_Y);
        *scrollY = 0;
        *scrollX = 0;
    }
    clearActorPool();
    zeroWord = 0;
    dma3 = D_040000D4;
    dma3[0] = (u32)&zeroWord;
    dma3[1] = 0xC0 << 19;
    dma3[2] = 0x8100C000;
    (void)dma3[2];
    postDisplaySprite(1, (const void *)MAIN_OBJ_SPRITE_GFX, 0xA0 << 19, 0x40, 0x10);
    if (*(u32 *)(obj + 0x3C) <= 4) {
        decompressToVram((void *)MAIN_OBJ_TILE_GFX_NORMAL_A, (void *)0x06008000);
        decompressToVram((void *)MAIN_OBJ_TILE_GFX_NORMAL_B, (void *)(0xC0 << 19));
    } else {
        decompressToVram((void *)MAIN_OBJ_TILE_GFX_ALT_A, (void *)0x06008000);
        decompressToVram((void *)MAIN_OBJ_TILE_GFX_ALT_B, (void *)(0xC0 << 19));
    }
    if (*(u32 *)(obj + 0x3C) <= 4) {
        u8 *gfxTable = (u8 *)MAIN_OBJ_GFX_TABLE;
        u32 kind = *(u32 *)(obj + 0x3C);
        decompressToVram(*(void **)(gfxTable + (kind << 3)), (void *)0x06009820);
        kind = *(u32 *)(obj + 0x3C);
        kind <<= 3;
        gfxTable += 4;
        decompressToVram(*(void **)(gfxTable + kind), (void *)0x06009B20);
    }
    {
        s16 stepIndex = *(s16 *)(obj + 0x22);
        *(u8 *)(obj + stepIndex * 2 + 0x19) = 0;
        callback = &gMainObjTimerCallbacks;
        _call_via_r2(obj + 0x18, obj + 0x22, (s32)*callback);
    }
}
