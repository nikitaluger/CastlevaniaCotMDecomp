extern void *sub_0805FAEC(s32, s32);

/* Spawns `count` type-0x1CF objects, each parented by the previously spawned
 * one, tagging them with `group` at +0x4C and consecutive ids starting at
 * `idBase` + 1 at +0x5C; stops early if the spawn budget is exhausted. */
void sub_080B98B8(s32 parent, u32 count, s32 group, s32 idBase) {
    s32 nextId;
    u32 i;
    void *obj;

    obj = (void *)parent;
    i = 0;
    if (i < count) {
        nextId = idBase + 1;
    loop_2:
        obj = sub_0805FAEC((s32)obj, 0x1CF);
        if (obj != NULL) {
            *(s32 *)((u8 *)obj + 0x4C) = group;
            *(s32 *)((u8 *)obj + 0x5C) = nextId;
            nextId += 1;
            i += 1;
            if (i < count) {
                goto loop_2;
            }
        }
    }
}
