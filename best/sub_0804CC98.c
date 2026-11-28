extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void initWorkStateForKind(void *, void *, void *, s32, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void registerScriptObject(void *, s32);
extern void sub_080C31E4(void *, void *, u32);
extern void updateScriptedEffectObject(void);
extern s32 nextRandomWord(void);
extern void setSpriteFlipForDirection(void *, void *);

extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallbacks[];

struct Part {
    u8 _0; u8 f1; u8 f2; u8 f3;
    u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE;
    u32 f10;
    u8 _14[0x0C];
};
struct Entity {
    u8 _0[4];
    u16 f4;
    u8 _6[2];
    u32 f08; u32 f0C;
    u8 _10[0x0C];
    s16 f1C;
    u8 _1E[0x0A];
    struct Part *f28;
    u8 _2C[8];
    u8 f34;
};
struct PartTable { u16 f0; u16 f2; u16 f4; u8 _6[0x0E]; };
extern struct PartTable gSpriteKindTable[];

void sub_0804CC98(u8 *scriptObj) {
    u8 *sprite;
    struct Entity *work;
    u8 *anim;
    u8 *s;
    struct Part *part;
    s32 workParam;
    u8 *partAttrs;
    u8 *cameraState, *frameCounter, *scrollXRows, *scrollYRows;
    u32 scrollRow;

    workParam = *(s32 *)(scriptObj + 0xAC);
    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    *(void **)(scriptObj + 0x38) = sprite;
    allocWorkSlot(scriptObj, 0, 0x48, 0);
    if (*(u32 *)(scriptObj + 0x3C) == 0) goto fail;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    work = *(struct Entity **)(scriptObj + 0x3C);
    anim = (u8 *)work + 0x34;
    installUpdateHandler(scriptObj, (u8 *)work, (void *)updateScriptedEffectObject);
    initWorkStateForKind(scriptObj, sprite, (u8 *)work, workParam, 0x35);
    initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + *(s16 *)((u8 *)work + 0x1C) * 0xC);
    setAnimationFrame(sprite, anim, 0, 1);
    if (nextRandomWord() & 1) {
        *(u32 *)((u8 *)work + 0x10) = 0x8000;
    } else {
        *(u32 *)((u8 *)work + 0x10) = 0x080CF9BC;
    }
    *(u16 *)(scriptObj + 0x4C) = 0x80;
    setSpriteFlipForDirection(sprite, (void *)*(u32 *)((u8 *)work + 0x10));
    partAttrs = (u8 *)0x080CF9BC;
    part = allocEffectPart();
    work->f28 = part;
    if (part == NULL) goto fail;
    goto body;

fail:
    sub_080C31E0(scriptObj, *(void **)(scriptObj + 0x24));
    return;

body:
    part->f1 = 5;
    work->f28->f2 = 8;
    work->f28->f3 = 1;
    {
        workParam = 0;
        work->f28->f4 = gSpriteKindTable[*(s16 *)((u8 *)work + 0x1C)].f0;
        work->f28->f6 = *(u16 *)(partAttrs + 0);
        work->f28->f8 = *(u16 *)(partAttrs + 2);
        work->f28->fA = *(u16 *)(partAttrs + 4);
        work->f28->fC = *(u16 *)(partAttrs + 6);
        work->f28->fE = gSpriteKindTable[*(s16 *)((u8 *)work + 0x1C)].f4;
    }
    work->f28->f10 = (u32)sprite;
    {
        cameraState = gCameraState;
        frameCounter = gMainWorkspace;
        frameCounter += 0x18A8;
        scrollRow = ((u32)*frameCounter + 1) * 0x40;
        scrollXRows = cameraState + 0x1278;
        *(u32 *)(sprite + 0x14) = *(u32 *)((u8 *)work + 0x08) - ((*(u32 *)(scrollXRows + scrollRow) + 0x8000) & 0xFFFF0000);
        scrollRow = ((u32)*frameCounter + 1) * 0x40;
        scrollYRows = cameraState + 0x127C;
        *(u32 *)(sprite + 0x18) = *(u32 *)((u8 *)work + 0x0C) - ((*(u32 *)(scrollYRows + scrollRow) + 0xFFFF8000) & 0xFFFF0000);
    }
    do { registerScriptObject(scriptObj, 0); } while (0);
    {
        u16 flags = *(u16 *)(scriptObj + 2);
        flags |= 0x1000;
        *(u16 *)(scriptObj + 2) = flags;
    }
    *(u8 *)((u32)(*(s16 *)(scriptObj + 0x22) * 2) + (u32)scriptObj + 0x19) = (u8)workParam;
    {
        u32 *scriptCallback = (u32 *)gMainObjTimerCallbacks;
        u8 *scriptState = scriptObj + 0x18;
        sub_080C31E4(scriptState, scriptObj + 0x22, *scriptCallback);
        {
            u8 *stepBytePtr = (u8 *)((u32)(*(s16 *)(scriptObj + 0x22) * 2) + (u32)scriptObj + 0x19);
            *stepBytePtr = (u8)(*stepBytePtr + 1);
            stepBytePtr = scriptState;
            stepBytePtr += *(s16 *)(scriptObj + 0x22) * 2;
            {
                u8 stepByte = *stepBytePtr;
                void *cleanupFn = ((void **)*(void **)(scriptObj + 0x14))[stepByte];
                sub_080C31E0(scriptObj, cleanupFn);
            }
        }
    }
}
