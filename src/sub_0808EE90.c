extern void freeMotionTracker(void);
extern void unlinkAndFreeObject(void);
extern void sub_080C050C(s32);
extern void sub_080C31E0(void *, s32);

/* Tear down the object's attached sub-objects at group+0x38 and group+0x3C,
 * release resource 0x1B9, then dispatch the object's handler. */
void sub_0808EE90(void *arg0)
{
    void *field;
    void *state;

    field = *(void **)((u8 *)arg0 + 0x3C);
    state = (u8 *)field + 0x34;
    if (*(s32 *)((u8 *)state + 4) != 0)
    {
        freeMotionTracker();
    }
    if (*(s32 *)((u8 *)state + 8) != 0)
    {
        unlinkAndFreeObject();
    }
    sub_080C050C(0x1B9);
    sub_080C31E0(arg0, *(s32 *)((u8 *)field + 0x24));
}
