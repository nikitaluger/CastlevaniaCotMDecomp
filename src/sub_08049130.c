extern s32 sub_08005E80(s32);
extern s32 sub_0808DBB4(s32, s32, s32);
extern s32 sub_080C31E0(void *, s32);

/* Play sound 0x189, spawn an effect at the object's data position (with a
 * +0x20000 vertical offset), then run the object's cleanup callback. */
void sub_08049130(void *obj) {
    void *data;

    data = *(void **)((u8 *)obj + 0x3C);
    sub_08005E80(0x189);
    sub_0808DBB4(*(s32 *)((u8 *)data + 8), *(s32 *)((u8 *)data + 0xC) + 0x20000, 8);
    sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x24));
}
