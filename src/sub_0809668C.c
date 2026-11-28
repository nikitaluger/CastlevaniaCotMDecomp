extern void copyBytes(void *a, void *b, u32 c);
extern s32 scaleByRandom(s32);
extern s32 randomSignedOffset(s32);
extern void sub_08091E3C(s32, s32, s32, s32, s32, s32);
extern s32 signedRemainder(s16, s32);
extern void sub_080C31E0(void *, s32);

static inline u8 andBF(u8 b)
{
    u32 m = 0xBF;
    m &= b;
    return (u8)m;
}

/* Spawn two jittered particle objects each frame from a fixed offset table,
 * with a duration derived from the index; when the index expires, hand
 * control back to the entity's stored handler. */
void sub_0809668C(void *arg0)
{
    u32 offsets[16];
    s32 *offsets2;
    s32 byteOffset;
    s32 rawIndex;
    s32 xOffset;
    s32 yPos;
    s32 xPos;
    s32 param;
    s32 jitter;
    s32 signedIndex;
    s32 i;
    s32 duration;
    s16 index;
    s16 earlyIndex;
    void *sprite;
    void *motion;
    void *motionEx;

    sprite = *(void **)((u8 *)arg0 + 0x38);
    motion = *(void **)((u8 *)arg0 + 0x3C);
    motionEx = (u8 *)motion + 0x48;
    xPos = *(s16 *)((u8 *)motionEx + 0x14);
    earlyIndex = xPos;
    if (earlyIndex <= 2) {
        *(u8 *)(*(u8 **)((u8 *)motionEx + 4) + 1) = 0;
        *(u8 *)((u8 *)sprite + 0x2A) = andBF(*(u8 *)((u8 *)sprite + 0x2A));
    }
    copyBytes(offsets, (void *)0x08100B24, 0x40);
    i = 0;
    offsets2 = (s32 *)((u8 *)offsets + 4);
    do {
        rawIndex = (*(s16 *)((u8 *)motionEx + 0x14) * 2) + i;
        signedIndex = rawIndex;
        if (rawIndex < 0) {
            signedIndex = rawIndex + 7;
        }
        byteOffset = (rawIndex - ((signedIndex >> 3) * 8)) * 8;
        xOffset = *(s32 *)((u8 *)offsets + byteOffset);
        param = *(s32 *)((u32)offsets2 + byteOffset);
        jitter = randomSignedOffset(0x40000);
        xPos = *(s32 *)((u8 *)motion + 8);
        xPos += jitter;
        xOffset = (xOffset << 0x13) + 0xFFF40000;
        xPos += xOffset;
        jitter = randomSignedOffset(0x40000);
        yPos = *(s32 *)((u8 *)motion + 0xC);
        yPos += jitter;
        param = (param << 0x13) + 0xFFFC0000;
        yPos += param;
        param = scaleByRandom(0x2000);
        jitter = 0x800;
        param += jitter;
        index = *(s16 *)((u8 *)motionEx + 0x14);
        duration = signedRemainder(index, 3);
        sub_08091E3C(xPos, yPos, 0, param, 0x4000, (s16)duration);
        i++;
    } while (i <= 1);
    jitter = (u16) *(s16 *)((u8 *)motionEx + 0x14) - 1;
    *(s16 *)((u8 *)motionEx + 0x14) = (s16)jitter;
    if ((s32)(jitter << 0x10) <= 0) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
    }
}
