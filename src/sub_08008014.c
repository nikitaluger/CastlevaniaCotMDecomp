extern void sub_08010424(void);
extern void sub_08007ED0(void);
extern void sub_08007EF8(void);
extern void sub_080C31E0(void *, s32);

/* Scene setup tick: clear the two work-RAM areas, step the 4-frame delay
 * counter, then dispatch this object's action handler stored at +0x24. */
void sub_08008014(void *arg0) {
    sub_08010424();
    sub_08007ED0();
    sub_08007EF8();
    sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}
