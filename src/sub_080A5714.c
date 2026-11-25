extern void *sub_0805FAEC(s32 parent, s32 type);

/* Spawn effect object kind 0x197 under the given parent and give it the world
 * position (x, y) stored in the parent at +0x4C/+0x5C. */
void sub_080A5714(s32 parent, s32 x, s32 y) {
    void *obj;

    obj = sub_0805FAEC(parent, 0x197);
    if (obj != NULL) {
        *(s32 *)((u8 *)obj + 0x4C) = x;
        *(s32 *)((u8 *)obj + 0x5C) = y;
    }
}
