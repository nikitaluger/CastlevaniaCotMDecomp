extern u8 gCameraState[];    /* scroll-offset table */
extern u8 gMainWorkspace[];    /* global game state */
extern u32 gSpriteAnimDataTable[];   /* frame-control data */
extern u32 gMainObjTimerCallback[];   /* step-script operation */

extern void allocWorkSlot(void *, u32, u32, u32);
extern void *allocSpriteObject(void *);          /* create the sprite object */
extern void installUpdateHandler(void *, void *, void *);
extern void initWorkStateForKind(void *, void *, void *, void *, u32);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, u32, u32); /* set animation/frame control */
extern void sub_0803AEF0(void *, void *, void *);
extern void sub_0803AF70(void *, void *, void *, void *);
extern u32 sub_0805FAEC(void *, u32);
extern void sub_080338F0(void *, void *, void *);
extern void registerScriptObject(void *, u32);
extern void sub_080C31E0(void *, void *);   /* cleanup callback */
extern void sub_080C31E4(void *, void *, void *); /* run a script handler */
extern void sub_08033498(void);

/* Spawn and initialise a scripted sprite using the calling entity's parameters,
 * align its world position to the scene scroll, then either finish setup or
 * abort to the script's cleanup path depending on a game-state flag. */
void sub_08032ED0(void *arg0)
{
    u8 *savedAC = *(u8 **)((u8 *)arg0 + 0xAC);
    u8 *sprite = allocSpriteObject(savedAC);
    u8 *logic;
    u8 *animData;
    s16 cfgIndex;
    u8 *scriptData;
    u8 cmdIndex;

    if (sprite == NULL) goto fail;
    *(u8 **)((u8 *)arg0 + 0x38) = sprite;
    allocWorkSlot(arg0, 0, 0x64, 0);
    if (*(u8 *volatile *)((u8 *)arg0 + 0x3C) == NULL) goto fail;
    *(u32 *)((u8 *)sprite + 0x1C) = 0x8000000A;
    logic = *(u8 **)((u8 *)arg0 + 0x3C);
    animData = logic + 0x34;
    installUpdateHandler(arg0, logic, (void *)sub_08033498);
    initWorkStateForKind(arg0, sprite, logic, savedAC, 0x15);
    *(u16 *)((u8 *)logic + 0x04) = 0x08;
    cfgIndex = *(s16 *)((u8 *)logic + 0x1C);
    initSpriteGraphics(sprite, animData, (void *)((u32)cfgIndex * 12 + (u32)gSpriteAnimDataTable));
    setAnimationFrame(sprite, animData, 0, 1);
    sub_0803AEF0(arg0, logic, sprite);
    sub_0803AF70(arg0, logic, sprite, (u8 *)logic + 0x54);

    if (sub_0805FAEC(arg0, 0xE1) == 0) {
fail:
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
    } else {
        sub_080338F0(arg0, logic, sprite);

        {
            u8 *pt = gCameraState;
            u8 *pb = gMainWorkspace;
            u8 *base1;
            u8 *base2;
            u32 idx;

            pb += 0x18A8;

            idx = ((u32)*pb + 1) * 0x40;
            base1 = pt + 0x1278;
            *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)logic + 0x08) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);

            idx = ((u32)*pb + 1) * 0x40;
            base2 = pt + 0x127C;
            *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)logic + 0x0C) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
        }

        registerScriptObject(arg0, 0);
        *(u16 *)((u8 *)arg0 + 0x02) |= 0x1000;
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        {
            u32 litaddr = 0x08671BB0;
            scriptData = (u8 *)arg0 + 0x18;
            sub_080C31E4(scriptData, (u8 *)arg0 + 0x22, *(void **)litaddr);
        }
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) += 1;
        {
            s32 off = *(s16 *)((u8 *)arg0 + 0x22) * 2;
            cmdIndex = *(u8 *)(scriptData + off);
        }
        sub_080C31E0(arg0, *(void **)(*(u32 *)((u8 *)arg0 + 0x14) + cmdIndex * 4));
    }
}
