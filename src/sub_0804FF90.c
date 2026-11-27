void freeMotionTracker(void);
void unlinkAndFreeObject(void);
void sub_08016678(void *);
void sub_080C31E0(void *, s32);

/* Release the enemy's spawned child objects (three from each pool: slots
 * +0x28/+0x68/+0x6C and +0x2C/+0x70/+0x74), tear down the actor's sprite and
 * run the enemy's next action-script handler. */
void sub_0804FF90(void *arg0) {
    void *enemy;
    void *children;

    enemy = *((void **)((u8 *)arg0 + 0x3C));
    children = enemy + 0x48;
    if (*(s32 *)((u8 *)enemy + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)children + 0x20) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)children + 0x24) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)enemy + 0x2C) != 0) {
        freeMotionTracker();
    }
    if (*(s32 *)((u8 *)children + 0x28) != 0) {
        freeMotionTracker();
    }
    if (*(s32 *)((u8 *)children + 0x2C) != 0) {
        freeMotionTracker();
    }
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)((u8 *)enemy + 0x24));
}
