extern u16 D_080CFB1C[];
extern u16 D_080CFB24[];
extern u16 D_080CFB2C[];
extern u16 D_080CFB34[];
extern u16 D_080CFB3C[];

struct Unk547E0 {
    u8 pad[0x28];
    u16 * volatile field;
};

void sub_080547E0(u8 *arg0, struct Unk547E0 *arg1) {
    u16 *src = D_080CFB1C;
    u16 v = *(u16*)(arg0 + 0x28);
    switch (v) {
        case 0: src = D_080CFB1C; break;
        case 2: src = D_080CFB24; break;
        case 4: src = D_080CFB2C; break;
        case 6: src = D_080CFB34; break;
        case 8: src = D_080CFB3C; break;
    }
    arg1->field[3] = src[0];
    arg1->field[4] = src[1];
    arg1->field[5] = src[2];
    arg1->field[6] = src[3];
}
