extern void decompressToVram(void *src, void *dst);

/* Graphics state used by the transition scripts: graphics-header word at
 * +0x1262, the two palette colour indices at +0x143A/+0x143B, the script frame
 * counter at +0x1454 and the transition flags at +0x145C. */
struct TransitionState {
    u8 pad_0[0x1262];
    u16 header1262;
    u8 pad_1264[0x1D6];
    u8 colorA;
    u8 colorB;
    u8 pad_143C[0x18];
    s32 frame;
    u8 pad_1458[4];
    u8 flags;
};
extern struct TransitionState gCameraState;

/* Transition step: advance the script frame and keep going. */
s32 sub_08060408(void)
{
    gCameraState.frame += 1;
    return 0;
}

/* Transition step: swap the two palette colour indices (palette flash) and
 * advance the script frame. */
s32 sub_08060438(void)
{
    u8 tmp = gCameraState.colorB;
    gCameraState.colorB = gCameraState.colorA;
    gCameraState.colorA = tmp;
    gCameraState.frame += 1;
    return 0;
}

/* Transition step: upload the compressed sprite tileset at 0x084427D8 to the
 * tile slot selected by the graphics header, raise transition flag 8, advance
 * the frame and report the step as finished. */
s32 sub_080603B8(void)
{
    gCameraState.frame += 1;
    gCameraState.flags |= 8;
    decompressToVram((void *)0x084427D8, (void *)(((gCameraState.header1262 & 0x1F00) << 3) + 0x06000C80));
    return 2;
}

/* Transition step: swap the two palette colour indices back and advance the
 * script frame. */
s32 sub_0806046C(void)
{
    u8 tmp = gCameraState.colorA;
    gCameraState.colorA = gCameraState.colorB;
    gCameraState.colorB = tmp;
    gCameraState.frame += 1;
    return 0;
}
