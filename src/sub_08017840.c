extern u32 gScriptStepCallbackTable;

void _call_via_r2(void *, void *, u32);
void setAnimationFrame(u32, void *, u32, u32);
void sub_080C31E4(void *, void *, u32);
void sub_08016AAC(void *);
void sub_08016B24(void *);
s32 sub_08016598(void *, u16);

/* Set the object's animation to frame 5, copy over two of its state fields,
   clear the current step's progress and run the script interpreter. */
void sub_08017840(void *arg0) {
    u8 *self = (u8 *)arg0;
    u32 sprite = *(u32 *)(self + 0x38);
    u8 *field = *(u8 **)(self + 0x3C);
    u8 *anim = field + 0x34;
    u8 *state = field + 0x48;
    void **scriptFn;

    setAnimationFrame(sprite, anim, 5, 0);
    *(u32 *)(state + 0x08) = *(u32 *)(field + 0x08);
    *(u32 *)(state + 0x0C) = *(u32 *)(field + 0x0C);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    scriptFn = (void **)0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, (s32)*scriptFn);
}
