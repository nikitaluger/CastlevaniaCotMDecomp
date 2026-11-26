extern void copyPoseAttrs(void *, void *);

/* Copies two eight-byte blocks of animation parameters from the table at
 * 0x08101C00 into the caller's sprite objects, picking the entry by the
 * entity's script index. */
void sub_080A3D8C(void *arg0, void *arg1, void *arg2) {
    void *obj1;
    void *obj2;
    s32 slot;
    u32 base;
    s16 index;
    void *dest1;
    void *dest2;

    obj1 = arg1;
    obj2 = arg2;
    slot = 0;
    index = *(s16 *)((u8 *)arg0 + 0x0E);

    switch (index) {
        case 0: slot = 0; break;
        case 2: slot = 1; break;
        case 4: slot = 2; break;
        case 6: slot = 3; break;
        case 8: slot = 4; break;
        case 10: slot = 0; break;
        case 14: slot = 1; break;
        case 18: slot = 2; break;
        case 22: slot = 3; break;
        case 26: slot = 4; break;
        default: break;
    }

    dest1 = *(void **)((u8 *)obj1 + 0x28);
    slot = slot << 4;
    base = 0x08101C00;
    copyPoseAttrs(dest1, (void *)(base + slot));
    dest2 = *(void **)((u8 *)obj2 + 0x50);
    base += 8;
    slot = slot + base;
    copyPoseAttrs(dest2, (void *)slot);
}
