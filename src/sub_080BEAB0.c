extern void _call_via_r0(void *);
extern u8 gCameraState[];
extern u32 D_0867078C[];
extern vu8 D_04000004;

/* Drive the VCOUNT interrupt from the current scanline-effect mode byte
 * (gCameraState + 0x1360): disable it for mode 0, otherwise enable it and call
 * that mode's handler from the 0x0867078C table. */
void sub_080BEAB0(void)
{
    u8 mode = gCameraState[0x9B * 0x20];
    if (mode == 0)
    {
        D_04000004 &= 0xDF;
    }
    else
    {
        D_04000004 |= 0x20;
        {
            u32 *vcountHandlers = (u32 *)D_0867078C;
            u8 mode2 = gCameraState[0x9B * 0x20];
            _call_via_r0((void *)vcountHandlers[mode2]);
        }
    }
}
