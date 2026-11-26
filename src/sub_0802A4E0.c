extern s32 sub_08014990(void *);
extern void setAnimationFrame(s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 gMainObjTimerCallback;

/* Runs a state check on the object's linked state at +0x3C; when bit 1 is set,
 * writes a facing-dependent +/-0x8000 offset into that state, clears this
 * object's frame counter and refills its frame slot from the char-data table. */
void sub_0802A4E0(void *arg0) {
    u8 *obj = (u8 *)arg0;
    s32 context = *(s32 *)(obj + 0x38);
    u8 *target = *(u8 **)(obj + 0x3C);
    u8 *result = target + 0x34;
    void **charData;

    setAnimationFrame(context, result, 0x0D, 0);
    if (*result & 2) {
        if (sub_08014990(context) > 0) {
            *(s32 *)(target + 0x10) = 0x8000;
        } else {
            *(s32 *)(target + 0x10) = (s32)0xFFFF8000;
        }
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = 0;
        charData = (void **)0x08671BB0;
        sub_080C31E4(obj + 0x18, obj + 0x22, (s32)*charData);
    }
}
