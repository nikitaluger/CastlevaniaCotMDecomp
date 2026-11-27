extern s32 gTrigFuncTable;
extern s32 D_08671BC0;

s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, s32);

struct ScriptEntity {
    u8 _00[0x14];
    u32 callbacks;
    u8 _18[0x0A];
    s16 stepIndex;
    u8 _24[0x14];
    u8 *sprite;
    u8 *actor;
    u8 _40[0x0C];
    s32 flag;
    u8 _50[0x0C];
    s32 posX;
    u8 _60[0x0C];
    s32 posY;
    u8 _70[0x0C];
    s32 angle;
};

/* Spread an angle's sine/cosine across the actor's tracked sprite slots, copy
 * the actor position and flipped angle, then optionally run one script step. */
void sub_080BCEBC(struct ScriptEntity *a)
{
    u8 *sprite;
    u8 *actor;
    u32 *tracker;
    u32 *angleFunc;
    s32 cosVal;
    s32 sinVal;
    s32 sinScaled;
    s32 cosScaled;
    s32 sinStep;
    s32 cosStep;
    u32 i;
    u32 *entry, *clearEntry;

    sprite = a->sprite;
    actor = a->actor;
    tracker = (u32 *)(actor + 0x48);
    angleFunc = &gTrigFuncTable;
    cosVal = sub_080C31E0(a->angle + 0x4000, *angleFunc);
    sinVal = sub_080C31E0(a->angle, *angleFunc);

    i = 0;
    entry = tracker;
    sinScaled = sinVal << 2;
    cosScaled = cosVal << 2;
    sinStep = sinVal << 3;
    cosStep = cosVal << 3;
    for (; i <= 0x31; i++)
    {
        u8 *target = (u8 *)(*(volatile u32 *)entry);
        *(s16 *)(target + 0x0A) = (s16)(cosScaled >> 16);
        target = (u8 *)*entry++;
        *(s16 *)(target + 0x0C) = (s16)(sinScaled >> 16);
        sinScaled += sinStep;
        cosScaled += cosStep;
    }

    *(s32 *)(actor + 8) = a->posX;
    *(s32 *)(actor + 0xC) = a->posY;
    *(u16 *)(sprite + 8) = (u16)(0x4000 - a->angle);

    if (a->flag == 0)
    {
        s32 *scriptFunc;
        u8 *stepArgs;
        u8 *stepIndexPtr;
        u32 zero;

        i = 0;
        scriptFunc = &D_08671BC0;
        stepArgs = (u8 *)a + 0x18;
        stepIndexPtr = (u8 *)a + 0x22;
        zero = 0;
        clearEntry = tracker;
        for (; i <= 0x31; i++)
        {
            ((u8 *)*clearEntry++)[1] = zero;
        }

        *(u8 *)((u8 *)a + (s32)a->stepIndex * 2 + 0x19) = 0;
        sub_080C31E4(stepArgs, stepIndexPtr, *scriptFunc);
        {
            s16 stepIndex = *(s16 *)((u8 *)a + 0x22);
            u8 *stepCounter = (u8 *)((s32)stepIndex * 2 + (u32)a);
            stepCounter[0x19]++;
        }
        {
            s16 stepIndex = *(s16 *)((u8 *)a + 0x22);
            u8 *q = stepArgs + (s32)stepIndex * 2;
            sub_080C31E0((s32)a, *(s32 *)(a->callbacks + (u32)(*q) * 4));
        }
    }
}
