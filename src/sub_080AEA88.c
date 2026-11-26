void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallback;

/* Fade step: advance the fade timer on every second script step and refresh
 * the palette-blend registers at 0x03000830 (colour 0x3F40, weights
 * timer | (0x10 - timer) << 8); once the timer reaches 8, advance the script. */
void sub_080AEA88(void *entity)
{
    s16 stepIndex = *(s16 *)((u8 *)entity + 0x22);

    if ((((u8 *)entity)[stepIndex * 2 + 0x19] & 1) == 0) {
        ((u8 *)entity)[0x50]++;
    }

    {
        vu16 *blend = (vu16 *)0x03000830;
        u16 color = 0x3F40;
        u8 level;
        blend[2] = color;
        level = ((u8 *)entity)[0x50];
        blend[3] = level | ((0x10 - level) << 8);
        if (((u8 *)entity)[0x50] == 8) {
            stepIndex = *(s16 *)((u8 *)entity + 0x22);
            ((u8 *)entity)[stepIndex * 2 + 0x19] = 0;
            {
                void **interpreter = &gMainObjTimerCallback;
                sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *interpreter);
            }
        }
    }
}
