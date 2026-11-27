struct S_02025FF0 { u8 _0[0x1870]; u32 p; };
extern struct S_02025FF0 gMainWorkspace;

void *spawnBudgetedEffect(void *, s32);

/* Spawn a case-2 object at fixed-point position (x, y): allocate one from the
 * entity pool, then store its position, 16-bit parameter and direction byte. */
void sub_0809C8A8(s32 x, s32 y, u16 param, u8 dir) {
    void *obj = spawnBudgetedEffect((void *)gMainWorkspace.p, 0x179);
    if (obj != NULL) {
        *(s32 *)((u8 *)obj + 0x4C) = x;
        *(s32 *)((u8 *)obj + 0x5C) = y;
        *(u16 *)((u8 *)obj + 0x6C) = param;
        *(u8 *)((u8 *)obj + 0x74) = dir;
    }
}
