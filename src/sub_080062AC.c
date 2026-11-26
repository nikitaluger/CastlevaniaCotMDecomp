/* Fold the raw coordinate pairs at gCameraState+0x1460 into the virtual input
 * word at D_03000830: copy the id/pressure fields, then set or clear the two
 * direction flags along with their coordinate values. */
extern u8 gCameraState[];
extern u16 D_03000830[];

static inline u16 flagBit(int n) {
    u16 m = 0x80 << n;
    return m;
}

void sub_080062AC(void) {
    u16 *input = D_03000830;
    u8 *raw = gCameraState;
    u16 word, upper;

    input[9] = raw[0x1468] | (raw[0x1469] << 8);
    word = input[10];
    upper = word & 0xFF00;
    input[10] = upper | raw[0x146A];

    if (raw[0x1460] >= raw[0x1462] && raw[0x1464] >= raw[0x1466]) {
        word = input[0];
        input[0] = word & 0xDFFF;
    } else {
        word = input[0];
        input[0] = flagBit(6) | word;
        input[5] = (raw[0x1460] << 8) | raw[0x1462];
        input[7] = (raw[0x1464] << 8) | raw[0x1466];
    }

    if (raw[0x1461] >= raw[0x1463] && raw[0x1465] >= raw[0x1467]) {
        word = input[0];
        input[0] = word & 0xBFFF;
    } else {
        word = input[0];
        input[0] = flagBit(7) | word;
        input[6] = (raw[0x1461] << 8) | raw[0x1463];
        input[8] = (raw[0x1465] << 8) | raw[0x1467];
    }
}
