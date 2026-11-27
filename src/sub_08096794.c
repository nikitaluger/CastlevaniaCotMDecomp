extern void freeMotionTracker(void *obj);
extern void sub_080C050C(s32 id);
extern void sub_080C31E0(void *entity, s32 handler);

/* Effect teardown: free the effect's sub-object, release its resource and hand
 * control back to the handler that was active before this one. */
void sub_08096794(void *entity) {
    void *work = *(void **)((u8 *)entity + 0x3C);

    if (*(s32 *)((u8 *)work + 0x4C) != 0) {
        freeMotionTracker(*(void **)((u8 *)work + 0x4C));
    }
    sub_080C050C(0x1BE);
    sub_080C31E0(entity, *(s32 *)((u8 *)work + 0x24));
}
