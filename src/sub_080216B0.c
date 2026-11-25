extern u16 D_080CE7E4[];
extern u16 D_080CE7EC[];
extern u16 D_080CE7F4[];
extern u16 D_080CE7FC[];

/* Attack hitbox: flag byte at +1, four 16-bit box edges at +6..+0xD. */
struct Hitbox {
    u8 pad[1];
    u8 flag;
    u8 pad2[4];
    u16 maxX, maxY, minX, minY;
};

/* Pick an attack hitbox table by the source entity's action index, clear the
 * target's active-hit flag for actions with no box, and copy the four box
 * edges into the target's hitbox. */
void sub_080216B0(u8 *source, u8 *target) {
    u8 *dst = target;
    u16 *boxParams = D_080CE7E4;
    s32 boxIndex = *(u16 *)(source + 0x28) - 0x31;

    switch (boxIndex) {
    case 0:
        boxParams = D_080CE7E4;
        break;
    case 1:
        boxParams = D_080CE7EC;
        break;
    case 3:
    case 7:
        boxParams = D_080CE7F4;
        break;
    case 14:
    case 18:
        boxParams = D_080CE7FC;
        break;
    default:
        ((struct Hitbox *)*(struct Hitbox **)(dst + 0x28))->flag = 0;
        break;
    }

    ((struct Hitbox *)*(struct Hitbox **)(dst + 0x28))->maxX = boxParams[0];
    ((struct Hitbox *)*(struct Hitbox **)(dst + 0x28))->maxY = boxParams[1];
    ((struct Hitbox *)*(struct Hitbox **)(dst + 0x28))->minX = boxParams[2];
    ((struct Hitbox *)*(struct Hitbox **)(dst + 0x28))->minY = boxParams[3];
}
