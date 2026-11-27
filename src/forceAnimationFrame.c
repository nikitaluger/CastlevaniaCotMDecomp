extern s32 sub_08010F5C(s32 obj, void *desc, s32 frameEntry, s32 gfxSrc, s32 gfxDst, s32 baseTile, s32 flags);

/* Point a graphics descriptor at animation frame `frameIndex`: store the index
 * in the descriptor and resolve the frame entry (frameGroup->frames + index*4)
 * together with its gfx source/destination for sub_08010F5C. */
void forceAnimationFrame(s32 obj, u8 *desc, u16 frameIndex, u8 flags) {
    u16 index = frameIndex;
    u8 *frameGroup;

    *(u16 *)(desc + 0xE) = index;
    frameGroup = *(u8 **)(desc + 8);
    sub_08010F5C(obj, desc, *(s32 *)(frameGroup + 0) + ((s32)(index << 16) >> 14), *(s32 *)(frameGroup + 4), *(s32 *)(frameGroup + 8), *(s32 *)(desc + 0x10), (s32)flags);
}
