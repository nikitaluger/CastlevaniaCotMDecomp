extern u16 gAnimatedEffectAffineParams[];
extern u16 D_080CEA78[];
extern u16 D_080CEA80[];
extern u16 D_080CEA88[];
extern u16 D_080CEA90[];
extern u16 D_080CEA98[];
extern u16 D_080CEAA0[];
/* Attack hitbox: a flag byte at +1 and four 16-bit box edges at +6..+0xD. */
struct Hitbox { u8 pad[1]; u8 flag; u8 pad2[4]; u16 maxX, maxY, minX, minY; };

/* Select an attack hitbox by the source's action offset, clear the target's
 * active-hit flag for the two "no hit" actions, and copy the box edges over. */
void sub_0802D678(u8 *source, u8 *target) {
    u16 *boxParams = gAnimatedEffectAffineParams;
    s32 hitboxIndex = *(u16 *)(source + 0x28) - 0x2C;
    switch (hitboxIndex) {
    case 0:
    case 23:
        ((struct Hitbox *)*(struct Hitbox **)(target + 0x28))->flag &= 0xFE;
        break;
    case 1:
        boxParams = gAnimatedEffectAffineParams;
        break;
    case 3:
        boxParams = D_080CEA78;
        break;
    case 6:
        boxParams = D_080CEA80;
        break;
    case 9:
        boxParams = D_080CEA88;
        break;
    case 12:
        boxParams = D_080CEA90;
        break;
    case 16:
        boxParams = D_080CEA98;
        break;
    case 22:
        boxParams = D_080CEAA0;
        break;
    default:
        break;
    }
    ((struct Hitbox *)*(struct Hitbox **)(target + 0x28))->maxX = boxParams[0];
    ((struct Hitbox *)*(struct Hitbox **)(target + 0x28))->maxY = boxParams[1];
    ((struct Hitbox *)*(struct Hitbox **)(target + 0x28))->minX = boxParams[2];
    ((struct Hitbox *)*(struct Hitbox **)(target + 0x28))->minY = boxParams[3];
}
