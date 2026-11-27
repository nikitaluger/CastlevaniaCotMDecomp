extern void *allocSpriteObject(void);            /* create the sprite object */
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void initWorkStateForKind(void *, void *, void *, s32, s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32); /* set animation/frame control */
extern void *allocEffectPart(void);            /* allocate a part object */
extern void sub_080C31E0(void *, void *);   /* cleanup callback */
extern void registerScriptObject(void *, s32);
extern void sub_080C31E4(void *, void *, u32); /* run a script handler */
extern void sub_08014290(void);

extern u8 gCameraState[];                     /* scroll-offset table */
extern u8 gMainWorkspace[];                     /* global game state */
extern u8 gSpriteAnimDataTable[];                     /* frame-control data */
extern u8 D_080CF968[];                     /* part parameter table */
extern u32 gMainObjTimerCallbacks[];                    /* step-script operation */

struct Part {
    u8 _0; u8 f1; u8 f2; u8 f3;
    u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE;
    u32 f10;
    u8 _14[0x0C];
};
struct Entity {
    u8 _0[8];
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

/* Creates a sprite and part object for an entity, configures the part's parameters and
   screen position, then advances the object's first script step. */
void createEntitySpriteAndPart(u8 *obj) {
    u8 *sprite;
    struct Entity *entity;
    u8 *anim;
    u8 *s;
    struct Part *part;
    s32 param;
    u8 *partParamTable;
    u8 *scrollTbl, *frameCounterPtr, *scrollXBase, *scrollYBase;
    u32 scrollRow;

    param = *(s32 *)(obj + 0xAC);
    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    *(void **)(obj + 0x38) = sprite;
    allocWorkSlot(obj, 0, 0x58, 0);
    if (*(u32 *)(obj + 0x3C) == 0) goto fail;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    entity = *(struct Entity **)(obj + 0x3C);
    anim = (u8 *)entity + 0x34;
    installUpdateHandler(obj, (u8 *)entity, (void *)sub_08014290);
    initWorkStateForKind(obj, sprite, (u8 *)entity, param, 0x10);
    initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + *(s16 *)((u8 *)entity + 0x1C) * 0xC);
    setAnimationFrame(sprite, anim, 0, 0);
    partParamTable = D_080CF968;
    part = allocEffectPart();
    entity->f28 = part;
    if (part == NULL) goto fail;
    goto body;

fail:
    sub_080C31E0(obj, *(void **)(obj + 0x24));
    return;

body:
    part->f1 = 5;
    entity->f28->f2 = 8;
    entity->f28->f3 = 1;
    {
        param = 0;
        entity->f28->f4 = gSpriteKindTable[*(s16 *)((u8 *)entity + 0x1C)].f0;
        entity->f28->f6 = *(u16 *)(partParamTable + 0);
        entity->f28->f8 = *(u16 *)(partParamTable + 2);
        entity->f28->fA = *(u16 *)(partParamTable + 4);
        entity->f28->fC = *(u16 *)(partParamTable + 6);
        entity->f28->fE = gSpriteKindTable[*(s16 *)((u8 *)entity + 0x1C)].f4;
    }
    entity->f28->f10 = (u32)sprite;
    {
        scrollTbl = gCameraState;
        frameCounterPtr = gMainWorkspace;
        frameCounterPtr += 0x18A8;
        scrollRow = ((u32)*frameCounterPtr + 1) * 0x40;
        scrollXBase = scrollTbl + 0x1278;
        *(u32 *)(sprite + 0x14) = *(u32 *)((u8 *)entity + 0x08) - ((*(u32 *)(scrollXBase + scrollRow) + 0x8000) & 0xFFFF0000);
        scrollRow = ((u32)*frameCounterPtr + 1) * 0x40;
        scrollYBase = scrollTbl + 0x127C;
        *(u32 *)(sprite + 0x18) = *(u32 *)((u8 *)entity + 0x0C) - ((*(u32 *)(scrollYBase + scrollRow) + 0xFFFF8000) & 0xFFFF0000);
    }
    registerScriptObject(obj, 0);
    {
        u16 flags = *(u16 *)(obj + 2);
        flags |= 0x1000;
        *(u16 *)(obj + 2) = flags;
    }
    *(u8 *)((u32)(*(s16 *)(obj + 0x22) * 2) + (u32)obj + 0x19) = (u8)param;
    {
        u32 *scriptCallback = (u32 *)gMainObjTimerCallbacks;
        u8 *scriptState = obj + 0x18;
        sub_080C31E4(scriptState, obj + 0x22, *scriptCallback);
        {
            u8 *stepBytePtr = (u8 *)((u32)(*(s16 *)(obj + 0x22) * 2) + (u32)obj + 0x19);
            *stepBytePtr = (u8)(*stepBytePtr + 1);
            stepBytePtr = scriptState;
            stepBytePtr += *(s16 *)(obj + 0x22) * 2;
            {
                u8 stepByte = *stepBytePtr;
                void *cleanupFn = ((void **)*(void **)(obj + 0x14))[stepByte];
                sub_080C31E0(obj, cleanupFn);
            }
        }
    }
}
