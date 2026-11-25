extern void sub_0808BB54(void);
extern void sub_080B7614(void);
extern void sub_080C31E0(void *, s32);

/* Count a timer at +0x5C down by 0x400 and advance the value at +0x6C by 0x200;
 * once the timer falls to 0x7FF or below, refresh the entity's state. */
void sub_080B6264(void *arg0)
{
    s32 timer;

    timer = *((s32 *)((u8 *)arg0 + 0x5C)) + 0xFFFFFC00;
    *((s32 *)((u8 *)arg0 + 0x5C)) = timer;
    *((s32 *)((u8 *)arg0 + 0x6C)) = (s32)(*((s32 *)((u8 *)arg0 + 0x6C)) + 0x200);
    if (timer <= 0x7FF) {
        sub_080B7614();
        sub_0808BB54();
        sub_080C31E0(arg0, *((s32 *)((u8 *)arg0 + 0x24)));
    }
}
