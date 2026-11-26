struct S_02025FF0 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;

struct Node_080A02AC {
    s16 id;
    u8 _pad[0x2C - 2];
    struct Node_080A02AC *next;
};

s32 sub_080A02AC(void) {
    struct Node_080A02AC *node;
    u32 count = 0;
    node = *(struct Node_080A02AC **)((u8 *)gMainWorkspace.v + 0x30);
    if (node != NULL) {
        do {
            if (node->id == 0x184) count++;
            node = node->next;
        } while (node != NULL);
    }
    if (count > 5) return 1;
    else return 0;
}

void *sub_0805FAEC(s32, s32);
extern u16 D_0866FDE8[];

/* Spawns a type-0x184 effect from the source entity, copying its +0x4C word and
 * filling in +0x5C and +0x6C; returns NULL when no object slot is available. */
void *sub_080A02EC(void *source) {
    void *effect = sub_0805FAEC((s32)gMainWorkspace.v, 0x184);
    void *result;
    if (effect != NULL) {
        u16 index;
        *(u32 *)((u8 *)effect + 0x4C) = *(u32 *)((u8 *)source + 0x4C);
        *(u32 *)((u8 *)effect + 0x5C) = 0x017F0000;
        index = D_0866FDE8[*(u8 *)((u8 *)source + 0x6C)];
        *(u16 *)((u8 *)effect + 0x6C) = index;
        result = effect;
    } else {
        result = NULL;
    }
    return result;
}
