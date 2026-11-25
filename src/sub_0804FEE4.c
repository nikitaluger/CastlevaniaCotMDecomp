extern s32 sub_08011368(void *, void *, s32, s32);
extern void sub_0808DBF8(s32, s32, s32);
extern void sub_0808DC40(s32, s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern s16 sub_080C36E4(s16, s32);

/* Effect-object update: advances a frame counter, emits trailing particles along a
   rising/swaying path, then calls the object's end callback once the counter expires. */
void sub_0804FEE4(void *effect) {
    u8 *obj = (u8 *)effect;
    void *sprite = *(void **)(obj + 0x38);
    u8 *data = *(u8 **)(obj + 0x3C);
    u8 *anim = data + 0x34;
    s16 *frameCount = (s16 *)(data + 0x48);
    s32 sinVal;
    s32 spawnX;
    s32 spawnY;
    u32 nextFrame;
    sub_08011368(sprite, anim, 2, 0);
    sinVal = sub_080C31E0((*frameCount * 0x480) & 0xFFFF, *(s32 *)0x08671BFC);
    spawnX = *(s32 *)(data + 8) + sinVal * 0x14;
    spawnY = *(s32 *)(data + 0xC) - *frameCount * 0x3000 + (0x80 << 0xA);
    if (sub_080C36E4(*frameCount, 6) == 1) {
        sub_0808DBF8(spawnX, spawnY, 8);
    }
    if (*frameCount == 0x5A) {
        sub_0808DC40(*(s32 *)(data + 8), *(s32 *)(data + 0xC) + (s32)0xFFF00000, 8);
    }
    nextFrame = *(u16 *)frameCount + 1;
    *(u16 *)frameCount = nextFrame;
    if ((s16)nextFrame > 0x64) {
        sub_080C31E0((s32)obj, *(s32 *)(obj + 0x24));
    }
}
