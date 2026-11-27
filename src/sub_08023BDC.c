extern u16 D_080CE84C[];
extern u16 D_080CE854[];
extern u16 D_080CE864[];
extern u16 D_080CE874[];
extern u16 D_080CE884[];
extern u16 D_080CE88C[];
extern u16 D_080CE89C[];
extern u16 D_080CE8A4[];

struct TwoHitboxAttribs {
    u8 pad[1];
    u8 kind;
    u8 pad2[4];
    u16 tile0, tile1, tile2, tile3;
};

void sub_08023BDC(u8 *entity, u8 *sprite) {
    u8 *state = *(u8 **)(entity + 0x3c);
    u8 *extra = state + 0x48;
    u16 *tiles = D_080CE84C;
    u16 *tiles2 = D_080CE84C;
    u32 index = *(u16 *)(sprite + 0x28) - 0x45;

    switch (index) {
    case 0:
        tiles = D_080CE84C;
        ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->kind = 0;
        break;
    case 1:
        tiles = D_080CE854;
        tiles2 = tiles + 4;
        break;
    case 3:
    case 6:
        tiles = D_080CE864;
        tiles2 = tiles + 4;
        break;
    case 9:
        tiles = D_080CE874;
        tiles2 = tiles + 4;
        break;
    case 13:
        tiles = D_080CE884;
        ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->kind = 0;
        break;
    case 17:
        tiles = D_080CE88C;
        tiles2 = tiles + 4;
        break;
    case 19:
        tiles = D_080CE89C;
        ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->kind = 0;
        break;
    case 22:
        tiles = D_080CE8A4;
        ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->kind = 0;
        break;
    default:
        ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->kind = 0;
        ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->kind = 0;
        break;
    }

    ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->tile0 = tiles[0];
    ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->tile1 = tiles[1];
    ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->tile2 = tiles[2];
    ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->tile3 = tiles[3];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->tile0 = tiles2[0];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->tile1 = tiles2[1];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->tile2 = tiles2[2];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->tile3 = tiles2[3];
}
