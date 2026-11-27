extern void setFacingDirection(void *a, s32 b);
extern void setAttachedObjectMode(s32 a, s32 b, void *c);
extern void setObjectModeWord(s32 a, s32 b);
extern void clearAttachedObjectAnimFlags(void *a);
extern void markType1D6Objects(void *a);
extern void markType1D7Objects(void);
extern void markType1DAObjects(void);
extern void disableEffectPart(s32 a);
extern void setEffectPartState(s32 a, s32 b);
extern void startScriptOnce(void *a, s32 b, s32 c);
extern void sub_0808D0A4(s32 a);
extern void sub_080C31E0(void *a, s32 b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern u16 gCrossfadeGfxState[];

/* Actor script step: tear down a scripted multi-part object — release its
 * attached sprites and effect parts, freeze the relevant object lists, start
 * a crossfade with a sound cue, then dispatch the script callback and advance. */
void teardownScriptedMultiPartObject(u8 *entity) {
    u16 __repair_narrow_0;
    u8 *work = *(u8 **)(entity + 0x3C);
    u8 *attach = work + 0x48;
    u8 *target = *(u8 **)(entity + 0x4C);
    s32 fadeValue;
    s32 zero = 0;

    setFacingDirection(target, *(s32 *)(work + 8));
    setAttachedObjectMode(*(s32 *)(attach + 0x20), 0, work);
    setObjectModeWord(*(s32 *)(attach + 0x1C), 0);
    clearAttachedObjectAnimFlags(attach);
    markType1D6Objects(entity);
    markType1D7Objects();
    markType1DAObjects();

    {
        u8 *partA = *(u8 **)(attach + 0x2C);
        if (partA != NULL) {
            sub_080C31E0(partA, *(s32 *)(partA + 0x24));
        }
    }
    {
        u8 *partB = *(u8 **)(attach + 0x30);
        if (partB != NULL) {
            sub_080C31E0(partB, *(s32 *)(partB + 0x24));
        }
    }

    {
        u8 *spriteA = *(u8 **)(*(u8 **)(attach + 0x14) + 0x38);
        *(u16 *)(spriteA + 2) = (*(u16 *)(spriteA + 2) | 0x400) | zero;
    }
    {
        u8 *spriteB = *(u8 **)(*(u8 **)(attach + 0x18) + 0x38);
        *(u16 *)(spriteB + 2) = (*(u16 *)(spriteB + 2) | 0x400) | zero;
    }

    disableEffectPart(*(s32 *)(attach + 0x34));
    setEffectPartState(*(s32 *)(attach + 0x34), 0);
    startScriptOnce(target, 1, 1);

    *(u32 *)(work + 0xD0) = 0x10;
    gCrossfadeGfxState[2] = 0x3F42;
    fadeValue = *(u32 *)(work + 0xD0);
    __repair_narrow_0 = (u16) (fadeValue | ((0x10 - fadeValue) << 8));
    gCrossfadeGfxState[3] = __repair_narrow_0;
    sub_0808D0A4(0x14);

    if (*(u8 *)(target + 0x34) != 0) {
        *(u8 *)(target + 0x34) = 0;
        *(u32 *)(attach + 0x40) = 0;
        *(u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity + 0x19) = zero;
        {
            u32 *callbackTable = (u32 *)0x08671BB0;
            u8 *scriptStream = entity + 0x18;
            sub_080C31E4(scriptStream, entity + 0x22, *callbackTable);
        }
        {
            u8 *stepAddr = (u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity);
            *(u8 *)(stepAddr + 0x19) = (u8)(*(u8 *)(stepAddr + 0x19) + 1);
        }
        {
            u8 *scriptStream = entity + 0x18;
            u8 *step = scriptStream + (s16)*(s16 *)(entity + 0x22) * 2;
            sub_080C31E0(entity, *(u32 *)((u32)(*step) * 4 + *(u32 *)(entity + 0x14)));
        }
    } else {
        *(u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity + 0x19) = zero;
        {
            u32 *callbackTable = (u32 *)0x08671BB0;
            u8 *scriptStream = entity + 0x18;
            sub_080C31E4(scriptStream, entity + 0x22, *callbackTable);
        }
        {
            u8 *stepAddr = (u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity);
            *(u8 *)(stepAddr + 0x19) = (u8)(*(u8 *)(stepAddr + 0x19) + 1);
        }
        {
            u8 *scriptStream = entity + 0x18;
            u8 *step = scriptStream + (s16)*(s16 *)(entity + 0x22) * 2;
            sub_080C31E0(entity, *(u32 *)((u32)(*step) * 4 + *(u32 *)(entity + 0x14)));
        }
    }
}
