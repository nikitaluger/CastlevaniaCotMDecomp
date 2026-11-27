extern u8 gCameraState[];

void decode2bppTiles(u8 arg0, u8 arg1, u8 arg2, u8 *src, u8 *dst)
{
    u8 sp[4];
    u32 i, j, k;
    u8 shifted;
    u8 idx;
    s32 out = 0, in = 0;

    sp[0] = (gCameraState[0x1439] << 4) | gCameraState[0x1439];
    sp[1] = (gCameraState[0x1439] << 4) | gCameraState[0x143A];
    sp[2] = (gCameraState[0x143A] << 4) | gCameraState[0x1439];
    sp[3] = (gCameraState[0x143A] << 4) | gCameraState[0x143A];

    for (i = 0; i < arg1; i++) {
        shifted = (u8)(src[in] << arg2);
        k = in + 1;
        for (j = 0; j < arg0; j++) {
            idx = (shifted & 0xC0) >> 6;
            dst[out] = sp[idx];
            out++;
            shifted = (u8)(shifted << 2);
        }
        out += 4 - arg0;
        in = k;
    }
}
