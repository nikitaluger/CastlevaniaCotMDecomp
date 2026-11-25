extern void *sub_0805FAEC(s32 parent, s32 type);

/* Spawns effect 0x18D at (x, y): allocates one object from the class budget
 * and stores the two fixed-point coordinates at +0x4C and +0x5C. */
void sub_080A2DA8(s32 parent, s32 x, s32 y) {
    void *obj;

    obj = sub_0805FAEC(parent, 0x18D);
    if (obj != NULL) {
        *(s32 *)((u8 *)obj + 0x4C) = x;
        *(s32 *)((u8 *)obj + 0x5C) = y;
    }
}
