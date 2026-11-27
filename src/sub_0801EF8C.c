extern u16 D_080CE738[];
extern u16 D_080CE740[];

struct Hitbox1EF8C {
    u8 pad[1];
    u8 flag;
    u8 pad2[4];
    u16 maxX;
    u16 maxY;
    u16 minX;
    u16 minY;
};

void sub_0801EF8C(u8 *arg0, u8 *arg1) {
    u16 *boxParams = D_080CE738;
    s32 idx = *(u16 *)(arg0 + 0x28) - 0x29;

    switch (idx) {
    case 0:
    case 2:
    case 7:
    case 11:
    case 15:
        ((struct Hitbox1EF8C *)*(struct Hitbox1EF8C **)(arg1 + 0x28))->flag &= 0xFA;
        break;
    case 19:
        boxParams = D_080CE740;
        break;
    default:
        break;
    }

    ((struct Hitbox1EF8C *)*(struct Hitbox1EF8C **)(arg1 + 0x28))->maxX = boxParams[0];
    ((struct Hitbox1EF8C *)*(struct Hitbox1EF8C **)(arg1 + 0x28))->maxY = boxParams[1];
    ((struct Hitbox1EF8C *)*(struct Hitbox1EF8C **)(arg1 + 0x28))->minX = boxParams[2];
    ((struct Hitbox1EF8C *)*(struct Hitbox1EF8C **)(arg1 + 0x28))->minY = boxParams[3];
}
