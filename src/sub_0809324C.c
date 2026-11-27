extern void freeMotionTracker(void *);
extern void sub_080C31E0(void *, s32);

/* Global scene state word at gMainWorkspace+0x3C, cleared when this subsystem
 * tears down. */
struct SceneState {
    u8 _0[0x3C];
    u16 stateWord;
};
extern struct SceneState gMainWorkspace;

/* Release the entity's attached sub-object (work+4) when present, clear the
 * global scene state word, then run the entity's state handler (work+8). */
void sub_0809324C(void *entity)
{
    u8 *work = *(u8 **)((u8 *)entity + 0x3C);
    if (*(s32 *)(work + 4) != 0)
        freeMotionTracker(*(void **)(work + 4));
    gMainWorkspace.stateWord = 0;
    sub_080C31E0(entity, *(s32 *)(work + 8));
}
