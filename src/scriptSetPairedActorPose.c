/* Sets a synchronized animation pose on two actors from a script index: maps the index
 * to a pose/variant pair, loads the matching transform data into each actor's sprite,
 * and applies the paired palette/attribute bytes. */
extern void copyPoseAttrs(void *, void *);
extern u16 gPairedPoseAttrs[];
extern u8 gPairedPoseBytes[];

struct IndexPair { u16 a; u16 b; };

/* Look the scripted animation index up in the thread's index table, then give both
 * actors their two halves of the matching pose record and variant bytes. */
void scriptSetPairedActorPose(u8 *thread, u8 *actorA, u8 *actorB)
{
    u32 poseId = 0;
    u32 variantIndex = 0;
    u32 tableIndex;
    u32 *posePtrTable;
    u8 *pairTable;

    if (actorB[0x21] == 2) {
        *(u8 *)(*(u32 *)(actorA + 0x28) + 1) = 0;
        *(u8 *)(*(u32 *)actorB + 1) = 0;
    }

    posePtrTable = *(u32 **)(thread + 8);
    tableIndex = (u32)(s16)(*(u16 *)(thread + 0xE)) + thread[1];
    pairTable = (u8 *)*posePtrTable;
    tableIndex = ((struct IndexPair *)((u8 *)(pairTable + tableIndex * 4) - 4))->b - 8;

    switch (tableIndex) {
    case 0: case 1: case 2: case 3: case 4: case 5: poseId = 1; break;
    case 9: poseId = 4; break;
    case 10: poseId = 5; break;
    case 11: case 12: poseId = 6; break;
    case 13: poseId = 7; break;
    case 14: poseId = 8; break;
    case 16: poseId = 9; break;
    case 17: poseId = 10; break;
    case 18: poseId = 11; break;
    case 19: poseId = 12; break;
    case 15: case 20: poseId = 13; break;
    case 22: poseId = 15; break;
    case 23: case 24: poseId = 16; break;
    case 7: case 25: poseId = 3; break;
    case 31: poseId = 0x11; variantIndex = 1; break;
    case 32: poseId = 0x12; variantIndex = 1; break;
    case 33: poseId = 0x13; variantIndex = 1; break;
    case 34: poseId = 0x14; variantIndex = 1; break;
    case 6: case 35: case 36: poseId = 2; break;
    case 21: case 37: poseId = 0xE; break;
    case 38: case 39: poseId = 0x15; variantIndex = 1; break;
    case 40: case 42: case 44: case 46: case 48: poseId = 0x16; variantIndex = 1; break;
    case 50: poseId = 0x17; variantIndex = 1; break;
    case 52: poseId = 0x18; variantIndex = 1; break;
    case 54: case 55: case 56: poseId = 0x19; variantIndex = 1; break;
    case 58: poseId = 0x1B; variantIndex = 1; break;
    case 60: case 62: case 64: poseId = 0x1C; variantIndex = 1; break;
    case 57: case 66: case 68: poseId = 0x1A; variantIndex = 1; break;
    case 26: case 27: case 28: case 29: case 30: case 70: case 71: case 72: case 73: case 74: case 75: variantIndex = 2; break;
    default: break;
    }

    copyPoseAttrs(*(void **)(actorA + 0x28), (u8 *)&gPairedPoseAttrs + poseId * PAIRED_POSE_ENTRY_SIZE);
    copyPoseAttrs(*(void **)actorB, (u8 *)&gPairedPoseAttrs + PAIRED_POSE_HALF_SIZE + poseId * PAIRED_POSE_ENTRY_SIZE);
    *(u8 *)(*(u32 *)(actorA + 0x28) + 1) = gPairedPoseBytes[variantIndex * 2];
    *(u8 *)(*(u32 *)actorB + 1) = (gPairedPoseBytes + 1)[variantIndex * 2];
}
