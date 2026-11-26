struct S_02021E90_local {
    u8 pad_0[0x1262];
    u16 bgControl;
    u8 pad_1264[0x1D6];
    u8 layerParamA;
    u8 layerParamB;
    u8 pad_143C[0x18];
    s32 scriptPos;
    u8 pad_1458[4];
    u8 graphicsFlags;
};
extern struct S_02021E90_local gCameraState;

/* Swap the two map-layer parameters and advance the map command script by one. */
s32 sub_08060438(void)
{
    u8 tmp = gCameraState.layerParamB;
    gCameraState.layerParamB = gCameraState.layerParamA;
    gCameraState.layerParamA = tmp;
    gCameraState.scriptPos += 1;
    return 0;
}
