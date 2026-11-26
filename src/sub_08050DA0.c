extern void setAnimationFrame(void *a, void *b, s32 c, s32 d);
extern void sub_08051E94(void *a, void *b, s32 c, s32 d);
extern void sub_08051F98(void *a, void *b, s32 c, s32 d, s32 e);

/* Trail-emitter state: once its 12-frame wait timer has elapsed, switch to
 * pose 6, lay down an 8-segment trail from its current heading, arm a fresh
 * 12-frame timer and advance to the next state. */
void sub_08050DA0(u8 *arg0)
{
    void *gfx = *(void **)(arg0 + 0x38);
    u8 *work = *(u8 **)(arg0 + 0x3C);
    u8 *anim = work + 0x34;
    u8 *trail = work + 0x48;
    s16 stateIndex = *(s16 *)(arg0 + 0x22);
    if (*(u8 *)(arg0 + stateIndex * 2 + 0x19) > 0x0B) {
        setAnimationFrame(gfx, anim, 6, 0);
        sub_08051E94(arg0, work + 0xF0, *(s32 *)(trail + 0xC), 0);
        sub_08051F98(arg0, trail, 0xC, 2, 1);
    }
}
