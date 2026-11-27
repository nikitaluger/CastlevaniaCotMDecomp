extern void sub_080C31E0(void *, s32);
extern void unlinkAndFreeObject(void);

struct WorldState { u8 _pad[0x18BC]; u16 count; };
extern struct WorldState gMainWorkspace;

/* If the work block holds a linked object, free it; when the state block's
 * type is 1, decrement the global counter; then switch to the entity's state
 * handler at work+0x24. */
void sub_08047FF0(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *state = work + 0x48;

    if (*(u32 *)(work + 0x28) != 0) unlinkAndFreeObject();
    if (*(s16 *)(state + 0x0A) == 1) {
        gMainWorkspace.count -= 1;
    }
    sub_080C31E0(self, *(u32 *)(work + 0x24));
}
