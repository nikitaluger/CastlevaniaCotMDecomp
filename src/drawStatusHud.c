/* Draws the status HUD: two fixed-point gauges rendered as digit sprites, a
 * name/icon plate, and a timed message banner. */
struct HudGfxState { u8 _0[8]; u32 flags; u8 _0C[0x1256]; u16 gfxTileBase; };
struct HudBannerState { u8 _0[0xD8]; u16 timer; u8 state; };
extern struct HudGfxState gCameraState;
extern struct HudBannerState gMessageBanner;
extern u8 gNamePlateTiles[];
extern u8 gStatusIconTiles[];
extern s32 gGameStatus[];
volatile int postDisplaySprite(void *a, void *b, void *c, u32 d, u32 e);
void sub_08062484(void);
s32 divideInt(s32, s32);
void drawStatusHud(void) {
    s32 *stats = gGameStatus;
    s32 gauge1Value, gauge2Value, percent;
    u8 *iconIndex;
    gauge1Value = stats[0xB1]; if (gauge1Value < 0) gauge1Value = 0;
    percent = divideInt(100 * ((u32)gauge1Value >> 8), stats[0xB2] >> 8);
    postDisplaySprite((void*)1, (void*)(0x080DBE58 + percent*26), (void*)(((gCameraState.gfxTileBase & 0x1F00) << 3) + 0x06000002), 0x1A, 0x10);
    if (*(u8*)((u8*)stats + 0x2DA) == 0 || (gCameraState.flags & 0x10)) postDisplaySprite((void*)1, (void*)0x08442438, (void*)0x05000020, 0x20, 0x10);
    else postDisplaySprite((void*)1, (void*)0x08442498, (void*)0x05000020, 0x20, 0x10);
    gauge2Value = stats[0xB3]; if (gauge2Value < 0) gauge2Value = 0;
    percent = divideInt(100 * ((u32)gauge2Value >> 8), stats[0xB4] >> 8);
    postDisplaySprite((void*)1, (void*)(0x080DC89A + percent*26), (void*)(((gCameraState.gfxTileBase & 0x1F00) << 3) + 0x06000042), 0x1A, 0x10);
    if (*(u8*)((u8*)stats + 0x2DB) == 0 || (gCameraState.flags & 0x10)) postDisplaySprite((void*)1, (void*)0x08442458, (void*)0x05000040, 0x20, 0x10);
    else postDisplaySprite((void*)1, (void*)0x084424B8, (void*)0x05000040, 0x20, 0x10);
    postDisplaySprite((void*)1, (void*)(gNamePlateTiles + *(s16*)((u8*)stats + 0x2D4) * 6), (void*)(((gCameraState.gfxTileBase & 0x1F00) << 3) + 0x06000086), 6, 0x10);
    iconIndex = (u8*)&stats[0xB6];
    postDisplaySprite((void*)1, (void*)(*iconIndex * 8 + gStatusIconTiles), (void*)(((gCameraState.gfxTileBase & 0x1F00) << 3) + 0x06000080), 4, 0x10);
    postDisplaySprite((void*)1, (void*)(*iconIndex * 8 + (gStatusIconTiles + 4)), (void*)(((gCameraState.gfxTileBase & 0x1F00) << 3) + 0x060000C0), 4, 0x10);
    if (gMessageBanner.timer != 0) {
        if (gMessageBanner.state == 0) {
            sub_08062484();
            gMessageBanner.state = 1;
            gMessageBanner.timer -= 1;
            if (gMessageBanner.timer == 0) { gMessageBanner.state = 0; postDisplaySprite((void*)1, (void*)0x08442570, (void*)(((gCameraState.gfxTileBase & 0x1F00) << 3) + 0x06000440), 0xC0, 0x10); }
        } else {
            gMessageBanner.timer -= 1;
            if (gMessageBanner.timer == 0) { gMessageBanner.state = 0; postDisplaySprite((void*)1, (void*)0x08442570, (void*)(((gCameraState.gfxTileBase & 0x1F00) << 3) + 0x06000440), 0xC0, 0x10); }
        }
    }
}
