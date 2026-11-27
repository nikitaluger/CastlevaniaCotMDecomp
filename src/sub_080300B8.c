void unlinkAndFreeObject(void);
void freeMotionTracker(void);
void sub_08016678(void *);
void _call_via_r1(void *, void *);

/* Release the actor's first two linked objects, set flag 0x10 on two more,
 * then clean up and dispatch the callback stored in its work state. */
void sub_080300B8(void *arg0)
{
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *extra = work + 0x48;
    {
        void *linked = *(void **)(work + 0x28);
        if (linked != NULL) unlinkAndFreeObject();
    }
    {
        void *linked = *(void **)(work + 0x2C);
        if (linked != NULL) freeMotionTracker();
    }
    {
        void *linked = *(void **)(work + 0x48);
        if (linked != NULL) {
            s32 flags = 0x10 | *(u16 *)((u8 *)linked + 0x6C);
            *(u16 *)((u8 *)linked + 0x6C) = flags;
        }
    }
    {
        void *linked = *(void **)(extra + 4);
        if (linked != NULL) {
            s32 flags = 0x10 | *(u16 *)((u8 *)linked + 0x6C);
            *(u16 *)((u8 *)linked + 0x6C) = flags;
        }
    }
    sub_08016678(arg0);
    _call_via_r1(arg0, *(void **)(work + 0x24));
}
