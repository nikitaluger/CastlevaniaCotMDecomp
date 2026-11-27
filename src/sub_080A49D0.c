s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, s32);
s32 sub_080141AC(void *, void *);
void sub_080C31E0(void *, void *);

/* Per-step update for a scripted object: if it has left the view, switch it to
 * its next script state; otherwise, when its display state does not own the
 * frame, switch to the 0x0866FF28 step table, advance the script index and the
 * step's phase byte, run the new step handler and restore the index. Finally
 * re-sync the sprite's screen coordinates to the camera. */
void sub_080A49D0(void *arg0)
{
    u8 *obj = arg0;
    s32 sprite = *(s32 *)(obj + 0x38);
    s32 state = *(s32 *)(obj + 0x3C);

    if (sub_080141AC(sprite, state) == 1) {
        sub_080C31E0(arg0, *(void **)(obj + 0x24));
        return;
    }
    if (updateObjectDisplayState(sprite, state) == 0) {
        int stepByteOffset = 0x18;
        s32 idx;
        s32 partOffset;

        *(u32 *)(obj + 0x14) = 0x0866FF28;
        *(u16 *)(obj + 0x22) += 1;
        ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
        idx = *(s16 *)(obj + 0x22);
        partOffset = idx << 1;
        sub_080C31E0(arg0, *(void **)(*(u32 *)(obj + 0x14) + *(u8 *)(obj + stepByteOffset + partOffset) * 4));
        *(u16 *)(obj + 0x22) -= 1;
    }
    sub_08013C8C(arg0, sprite);
}
