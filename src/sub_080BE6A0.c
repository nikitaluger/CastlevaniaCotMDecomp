struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 manager; };
extern struct S_02025FF0_1870 D_02025FF0;

extern void sub_080C31E0(void *, s32);

/* Release every type-0x1D6 child effect, first in the object's own list at
 * +0x30 and then in the global manager's list, by running its callback. */
void sub_080BE6A0(void *arg0)
{
    void *node = *(void **)((u8 *)arg0 + 0x30);
    while (node != 0) {
        if (*(s16 *)node == 0x1D6) {
            sub_080C31E0(node, *(s32 *)((u8 *)node + 0x24));
        }
        node = *(void **)((u8 *)node + 0x2C);
    }
    node = *(void **)((u8 *)(void *)D_02025FF0.manager + 0x30);
    while (node != 0) {
        if (*(s16 *)node == 0x1D6) {
            sub_080C31E0(node, *(s32 *)((u8 *)node + 0x24));
        }
        node = *(void **)((u8 *)node + 0x2C);
    }
}
