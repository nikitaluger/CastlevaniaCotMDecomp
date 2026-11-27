extern void sub_080BE578(void);
extern void clearAttachedObjectAnimFlags(void *);
extern void setAttachedObjectMode(s32, s32, void *);
extern void setObjectModeWord(s32, s32);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080C31E0(void *, void *);
extern void *gMainObjTimerCallbacks;

/* Actor script step: reset the actor and its linked work state, load the
 * resource at 0x08440AA8, clear the work's pointer flags, configure two
 * sub-objects, then advance the script. */
void sub_080BA17C(void *arg0)
{
    u8 *self;
    u8 *body;
    u8 *work;
    s32 zero;
    u8 *stepData;
    void **scriptTable;

    self = (u8 *)arg0;
    body = *(u8 **)(self + 0x3C);
    work = body + 0x48;
    zero = 0;
    *(s32 *)(self + 4) = zero;
    *(s32 *)(work + 0x6C) = zero;

    sub_080BE578();
    *(s32 *)(work + 0x40) = 0x10000;
    clearAttachedObjectAnimFlags(work);
    setAttachedObjectMode(*(s32 *)(work + 0x20), 2, body);
    setObjectModeWord(*(s32 *)(work + 0x1C), 1);

    *(s8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = (s8)zero;
    scriptTable = &gMainObjTimerCallbacks;
    stepData = self + 0x18;
    sub_080C31E4(stepData, self + 0x22, *scriptTable);

    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepData = stepData + *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + (*stepData * 4)));
}
