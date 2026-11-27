extern s32 sub_08015974();
extern s32 unlinkAndFreeObject();
extern s32 sub_08016678(void *);
extern s32 sub_0803B1CC(void *);
extern s32 sub_080C31E0(void *, s32);

// Releases the entity's graphics state: runs optional cleanup callbacks on the
// state, then invokes the entity's fail callback.
void sub_08033498(void *entity) {
    void *state = *(void **)((u8 *)entity + 0x3C);
    if (*(s32 *)((u8 *)state + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    sub_0803B1CC(state + 0x54);
    if (*(s32 *)((u8 *)state + 0x2C) != 0) {
        sub_08015974();
    }
    sub_08016678(entity);
    sub_080C31E0(entity, *(s32 *)((u8 *)state + 0x24));
}
