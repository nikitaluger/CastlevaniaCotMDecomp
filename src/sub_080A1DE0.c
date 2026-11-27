struct S_02025FF0 { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;
extern u32 gTrigFuncTable;
extern void *D_08101A58;

void *sub_080057F8();
s32 scaleByRandom(s32);
void stepAnimationTrack(s32, void*);
void advanceMotion(void*, s32);
void copyPoseAttrs(void*, s32);
void sub_080A2D30(s32, s32, s32, s32, s32, s32);
s32 sub_080C31E0(void *, void *);

/* Enemy script update: advance the current animation entry, copy its
   animation parameters, and spawn a projectile in a random direction when the
   script byte permits it. */
void sub_080A1DE0(void *arg0) {
    s32 sp8;
    s32 animIndex = 0;
    s32 *mainObj;
    void **p3C;
    void *p34;
    void **p34Ptr;
    s32 *entryTable;
    s16 entryIndex;
    u8 entryAdd;
    s32 tableIndex;
    s32 tableBase;
    u32 byteOffset;
    u8 *entryPtr;
    u16 tableValue;
    void **p28;
    u8 *flagPtr;
    s16 scriptIndex;
    u32 scriptOffset;
    u8 *scriptPtr;
    u32 speedScale;
    void *randomAngle;
    s32 *angleFunc;
    s32 angleCosArg;
    s32 cosScaled;
    s32 cosVelocity;
    s32 angleSinArg;
    s32 sinScaled;
    s32 sinVelocity;
    s32 velocityX;
    s32 velocityY;
    s32 owner;
    void *callback;

    mainObj = *(s32**)((u8*)arg0 + 0x38);
    sp8 = (s32)mainObj;
    p3C = *(void***)((u8*)arg0 + 0x3C);
    p34 = (void*)((u8*)p3C + 0x34);
    stepAnimationTrack((s32)mainObj, p34);
    p34Ptr = (void**)p34;
    entryTable = *(s32**)((u8*)p34Ptr + 8);
    entryIndex = *(s16*)((u8*)p34Ptr + 0x0E);
    entryAdd = *(u8*)((u8*)p34Ptr + 1);
    tableIndex = entryIndex + entryAdd;
    tableBase = entryTable[0];
    byteOffset = (u32)(tableIndex * 4);
    entryPtr = (u8 *)(byteOffset + (u32)tableBase);
    entryPtr -= 4;
    tableValue = *(u16 *)(entryPtr + 2);
    p28 = *(void***)((u8*)p3C + 0x28);
    *(u8*)((u8*)p28 + 1) = 1;
    switch ((u32)tableValue) {
    case 15: animIndex = 1; break;
    case 17: case 19: animIndex = 2; break;
    case 21: animIndex = 3; break;
    }
    copyPoseAttrs(*(void ***)((u8 *)p3C + 0x28), animIndex*8 + (s32)&D_08101A58);
    flagPtr = (u8*)arg0 + 0x80;
    if (*flagPtr == 0) {
        if (tableValue == 0x0E) {
            advanceMotion(p3C, 0);
        }
        if (*flagPtr == 0) {
            scriptIndex = *(s16*)((u8*)arg0 + 0x22);
            scriptOffset = (u32)(scriptIndex * 2);
            scriptPtr = (u8 *)(scriptOffset + (u32)arg0);
            if (!(*(scriptPtr + 0x19) & 1) && tableValue != 0x0E) {
                speedScale = ((u32)scaleByRandom(0x100000) + 0x80000) >> 8;
                randomAngle = sub_080057F8();
                angleFunc = (s32*)0x08671BFC;
                angleCosArg = sub_080C31E0((void *)((u32)randomAngle + 0x4000), (void *)*angleFunc);
                cosScaled = angleCosArg >> 8;
                cosVelocity = cosScaled * speedScale;
                velocityX = *(s32 *)((u8 *)p3C + 8) + cosVelocity;
                angleSinArg = sub_080C31E0(randomAngle, (void *)*angleFunc);
                sinScaled = (angleSinArg >> 8) * speedScale;
                velocityY = *(s32 *)((u8 *)p3C + 0xC) + sinScaled;
                owner = gMainWorkspace.v;
                sub_080A2D30(owner, sp8, 1, velocityX, velocityY, 2);
            }
        }
    }
    if (*(u8*)p34 & 2) {
        callback = *(void **)((u8*)arg0 + 0x24);
        sub_080C31E0(arg0, callback);
    }
}
