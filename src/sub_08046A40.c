void sub_08015974(void);
void unlinkAndFreeObject(void);
void sub_08016678(void *);
void sub_080C31E0(void *, s32);

/* Release the enemy's spawned child objects (slots +0x28 and +0x48..+0x54, plus
 * the list entry at +0x2C), tear down the actor's sprite and run the enemy's
 * next action-script handler. */
void sub_08046A40(void *arg0) {
    void *enemy;
    void *children;

    enemy = *((void **)((u8 *)arg0 + 0x3C));
    children = enemy + 0x48;
    if (*(s32 *)((u8 *)enemy + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)enemy + 0x48) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)children + 4) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)children + 8) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)children + 0xC) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)enemy + 0x2C) != 0) {
        sub_08015974();
    }
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)((u8 *)enemy + 0x24));
}
