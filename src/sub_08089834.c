extern u32 gMainWorkspace[];
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, void *);

/* Updates a scripted object's draw priority against the world depth (sets or
 * clears the "behind" flag on its sprite), then either retires the object when
 * the global transition flag is clear or refreshes its screen position. */
void sub_08089834(void *entity) {
    u8 *self = (u8 *)entity;
    u8 *state = *(u8 **)(self + 0x6C);
    void *sprite = *(void **)(self + 0x38);
    void *objectData = state + 4;
    s32 depth = (s32)gMainWorkspace[14];
    s32 objectY = *(s32 *)((u8 *)sprite + 0x14);
    if (depth < objectY) {
        u16 flags = *(u16 *)((u8 *)sprite + 2);
        u32 value = 0x10;
        value = value | flags;
        *(u16 *)((u8 *)sprite + 2) = value;
    } else {
        u16 flags = *(u16 *)((u8 *)sprite + 2);
        u32 value = 0xFFEF;
        value = value & flags;
        *(u16 *)((u8 *)sprite + 2) = value;
    }
    if (gMainWorkspace[4] == 0) {
        sub_080C31E0(self, *(void **)(self + 0x24));
    } else {
        sub_0806D588(sprite, objectData);
    }
}
