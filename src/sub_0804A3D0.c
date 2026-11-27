s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, s32);
s32 sub_080141AC(void *, void *);
void sub_080C31E0(void *, void *);

/* Script/step dispatcher for an object: if its target is off-screen run the
 * recovery callback; otherwise, when the current display frame isn't handled,
 * switch to the 0x0866E40C step table, advance the script index and the part's
 * step byte, run the new step handler, restore the index, and finally sync the
 * sprite's screen coordinates to the camera. */
void sub_0804A3D0(void *arg0)
{
    u8 *obj = arg0;
    s32 sprite = *(s32 *)(obj + 0x38);
    s32 target = *(s32 *)(obj + 0x3C);

    if (sub_080141AC(sprite, target) == 1) {
        sub_080C31E0(arg0, *(void **)(obj + 0x24));
        return;
    }
    if (updateObjectDisplayState(sprite, target) == 0) {
        int stepByteOffset = 0x18;
        s32 idx;
        s32 partOffset;

        *(u32 *)(obj + 0x14) = 0x0866E40C;
        *(u16 *)(obj + 0x22) += 1;
        ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
        idx = *(s16 *)(obj + 0x22);
        partOffset = idx << 1;
        sub_080C31E0(arg0, *(void **)(*(u32 *)(obj + 0x14) + *(u8 *)(obj + stepByteOffset + partOffset) * 4));
        *(u16 *)(obj + 0x22) -= 1;
    }
    sub_08013C8C(arg0, sprite);
}
