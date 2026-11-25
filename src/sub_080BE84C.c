extern void *sub_0805FAEC(void *, s32);

struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 obj; };
extern struct S_02025FF0_1870 D_02025FF0;

/* Spawn an entity of type 0x1DA at (x, y) with parameter `param`; the spawn is
 * silently skipped when the object pool is full. */
void sub_080BE84C(s32 x, s32 y, s32 param) {
    void *obj = sub_0805FAEC((void *)D_02025FF0.obj, 0x1DA);
    if (obj != 0) {
        *(s32 *)((u8 *)obj + 0x4C) = x;
        *(s32 *)((u8 *)obj + 0x5C) = y;
        *(s32 *)((u8 *)obj + 0x6C) = param;
    }
}
