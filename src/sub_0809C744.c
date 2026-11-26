extern u32 D_08101990[];
extern u8 gCameraState[];

void postDisplaySprite(s32, u32, u32, s32, s32);
void sub_08000E54(s32, u32, u32, s32, s32);

struct GfxSourceTable { u32 gfx0, gfx1, gfx2; };

/* Load a 0x100-byte graphics tile into the buffer whose address is held at
 * gCameraState+0x12F4: gfxIndex 1-3 copy one of three sources from D_08101990
 * with postDisplaySprite, while index 0 fills with the constant 0x8080 via
 * sub_08000E54. */
void sub_0809C744(u8 gfxIndex)
{
    u8 index = gfxIndex;
    struct GfxSourceTable sources = *(struct GfxSourceTable *)D_08101990;

    if (index != 0)
    {
        u32 *srcList = &sources.gfx0;
        s32 srcIndex = index - 1;
        u32 src = srcList[srcIndex];
        u8 *destPtr = gCameraState;
        destPtr += 0x12F4;
        postDisplaySprite(1, src, *(u32 *)destPtr, 0x100, 0x10);
    }
    else
    {
        u32 src = 0x8080;
        u8 *destPtr = gCameraState;
        destPtr += 0x12F4;
        sub_08000E54(1, src, *(u32 *)destPtr, 0x100, 0x10);
    }
}
