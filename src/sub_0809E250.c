extern void sub_080C31E0(void *, void *);
struct S_10 { u8 pad[0x10]; u32 v; };
extern struct S_10 gMainWorkspace;

/* Command script step: when the current command slot holds 0x78, set the
 * global mode at gMainWorkspace+0x10 to 3 and run the entity's pending callback. */
void sub_0809E250(void *entity)
{
    s16 slot = *(s16 *)((u8 *)entity + 0x22);
    if (*(u8 *)((u8 *)entity + slot * 2 + 0x19) == 0x78) {
        gMainWorkspace.v = 3;
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
    }
}
