struct S_02025FF0 { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;
extern u32 gTrigFuncTable;
extern u16 gPoseAttrs[];

void *nextRandomWord();
s32 scaleByRandom(s32);
void stepAnimationTrack(s32, void*);
void advanceMotion(void*, s32);
void copyPoseAttrs(void*, s32);
void spawnFacingProjectile(s32, s32, s32, s32, s32, s32);
/* Indirect call: invokes the function pointer in the second argument with the first as its argument. */
s32 sub_080C31E0(void *, void *);

/* Enemy script update: advance the current animation entry, copy its pose
   attributes into the hit target, and spawn a projectile in a random direction
   when the script step's timer byte permits it. */
void enemyStepRandomProjectile(void *thread) {
    s32 sp8;
    s32 animIndex = 0;
    s32 *mainObj;
    void **work;
    void *animTrack;
    void **animTrackPtr;
    s32 *entryTable;
    s16 entryIndex;
    u8 entryAdd;
    s32 tableIndex;
    s32 tableBase;
    u32 byteOffset;
    u8 *entryPtr;
    u16 entryKind;
    void **target;
    u8 *flagPtr;
    s16 scriptIndex;
    u32 scriptOffset;
    u8 *scriptPtr;
    u32 speedScale;
    void *angle;
    s32 *trigFunc;
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

    mainObj = *(s32**)((u8*)thread + 0x38);
    sp8 = (s32)mainObj;
    work = *(void***)((u8*)thread + 0x3C);
    animTrack = (void*)((u8*)work + 0x34);
    stepAnimationTrack((s32)mainObj, animTrack);
    animTrackPtr = (void**)animTrack;
    entryTable = *(s32**)((u8*)animTrackPtr + 8);
    entryIndex = *(s16*)((u8*)animTrackPtr + 0x0E);
    entryAdd = *(u8*)((u8*)animTrackPtr + 1);
    tableIndex = entryIndex + entryAdd;
    tableBase = entryTable[0];
    byteOffset = (u32)(tableIndex * 4);
    entryPtr = (u8 *)(byteOffset + (u32)tableBase);
    entryPtr -= 4;
    entryKind = *(u16 *)(entryPtr + 2);
    target = *(void***)((u8*)work + 0x28);
    *(u8*)((u8*)target + 1) = 1;
    switch ((u32)entryKind) {
    case 15: animIndex = 1; break;
    case 17: case 19: animIndex = 2; break;
    case 21: animIndex = 3; break;
    }
    copyPoseAttrs(*(void ***)((u8 *)work + 0x28), animIndex*8 + (s32)&gPoseAttrs);
    flagPtr = (u8*)thread + 0x80;
    if (*flagPtr == 0) {
        if (entryKind == 0x0E) {
            advanceMotion(work, 0);
        }
        if (*flagPtr == 0) {
            scriptIndex = *(s16*)((u8*)thread + 0x22);
            scriptOffset = (u32)(scriptIndex * 2);
            scriptPtr = (u8 *)(scriptOffset + (u32)thread);
            if (!(*(scriptPtr + 0x19) & 1) && entryKind != 0x0E) {
                speedScale = ((u32)scaleByRandom(0x100000) + 0x80000) >> 8;
                angle = nextRandomWord();
                trigFunc = (s32*)0x08671BFC;
                angleCosArg = sub_080C31E0((void *)((u32)angle + 0x4000), (void *)*trigFunc);
                cosScaled = angleCosArg >> 8;
                cosVelocity = cosScaled * speedScale;
                velocityX = *(s32 *)((u8 *)work + 8) + cosVelocity;
                angleSinArg = sub_080C31E0(angle, (void *)*trigFunc);
                sinScaled = (angleSinArg >> 8) * speedScale;
                velocityY = *(s32 *)((u8 *)work + 0xC) + sinScaled;
                owner = gMainWorkspace.v;
                spawnFacingProjectile(owner, sp8, 1, velocityX, velocityY, 2);
            }
        }
    }
    if (*(u8*)animTrack & 2) {
        callback = *(void **)((u8*)thread + 0x24);
        sub_080C31E0(thread, callback);
    }
}
