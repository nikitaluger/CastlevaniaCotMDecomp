extern void sub_080C2E68(void *a, void *b, u32 c);
extern s32 sub_0800583C(s32);
extern s32 sub_08005820(s32);
extern void *sub_08091B80(s32, s32, s32, s32, s32);
extern void sub_080C31E0(void *, s32);

static inline u8 andBF(u8 b)
{
    u32 m = 0xBF;
    m &= b;
    return (u8)m;
}

void sub_08094A40(void *arg0)
{
    s32 stackArg;
    u32 offsets[16];
    u16 *flagPtr;
    s32 *offsets2;
    s32 byteOffset;
    s32 rawIndex;
    s32 xOffset;
    s32 yPos;
    s32 param;
    s32 rndParam;
    s32 xPos;
    s32 jitter;
    s32 signedIndex;
    s32 i;
    s32 index;
    void *sprite;
    void *motion;
    void *motionEx;

    sprite = *(void **)((u8 *)arg0 + 0x38);
    flagPtr = *(u16 **)((u8 *)arg0 + 0xAC);
    motion = *(void **)((u8 *)arg0 + 0x3C);
    motionEx = (u8 *)motion + 0x34;
    index = *(s16 *)((u8 *)motionEx + 0xC);
    if (index <= 3) {
        *(u8 *)(*(u8 **)((u8 *)motionEx + 4) + 1) = 0;
        *(u8 *)((u8 *)sprite + 0x2A) = andBF(*(u8 *)((u8 *)sprite + 0x2A));
    }
    sub_080C2E68(offsets, (void *)0x0810087C, 0x40);
    i = 0;
    offsets2 = (s32 *)((u8 *)offsets + 4);
    do {
        rawIndex = (*(s16 *)((u8 *)motionEx + 0xC) * 2) + i;
        signedIndex = rawIndex;
        if (rawIndex < 0) {
            signedIndex = rawIndex + 7;
        }
        byteOffset = (rawIndex - ((signedIndex >> 3) * 8)) * 8;
        xOffset = *(s32 *)((u8 *)offsets + byteOffset);
        param = *(s32 *)((u32)offsets2 + byteOffset);
        jitter = sub_0800583C(0x40000);
        xPos = *(s32 *)((u8 *)motion + 8);
        xPos += jitter;
        xOffset = (xOffset << 0x13) + 0xFFF40000;
        xPos += xOffset;
        jitter = sub_0800583C(0x40000);
        yPos = *(s32 *)((u8 *)motion + 0xC);
        yPos += jitter;
        param = (param << 0x13) + 0xFFFC0000;
        yPos += param;
        rndParam = sub_08005820(0x2000) + 0x800;
        stackArg = 0x4000;
        sub_08091B80(xPos, yPos, 0, rndParam, stackArg);
        i++;
    } while (i <= 1);
    index = (u16)*(u16 *)((u8 *)motionEx + 0xC) - 1;
    *(u16 *)((u8 *)motionEx + 0xC) = (u16)index;
    if ((s32)(index << 0x10) <= 0) {
        *flagPtr |= 4;
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
    }
}
