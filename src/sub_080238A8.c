struct ObjFlags { u16 flags; };   /* generic low-word flag field of an object */

extern s32 sub_08016238(void *);                /* hit-test an object against the global list */
extern void sub_08023F34(s32, s32, s32);        /* spawn an effect at world coordinates */
extern void sub_08005E80(s32);                  /* play a sound effect */
extern void sub_08011368(void *, void *, s32, s32); /* set animation/frame control */
extern void sub_080113A8(void *, void *);       /* request a frame from frame control */
extern void sub_0801165C(void *, s32);          /* advance frame control velocity */
extern s32 sub_08013B5C(void *, void *);        /* advance an actor's own AI */
extern void sub_08023BDC(void *, void *);       /* extra per-frame processing for this actor */
extern s32 sub_080C31E0(void *, s32);           /* cleanup callback */
extern void sub_080C31E8(void *, void *, s32, s32); /* run a step-script handler */

extern u8 D_02021E90[];                         /* scroll-offset table */
extern u8 D_02025FF0[];                         /* global game state */
extern u8 D_0866D8C0[];                         /* step-script handler table */
extern s32 D_08671BDC[];                        /* step-script data table */

/* Updates a two-hitbox scripted enemy: checks both of its collision parts, spawns a
   death effect and plays a sound when either is hit, advances the step script and
   animation, then projects the actor into sprite screen space. */
void sub_080238A8(u8 *eff)
{
    u8 *sprite;
    u8 *actor;
    u8 *anim;
    u8 *extra;
    u8 *stepSlot;
    u8 *stepBase;
    u8 *scrollTbl;
    u8 *scrollIdxPtr;
    u8 *xBase;
    s32 *scriptData;
    s32 stepOffset;
    u32 scrollIdx;
    u32 scrollX;
    u32 scrollY;
    u32 handlerIndex;

    sprite = *(u8 **)(eff + 0x38);
    actor = *(u8 **)(eff + 0x3C);
    anim = actor + 0x34;
    extra = actor + 0x48;

    *(u8 *)(*(u8 **)(actor + 0x28) + 1) = 5;
    *(u8 *)(*(u8 **)(extra + 4) + 1) = 5;

    if (sub_08016238(*(u8 **)(actor + 0x28)) != 0 || sub_08016238(*(u8 **)(extra + 4)) != 0) {
        u8 *obj = *(u8 **)(actor + 0x28);
        s32 x = *(s32 *)(actor + 8) + ((s32)*(s16 *)(obj + 0x0A) << 16);
        s32 y = *(s32 *)(actor + 0x0C) + ((s32)*(s16 *)(obj + 0x0C) << 16);
        sub_08023F34(x, y, 2);
        sub_08005E80(0x189);
        ((struct ObjFlags *)actor)->flags |= 1;
    }

    if ((*(u16 *)(eff + 0x6C) & 2) || *(u16 *)(sprite + 0x28) == 0x4B) {
        ((struct ObjFlags *)actor)->flags |= 1;
    }

    if (*(u16 *)actor & 1) {
        u8 stepFlag = *(u8 *)(eff + (s32)*(s16 *)(eff + 0x22) * 2 + 0x1A);
        if (stepFlag != 3) {
            if (stepFlag == 1) {
                sub_080C31E0(eff, *(s32 *)(eff + 0x24));
                return;
            } else {
                s32 spriteState = *(u16 *)(sprite + 0x28);
                if (spriteState == 0x46) goto case46;
                if (spriteState > 0x46) goto gt46;
                if (spriteState == 0x45) goto case45;
                goto endsw;
            gt46:
                if (spriteState == 0x48) goto case48;
                goto endsw;
            case45:
                sub_08011368(sprite, anim, 0x2B, 0);
                goto endsw;
            case46:
                sub_08011368(sprite, anim, 0x27, 0);
                goto endsw;
            case48:
                sub_08011368(sprite, anim, 0x22, 0);
            endsw:
                *(u8 *)(eff + (s32)*(s16 *)(eff + 0x22) * 2 + 0x1B) = 0;
                scriptData = D_08671BDC;
                sub_080C31E8(eff + 0x18, eff + 0x22, 3, *scriptData);
            }
        }
    }

    if (sub_08013B5C(sprite, actor) == 0) {
        *(u32 *)(eff + 0x14) = (u32)D_0866D8C0;
        *(u16 *)(eff + 0x22) = *(u16 *)(eff + 0x22) + 1;
        stepSlot = (u8 *)((u32)(*(s16 *)(eff + 0x22)) * 2 + (u32)eff);
        *(u8 *)(stepSlot + 0x19) = *(u8 *)(stepSlot + 0x19) + 1;
        stepOffset = *(s16 *)(eff + 0x22) * 2;
        stepBase = eff;
        stepBase += 0x18;
        handlerIndex = *(u8 *)((u32)stepBase + (u32)stepOffset);
        sub_080C31E0(eff, *(s32 *)(*(u32 *)(eff + 0x14) + handlerIndex * 4));
        *(u16 *)(eff + 0x22) = *(u16 *)(eff + 0x22) - 1;
        if (*(u16 *)(eff + 2) & 0x8000) {
            return;
        }
        sub_080113A8(sprite, anim);
        sub_0801165C(actor, 0);
    }

    sub_08023BDC(eff, sprite);

    scrollTbl = D_02021E90;
    scrollIdxPtr = D_02025FF0;
    scrollIdxPtr += 0x18A8;
    scrollIdx = ((u32)*scrollIdxPtr + 1) * 0x40;
    xBase = scrollTbl + 0x1278;
    scrollX = *(u32 *)(xBase + scrollIdx);
    *(u32 *)(sprite + 0x14) = *(u32 *)(actor + 8) - ((scrollX + 0x8000) & 0xFFFF0000);
    scrollIdx = ((u32)*scrollIdxPtr + 1) * 0x40;
    scrollTbl += 0x127C;
    scrollY = *(u32 *)(scrollTbl + scrollIdx);
    *(u32 *)(sprite + 0x18) = *(u32 *)(actor + 0xC) - ((scrollY + 0xFFFF8000) & 0xFFFF0000);
}
