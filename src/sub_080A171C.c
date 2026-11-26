extern void sub_080C31E0(void *, void *);
struct GameState { u8 pad[0x10]; u32 mode; };
extern struct GameState gMainWorkspace;

/* Command script step: when the current command slot holds 0x78, set the
 * global mode at gMainWorkspace+0x10 to 4 and run the entity's pending callback. */
void sub_080A171C(void *entity)
{
    s16 slot = *(s16 *)((u8 *)entity + 0x22);
    if (*(u8 *)((u8 *)entity + slot * 2 + 0x19) == 0x78) {
        gMainWorkspace.mode = 4;
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
    }
}
