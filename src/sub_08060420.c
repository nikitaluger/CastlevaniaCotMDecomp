/* Main game state (D_02021E90) fields touched by the map command scripts. */
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
extern struct S_02021E90_local D_02021E90;

/* Advance the map command script by one step (a do-nothing script command). */
s32 sub_08060420(void)
{
    D_02021E90.scriptPos += 1;
    return 0;
}
