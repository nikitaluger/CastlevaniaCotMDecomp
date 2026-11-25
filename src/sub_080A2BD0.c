extern void sub_0800168C(void *, s32, s32, s32);
extern s32 sub_080A2E38(s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080A2C38(void);

/* Initialises an entity's companion state: allocates it, fills its 11-slot child
 * table, sets the respawn flag/flags and installs sub_080A2C38 as its update
 * callback. Without a companion, dispatches the entity's fallback handler. */
void sub_080A2BD0(void *arg0) {
    void *companion;

    sub_0800168C(arg0, 0, 0xA0, 0);
    companion = *(void **)((u8 *)arg0 + 0x3C);
    if (companion == NULL) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
    } else {
        u32 childIndex = 0;
        u8 *respawnFlag = (u8 *)arg0 + 0x4C;
        s32 *childTable = (s32 *)((u8 *)companion + 0x48);
        for (; childIndex <= 10; childIndex++) {
            *childTable++ = sub_080A2E38(childIndex);
        }
        *respawnFlag = 0;
        {
            u16 flags = *(u16 *)((u8 *)arg0 + 2) | 0x1000;
            *(u16 *)((u8 *)arg0 + 2) = flags | 0x800;
        }
        *(void **)((u8 *)arg0 + 0x14) = &sub_080A2C38;
        *(u16 *)((u8 *)arg0 + 0x22) = 1;
        sub_080C31E0(arg0, &sub_080A2C38);
    }
}
