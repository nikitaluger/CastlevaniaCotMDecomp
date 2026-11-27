extern void sub_080C31E0(void *a, void *b);
extern void unlinkAndFreeObject(void *a);

struct SceneState {
    u8 pad0[0x14EC];
    u8 state;
    u8 pad1[0x1780 - 0x14ED];
    u32 slotState[1];
};
extern struct SceneState gMainWorkspace;

/* Unlink the group node this entity owns at +0x3C, clear its per-slot state
 * word (slot at +0xAC), then run the group's +0x18 handler. */
void releaseEffectGroup(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *group = *(u8 **)(self + 0x6C) + 4;

    unlinkAndFreeObject(*(void **)(group + 0x3C));
    gMainWorkspace.slotState[*(s32 *)(self + 0xAC)] = 0;
    sub_080C31E0(arg0, *(void **)(group + 0x18));
}
