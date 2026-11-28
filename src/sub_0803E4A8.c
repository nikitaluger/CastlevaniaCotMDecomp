extern u16 D_080CF3DC[];
extern u16 D_080CF3E4[];
extern u16 D_080CF3EC[];
extern u16 D_080CF3F4[];

struct TwoHitboxAttribs {
    u8 pad[1];
    u8 kind;
    u8 pad2[4];
    u16 tile0, tile1, tile2, tile3;
};

void sub_0803E4A8(u8 *arg0, u8 *arg1) {
    u8 *state = *(u8 **)(arg0 + 0x3c);
    u8 *extra = state + 0x48;
    u16 *tiles1 = D_080CF3DC;
    u16 *tiles2 = D_080CF3DC + 0x10;
    u16 *tiles3 = D_080CF3DC + 0x14;
    u32 index = *(u16 *)(arg1 + 0x28) - 0x10;

    switch (index) {
    case 0:
        tiles1 = D_080CF3E4;
        tiles2 = D_080CF3E4 + 0xC;
        ((struct TwoHitboxAttribs *)*(u8 **)(extra + 8))->kind = 0;
        break;
    case 3:
        tiles1 = D_080CF3EC;
        tiles2 = D_080CF3EC + 0x10;
        ((struct TwoHitboxAttribs *)*(u8 **)(extra + 8))->kind = 0;
        break;
    case 6:
        tiles1 = D_080CF3F4;
        tiles2 = D_080CF3F4 + 0x18;
        tiles3 = D_080CF3F4 + 0x8;
        break;
    case 11:
        tiles1 = D_080CF3F4;
        tiles2 = D_080CF3F4 + 0x10;
        tiles3 = D_080CF3F4 + 0x14;
        break;
    case 16:
        tiles1 = D_080CF3F4;
        tiles2 = D_080CF3F4 + 0x10;
        ((struct TwoHitboxAttribs *)*(u8 **)(extra + 8))->kind = 0;
        break;
    default:
        break;
    }

    do { ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->tile0 = tiles1[0];
    ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->tile1 = tiles1[1];
    ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->tile2 = tiles1[2];
    ((struct TwoHitboxAttribs *)*(u8 **)(state + 0x28))->tile3 = tiles1[3];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->tile0 = tiles2[0];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->tile1 = tiles2[1];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->tile2 = tiles2[2];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 4))->tile3 = tiles2[3];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 8))->tile0 = tiles3[0];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 8))->tile1 = tiles3[1]; } while (0);
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 8))->tile2 = tiles3[2];
    ((struct TwoHitboxAttribs *)*(u8 **)(extra + 8))->tile3 = tiles3[3];
}
