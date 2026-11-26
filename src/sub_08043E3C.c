extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, void *);
extern u32 D_080CF570[];
extern void *gMainObjTimerCallback;

/* Drive this entity's attached object: start its animation, and when the
 * animation reaches frame 0x5A, push the next id from the state table into the
 * attached object and run its update script. */
void sub_08043E3C(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *owner = *(void **)(self + 0x38);
    u8 *attached = *(u8 **)(self + 0x3C);
    void *animState = attached + 0x34;
    u8 *dest = attached + 0x48;
    setAnimationFrame(owner, animState, 0, 0);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x5A) {
        s32 zero;
        u32 nextId;
        nextId = D_080CF570[*(u8 *)(self + 0x4C)];
        zero = 0;
        dest[0] = (u8)nextId;
        dest[1] = (u8)zero;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = (u8)zero;
        {
            void **idTable = &gMainObjTimerCallback;
            sub_080C31E4(self + 0x18, self + 0x22, *idTable);
        }
    }
}
