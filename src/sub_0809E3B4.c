extern s32 sub_080057F8(void);
extern s32 scaleByRandom(s32);
extern void sub_080A0288(void*, s32);
extern s32 sub_080A02A4(void*);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

/* When a spawn timer expires, choose a random target coordinate inside the
 * camera's visible range and assign it to the entity. */
void sub_0809E3B4(void *arg0, void *arg1) {
    void *self;
    void *spawnState;
    s32 delay;
    u8 *base;
    u32 off;
    u32 *centerPtr;
    u8 *layerTable, *xTable, *activeLayerPtr;
    s32 lowerBound, upperBound, layerX, spawnMin, spawnMax, span, offset;
    u32 layerOffset;

    self = arg0;
    spawnState = arg1;
    delay = *((u8*)arg1 + 1);
    if (delay != 0) {
        delay = delay - 1;
        *((u8*)arg1 + 1) = delay;
        if ((u8)delay != 0) goto end;
    }
    if (sub_080A02A4(arg0) != 0) goto end;

    base = gMainWorkspace;
    off = 0x174C;
    centerPtr = (u32 *)(base + off);
    lowerBound = *centerPtr + 0xFFF00000;
    upperBound = *centerPtr + 0x100000;

    layerTable = gCameraState;
    activeLayerPtr = base;
    activeLayerPtr += 0x18A8;
    layerOffset = ((u32)*activeLayerPtr + 1) * 0x40;
    xTable = layerTable + 0x1278;
    layerX = *(u32 *)(xTable + layerOffset);

    spawnMin = layerX + 0x208000;
    if (spawnMin <= 0x2FFFFF) spawnMin = 0x300000;
    spawnMax = layerX + 0xD08000;
    if (spawnMax > 0x01D00000) spawnMax = 0x01D00000;
    if (lowerBound >= spawnMin || upperBound <= spawnMin) {
        if (lowerBound >= spawnMax || upperBound <= spawnMax) {
            if (lowerBound > spawnMin && upperBound < spawnMax) {
                if (sub_080057F8() & 1) {
                    spawnMax = lowerBound;
                } else {
                    spawnMin = upperBound;
                }
            }
        } else {
            spawnMax = lowerBound;
        }
    } else {
        spawnMin = upperBound;
    }
    span = spawnMax - spawnMin;
    offset = scaleByRandom(span);
    sub_080A0288(arg0, offset + spawnMin);
    *((u8*)arg1) += 1;
end:
    return;
}
