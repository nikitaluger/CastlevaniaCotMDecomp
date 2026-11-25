extern s32 sub_08007D7C(void *, s32, s32);
extern s32 sub_080159BC(s32, s32, s32, s32, u32, u32);
extern u8 D_02025FF0[];
extern u8 D_02023130[];
extern s16 D_080CB278[];

struct ObjFlags { u8 _0[2]; u16 bits; };

/* Moves an object horizontally by its velocity, resolving tile collisions and
 * recording wall/floor/ceiling hits in the object's flag word. */
void sub_08011674(u8 *obj, s32 probeNeg, s32 probePos)
{
    s32 velocity = *(s32 *)(obj + 0x10);
    s32 probeX, newX, candidateX, tile;
    s32 oldX, oldPage;
    u32 hit[5];

    *(u16 *)(obj + 2) = 0;
    if (*(u16 *)(obj + 4) & 0x10) {
        if (probeNeg != 0 || probePos != 0) {
            if (velocity < 0) probeX = *(s32 *)(obj + 8) - probeNeg;
            else probeX = *(s32 *)(obj + 8) + probePos;
        } else probeX = *(s32 *)(obj + 8);
        if (sub_080159BC(probeX, *(s32 *)(obj + 0xC), velocity, 0, 0x900 | *(u16 *)(obj + 6), (u32)hit) == 1) {
            velocity += (s32)hit[1];
            if (*(u16 *)hit & 6) ((struct ObjFlags *)obj)->bits |= 0x200;
        }
    }
    oldX = *(s32 *)(obj + 8);
    oldPage = oldX & 0xFFFF0000;
    newX = oldX + velocity;
    if (oldPage == (newX & 0xFFFF0000)) {
        *(s32 *)(obj + 8) = newX;
    } else {
        if (probeNeg != 0 || probePos != 0) {
            if (velocity < 0) candidateX = newX - probeNeg;
            else candidateX = newX + probePos;
        } else candidateX = newX;

        tile = sub_08007D7C((void *)(D_02023130 + D_02025FF0[0x18A8] * 0x40), candidateX, *(s32 *)(obj + 0xC));
        if (D_080CB278[(u16)tile] & 0xA) {
            if (*(s32 *)(obj + 0x10) > 0) candidateX = (candidateX & 0xFFF80000) - 0x8000;
            else candidateX = (candidateX & 0xFFF80000) + 0x88000;
            ((struct ObjFlags *)obj)->bits |= 1;
        }
        if (*(u16 *)(obj + 4) & 8) {
            tile = sub_08007D7C((void *)(D_02023130 + D_02025FF0[0x18A8] * 0x40), candidateX, *(s32 *)(obj + 0xC) + 0x80000);
            if (D_080CB278[(u16)tile] & 1) {
                if (*(s32 *)(obj + 0x10) > 0) candidateX = (candidateX & 0xFFF80000) - 0x8000;
                else candidateX = (candidateX & 0xFFF80000) + 0x88000;
                ((struct ObjFlags *)obj)->bits |= 2;
            }
        }
        if (*(u16 *)(obj + 4) & 0x20) {
            tile = sub_08007D7C((void *)(D_02023130 + D_02025FF0[0x18A8] * 0x40), candidateX, *(s32 *)(obj + 0xC) - 0x80000);
            if (D_080CB278[(u16)tile] & 1) {
                if (*(s32 *)(obj + 0x10) > 0) candidateX = (candidateX & 0xFFF80000) - 0x8000;
                else candidateX = (candidateX & 0xFFF80000) + 0x88000;
                ((struct ObjFlags *)obj)->bits |= 0x10;
            }
        }
        if (probeNeg != 0 || probePos != 0) {
            if (velocity < 0) candidateX += probeNeg;
            else candidateX -= probePos;
        }
        *(s32 *)(obj + 8) = candidateX;
    }
}
