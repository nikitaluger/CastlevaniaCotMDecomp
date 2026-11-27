extern s32 sub_08011650(s32);
extern s32 sub_08015974();
extern s32 unlinkAndFreeObject();
extern s32 sub_08016678(void *);
extern s32 sub_080C31E0(void *, s32);

/* Release an entity's graphics state: run the optional cleanup callbacks on
 * its state block, release the sprite, then invoke the entity's fail callback. */
void releaseActorEffectSubObject(void *entity) {
    s32 sprite = *(s32 *)((u8 *)entity + 0x38);
    void *state = *(void **)((u8 *)entity + 0x3C);
    if (*(s32 *)((u8 *)state + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    sub_08011650(sprite);
    if (*(s32 *)((u8 *)state + 0x2C) != 0) {
        sub_08015974();
    }
    sub_08016678(entity);
    sub_080C31E0(entity, *(s32 *)((u8 *)state + 0x24));
}
