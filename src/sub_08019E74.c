extern void *spawnBudgetedEffect(s32, s32);

struct S_02025FF0_1870 { u8 _p[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;

/* Spawns effect 0x8B at fixed-point position (x, y) with depth z and speed;
 * stores the integer screen position and returns the new object (NULL if none). */
void *sub_08019E74(s32 x, s32 y, s32 z, s32 speed) {
    void *obj;
    s32 fx, fy;
    s32 px, py;
    obj = spawnBudgetedEffect(gMainWorkspace.v, 0x8B);
    if (obj == NULL) return NULL;
    fx = x;
    if (fx < 0) fx += 0xFFFF;
    px = fx >> 16;
    *(s16 *)((u8 *)obj + 0x4C) = px;
    fy = y;
    if (fy < 0) fy += 0xFFFF;
    py = fy >> 16;
    *(s16 *)((u8 *)obj + 0x54) = py;
    *(u32 *)((u8 *)obj + 0x5C) = z;
    *(u32 *)((u8 *)obj + 0x6C) = speed;
    return obj;
}
