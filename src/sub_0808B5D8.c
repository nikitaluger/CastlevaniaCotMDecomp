struct InputButtonState {
    u8 pad[0x28];
    u16 pressed;      /* +0x28: buttons newly pressed this frame */
    u16 prevKeys;     /* +0x2A: button state on the previous frame */
    u16 activeKeys;   /* +0x2C: buttons to act on (fresh press or auto-repeat) */
    u16 heldKeys;     /* +0x2E: buttons currently held */
    u8 repeatTimer;   /* +0x30: frames the held buttons have been stable */
    u8 pad2[3];
    u16 currentKeys;  /* +0x34: current button state (from demo playback) */
};
extern struct InputButtonState D_02025FF0;

/* Refresh the button state: publish the buttons pressed this frame and re-emit
 * the held buttons as an auto-repeat once they have been stable for 30 frames. */
void sub_0808B5D8(void)
{
    struct InputButtonState *in = &D_02025FF0;
    u16 keys = in->currentKeys;
    u16 prevKeys = in->prevKeys;
    u16 pressed;
    u16 newButtons;
    u32 zero = 0;
    pressed = keys;
    pressed &= ~prevKeys;
    in->pressed = pressed;
    in->prevKeys = keys;
    in->activeKeys = pressed;
    {
        u16 mask = 0x3FF;
        newButtons = mask;
        newButtons &= pressed;
        if (newButtons == 0)
        {
            mask &= keys;
            if (in->heldKeys == mask)
            {
                u32 count = in->repeatTimer + 1;
                in->repeatTimer = count;
                if ((u8)count == 0x1E)
                {
                    in->activeKeys = mask;
                    in->heldKeys = mask;
                    in->repeatTimer = 0x1B;
                }
            }
            else
            {
                in->repeatTimer = zero;
                in->heldKeys = newButtons;
            }
        }
        else
        {
            in->heldKeys = keys & mask;
            in->repeatTimer = zero;
        }
    }
}
