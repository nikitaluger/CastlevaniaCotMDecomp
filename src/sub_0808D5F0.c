void sub_080C31E0(void *, void *);

struct S_02021E90_1460 {
    u8 pad[0x1460];
    u8 keyRepeat0;
    u8 keyRepeat1;
    u8 keyRepeat2;
    u8 keyRepeat3;
    u8 keyRepeat4;
    u8 keyRepeat5;
    u8 keyRepeat6;
    u8 keyRepeat7;
};
extern struct S_02021E90_1460 gCameraState;

/* Clear the eight key-repeat counters (the two words at gCameraState+0x1460)
 * so the next button press starts fresh, then advance to the actor's next
 * state handler. */
void sub_0808D5F0(void *arg0)
{
    gCameraState.keyRepeat0 = 0;
    gCameraState.keyRepeat4 = 0;
    gCameraState.keyRepeat2 = 0;
    gCameraState.keyRepeat6 = 0;
    gCameraState.keyRepeat1 = 0;
    gCameraState.keyRepeat5 = 0;
    gCameraState.keyRepeat3 = 0;
    gCameraState.keyRepeat7 = 0;
    sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
}
