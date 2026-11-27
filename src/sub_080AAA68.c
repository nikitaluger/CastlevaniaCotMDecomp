void *spawnBudgetedEffect(u32, s32);

struct S_02025FF0_1870 {
    u8 _0x000[0x1870];
    u32 objectPoolId;
};
extern struct S_02025FF0_1870 gMainWorkspace;

/* Spawn a projectile from the global pool: allocate object 0x19E and fill its
 * aim position, angle, owner handle and the two control bytes, if one is free. */
void sub_080AAA68(void *owner, s32 spawnX, s32 spawnY, s32 angle, u8 shotCount, u8 variant) {
    void *shot = spawnBudgetedEffect(gMainWorkspace.objectPoolId, 0x19E);
    if (shot != NULL) {
        *(s32 *)((u8 *)shot + 0x4C) = spawnX;
        *(s32 *)((u8 *)shot + 0x5C) = spawnY;
        *(s32 *)((u8 *)shot + 0x6C) = angle;
        *(s32 *)((u8 *)shot + 0x7C) = *(s32 *)(*(s32 *)((u8 *)owner + 0x38) + 0x24);
        *(u8 *)((u8 *)shot + 0x8C) = shotCount;
        *(u8 *)((u8 *)shot + 0x90) = variant;
    }
}
