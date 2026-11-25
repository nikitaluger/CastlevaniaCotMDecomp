extern void sub_0808BB54(void);
extern void sub_080C31E0(void *, s32);

/* Set the scene state to 5, refresh the area's graphics setup, then dispatch
 * this object's action handler stored at +0x24. */
void sub_080BB7B0(void *arg0) {
    s32 *state = (s32 *)0x02025FF0;
    state[0x10] = 5;
    sub_0808BB54();
    sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}
