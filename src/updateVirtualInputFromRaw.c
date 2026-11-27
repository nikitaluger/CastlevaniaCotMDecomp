/* Fold the raw coordinate pairs at gCameraState+0x1460 into the virtual-input
 * word at gCrossfadeGfxState: copy the id/pressure fields, then set or clear the
 * two direction flags along with their coordinate values. flagBit builds each
 * flag by a runtime shift rather than a literal. */
extern u8 gCameraState[];
extern u16 gCrossfadeGfxState[];

static inline u16 flagBit(int n) {
    u16 m = 0x80 << n;
    return m;
}

void updateVirtualInputFromRaw(void) {
    u16 *virtualInput = gCrossfadeGfxState;
    u8 *rawInput = gCameraState;
    u16 word, upper;

    virtualInput[9] = rawInput[0x1468] | (rawInput[0x1469] << 8);
    word = virtualInput[10];
    upper = word & 0xFF00;
    virtualInput[10] = upper | rawInput[0x146A];

    if (rawInput[0x1460] >= rawInput[0x1462] && rawInput[0x1464] >= rawInput[0x1466]) {
        word = virtualInput[0];
        virtualInput[0] = word & 0xDFFF;
    } else {
        word = virtualInput[0];
        virtualInput[0] = flagBit(6) | word;
        virtualInput[5] = (rawInput[0x1460] << 8) | rawInput[0x1462];
        virtualInput[7] = (rawInput[0x1464] << 8) | rawInput[0x1466];
    }

    if (rawInput[0x1461] >= rawInput[0x1463] && rawInput[0x1465] >= rawInput[0x1467]) {
        word = virtualInput[0];
        virtualInput[0] = word & 0xBFFF;
    } else {
        word = virtualInput[0];
        virtualInput[0] = flagBit(7) | word;
        virtualInput[6] = (rawInput[0x1461] << 8) | rawInput[0x1463];
        virtualInput[8] = (rawInput[0x1465] << 8) | rawInput[0x1467];
    }
}
