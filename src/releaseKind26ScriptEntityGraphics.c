extern void freeMotionTracker(void *);
extern void unlinkAndFreeObject(void *);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

/* Free every channel the object currently owns: the three animation slots and
 * the two list entries, then restart the animation timer and continue the
 * script at the stored handler. */
void releaseKind26ScriptEntityGraphics(void *arg0) {
    void *base;
    void *anim;

    base = *(void **)((u8 *)arg0 + 0x3C);
    anim = (u8 *)base + 0x48;
    if (*(s32 *)((u8 *)base + 0x28) != 0) {
        unlinkAndFreeObject(*(void **)((u8 *)base + 0x28));
    }
    if (*(s32 *)((u8 *)anim + 0xC) != 0) {
        unlinkAndFreeObject(*(void **)((u8 *)anim + 0xC));
    }
    if (*(s32 *)((u8 *)anim + 0x10) != 0) {
        unlinkAndFreeObject(*(void **)((u8 *)anim + 0x10));
    }
    if (*(s32 *)((u8 *)anim + 0x14) != 0) {
        unlinkAndFreeObject(*(void **)((u8 *)anim + 0x14));
    }
    if (*(s32 *)((u8 *)base + 0x2C) != 0) {
        freeMotionTracker(*(void **)((u8 *)base + 0x2C));
    }
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)((u8 *)base + 0x24));
}
