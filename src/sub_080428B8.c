extern void freeMotionTracker(void);
extern void unlinkAndFreeObject(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

/* Tears down an entity: unlinks the objects recorded in its state (+0x28,
 * +0x2C and +0x50..+0x58) from the global object lists, clears the state and
 * invokes the callback at +0x24. */
void sub_080428B8(void *entity) {
    u8 *childRef;
    s32 remaining;
    void *state;

    state = *(void **)((u8 *)entity + 0x3C);
    if (*(s32 *)((u8 *)state + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)state + 0x2C) != 0) {
        freeMotionTracker();
    }
    childRef = (u8 *)state + 0x50;
    remaining = 1;
    do {
        if (*(s32 *)childRef != 0) {
            unlinkAndFreeObject();
        }
        childRef += 4;
        remaining -= 1;
    } while (remaining >= 0);
    sub_08016678(entity);
    sub_080C31E0(entity, *(s32 *)((u8 *)state + 0x24));
}
