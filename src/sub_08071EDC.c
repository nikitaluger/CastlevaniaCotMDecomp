extern void sub_080C31E4(void *a, void *b, s32 c);
extern void sub_08071FA0(void);
extern void sub_08072018(void *a);

struct S_02025368 {
    u8 pad0[0x2FC];
    s16 s2FC;
    u8 pad1[2];
    u32 u300;
};
extern struct S_02025368 gGameStatus;

extern s32 gMainObjTimerCallback[];
extern u32 gLevelExpTable[];

/* Script step: once the global sequence timer reaches the frame threshold for
 * the current stage, set the intro flags, advance the stage and step on. */
void sub_08071EDC(void *entity)
{
    u8 *state = (u8 *)&gGameStatus;
    u32 *frameCount = (u32 *)(state + 0x300);
    u32 *thresholds = gLevelExpTable;
    s32 stage = *(s16 *)(state + 0x2FC) - 1;

    if (*frameCount >= thresholds[stage])
    {
        sub_08071FA0();
        sub_08072018(entity);
        *(u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *nv = gMainObjTimerCallback;
            sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *nv);
        }
    }
}

/* Script step: tick a halfword timer down by 0x80 each frame; when it lands on
 * 0x80, advance the script. */
void sub_080721A0(void *entity)
{
    u8 *self = (u8 *)entity;
    s16 *timers = *(s16 **)(self + 0x38);
    s16 value = timers[2] - 0x80;
    timers[2] = value;
    if ((s16)value == 0x80)
    {
        *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *nv = gMainObjTimerCallback;
            sub_080C31E4(self + 0x18, self + 0x22, *nv);
        }
    }
}

/* Script step: tick another halfword timer down; on 0x80 start the work
 * countdown at +0x2C (0x60) and advance the script. */
void sub_080721D8(void *entity)
{
    u8 *self = (u8 *)entity;
    u8 *work = *(u8 **)(self + 0x6C) + 4;
    s16 *timers = *(s16 **)(self + 0x38);
    s16 value = timers[3] - 0x80;
    timers[3] = value;
    if ((s16)value == 0x80)
    {
        *(u32 *)(work + 0x2C) = 0x60;
        *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *nv = gMainObjTimerCallback;
            sub_080C31E4(self + 0x18, self + 0x22, *nv);
        }
    }
}

/* Script step: count the work countdown at +0x2C down to zero, then advance
 * the script. */
void sub_08072218(void *entity)
{
    u8 *self = (u8 *)entity;
    u8 *work = *(u8 **)(self + 0x6C) + 4;
    s32 countdown = *(s32 *)(work + 0x2C) - 1;
    *(s32 *)(work + 0x2C) = countdown;
    if (countdown == 0)
    {
        *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *nv = gMainObjTimerCallback;
            sub_080C31E4(self + 0x18, self + 0x22, *nv);
        }
    }
}
