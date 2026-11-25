extern void sub_080161F0(void *obj);
extern void sub_0803F24C(void *entity);
extern void sub_080C31E0(void *entity, s32 handler);

/* Teardown: free the effect's sub-object at +0x28, clear the linked object's
 * active flag, then hand control to the next handler. */
void sub_0803F228(void *entity) {
    void *work = *(void **)((u8 *)entity + 0x3C);
    if (*(s32 *)((u8 *)work + 0x28) != 0) {
        sub_080161F0(*(void **)((u8 *)work + 0x28));
    }
    sub_0803F24C(entity);
    sub_080C31E0(entity, *(s32 *)((u8 *)work + 0x24));
}
