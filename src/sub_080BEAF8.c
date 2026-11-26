extern u8 gCameraState[];
extern u32 D_086707B0[];  /* table of Thumb state-handler pointers */

/* Run the state handler selected by the mode byte at gCameraState + 0x1361. */
void sub_080BEAF8(void) {
    u32 *handlers = D_086707B0;
    u8 *base = gCameraState;
    u32 off = 0x1361;
    u8 handler = *(base + off);
    extern void sub_080C31DC(void *);
    sub_080C31DC((void *)handlers[handler]);
}
