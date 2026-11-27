extern u16 D_080CF2A0[];
extern u16 D_080CF2B8[];
extern u16 D_080CF2C0[];

struct TwoHitboxAttribs {
    u8 pad[1];
    u8 kind;
    u8 pad2[4];
    u16 tile0, tile1, tile2, tile3;
};

void sub_0803BB10(u8 *entity, u8 *sprite) {
    u8 *state = *(u8 **)(entity + 0x3c);
    u8 *extra = state + 0x48;
    u16 *tiles = D_080CF2A0;
    u16 *tiles2 = tiles + 4;
    u16 *tiles3 = tiles + 8;
    u32 index = *(u16 *)(sprite + 0x28);

    switch (index) {
    case 0:
    case 5:
        tiles = D_080CF2A0;
        tiles2 = tiles + 4;
        tiles3 = tiles + 8;
        break;
    case 10:
    case 16:
        tiles2 = D_080CF2B8;
        break;
    case 21:
        tiles = D_080CF2C0;
        tiles2 = tiles + 4;
        tiles3 = tiles + 8;
        break;
    default:
        break;
    }

    ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->tile0 = tiles[0];
    ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->tile1 = tiles[1];
    ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->tile2 = tiles[2];
    ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->tile3 = tiles[3];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 0xC))->tile0 = tiles2[0];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 0xC))->tile1 = tiles2[1];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 0xC))->tile2 = tiles2[2];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 0xC))->tile3 = tiles2[3];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 8))->tile0 = tiles3[0];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 8))->tile1 = tiles3[1];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 8))->tile2 = tiles3[2];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 8))->tile3 = tiles3[3];
}
