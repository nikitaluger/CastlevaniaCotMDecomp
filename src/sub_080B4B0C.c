/* Sets a synchronized animation pose on two actors from a script index: maps the index
 * to a pose/variant pair, loads the matching transform data into each actor's sprite,
 * and applies the paired palette/attribute bytes. */
extern void sub_08014588(void *, void *);
extern u16 D_0810298C[];
extern u8 D_08102B5C[];

struct Pair { u16 a; u16 b; };

void sub_080B4B0C(u8 *script, u8 *actorA, u8 *actorB)
{
    u32 poseIndex = 0;
    u32 variant = 0;
    u32 idx;
    u32 *ptrTable;
    u8 *tableBase;

    if (actorB[0x21] == 2) {
        *(u8 *)(*(u32 *)(actorA + 0x28) + 1) = 0;
        *(u8 *)(*(u32 *)actorB + 1) = 0;
    }

    ptrTable = *(u32 **)(script + 8);
    idx = (u32)(s16)(*(u16 *)(script + 0xE)) + script[1];
    tableBase = (u8 *)*ptrTable;
    idx = ((struct Pair *)((u8 *)(tableBase + idx * 4) - 4))->b - 8;

    switch (idx) {
    case 0: case 1: case 2: case 3: case 4: case 5: poseIndex = 1; break;
    case 9: poseIndex = 4; break;
    case 10: poseIndex = 5; break;
    case 11: case 12: poseIndex = 6; break;
    case 13: poseIndex = 7; break;
    case 14: poseIndex = 8; break;
    case 16: poseIndex = 9; break;
    case 17: poseIndex = 10; break;
    case 18: poseIndex = 11; break;
    case 19: poseIndex = 12; break;
    case 15: case 20: poseIndex = 13; break;
    case 22: poseIndex = 15; break;
    case 23: case 24: poseIndex = 16; break;
    case 7: case 25: poseIndex = 3; break;
    case 31: poseIndex = 0x11; variant = 1; break;
    case 32: poseIndex = 0x12; variant = 1; break;
    case 33: poseIndex = 0x13; variant = 1; break;
    case 34: poseIndex = 0x14; variant = 1; break;
    case 6: case 35: case 36: poseIndex = 2; break;
    case 21: case 37: poseIndex = 0xE; break;
    case 38: case 39: poseIndex = 0x15; variant = 1; break;
    case 40: case 42: case 44: case 46: case 48: poseIndex = 0x16; variant = 1; break;
    case 50: poseIndex = 0x17; variant = 1; break;
    case 52: poseIndex = 0x18; variant = 1; break;
    case 54: case 55: case 56: poseIndex = 0x19; variant = 1; break;
    case 58: poseIndex = 0x1B; variant = 1; break;
    case 60: case 62: case 64: poseIndex = 0x1C; variant = 1; break;
    case 57: case 66: case 68: poseIndex = 0x1A; variant = 1; break;
    case 26: case 27: case 28: case 29: case 30: case 70: case 71: case 72: case 73: case 74: case 75: variant = 2; break;
    default: break;
    }

    sub_08014588(*(void **)(actorA + 0x28), (u8 *)&D_0810298C + poseIndex * 16);
    sub_08014588(*(void **)actorB, (u8 *)&D_0810298C + 8 + poseIndex * 16);
    *(u8 *)(*(u32 *)(actorA + 0x28) + 1) = D_08102B5C[variant * 2];
    *(u8 *)(*(u32 *)actorB + 1) = (D_08102B5C + 1)[variant * 2];
}
