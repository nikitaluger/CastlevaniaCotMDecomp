extern void copyPoseAttrs(void *, void *);
extern u8 D_080CEE58[];

/* Maps the owner's state at +0x28 to a parameter-table index, stamps that
 * index into two target objects and copies their parameter records to them. */
void sub_08035DEC(u8 *owner, void **targets) {
    s32 paramIndex = 1;
    volatile u8 indexBytes[2];
    volatile u8 *p = indexBytes;
    *p = paramIndex;
    *(p + 1) = paramIndex;

    switch (*(u16 *)(owner + 0x28)) {
    case 0x3E: paramIndex = 2; break;
    case 0x40: paramIndex = 3; break;
    case 0x42: paramIndex = 4; break;
    case 0x44: paramIndex = 5; break;
    case 0x47: paramIndex = 6; break;
    case 0x4A: paramIndex = 7; break;
    case 0x4E: paramIndex = 8; break;
    case 0x52: paramIndex = 9; break;
    case 0x53: paramIndex = 10; break;
    default: break;
    }
    *(u8 *)((u8 *)targets[0] + 1) = indexBytes[0];
    *(u8 *)((u8 *)targets[1] + 1) = indexBytes[1];
    copyPoseAttrs(targets[0], D_080CEE58 + paramIndex * 0x10);
    copyPoseAttrs(targets[1], D_080CEE58 + 8 + paramIndex * 0x10);
}
