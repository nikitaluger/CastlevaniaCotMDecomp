/* Per-frame camera/scroll update for an entity: bail out when a special camera
 * mode owns the position, otherwise reset and re-track the scroll position,
 * ease one scroll coordinate toward its target, fire a timed effect when the
 * object's countdown expires, then run the final camera update. */
extern s32 sub_0806C4B4(void *a, void *b);
extern void sub_0806C5EC(void *a, s32 b, void *c, void *d);
extern void sub_0806AA64(s32 a, void *b);
extern s32 sub_08003740(void *a, s32 b);
extern void sub_08003A6C(void *a, s32 b, s32 c);
extern void sub_0806C6B0(void *a, s32 b, void *c, void *d);
extern void sub_080C31E4(void *a, void *b, s32 c);

extern u8 D_080DEA88[];
extern u8 gMainObjTimerCallback[];

void sub_08066674(void *entity)
{
    void *cam;
    void *pos;
    s32 view;
    s32 delta;
    s32 cur;
    void *timer;
    s32 timerResult;
    u8 *effectTable;

    cam = *(void **)((u8 *)entity + 0x6C);
    pos = (u8 *)cam + 4;
    view = *(s32 *)((u8 *)entity + 0x38);

    if (sub_0806C4B4(pos, pos) != 0)
        return;

    sub_0806C5EC(entity, view, pos, pos);

    delta = *(s32 *)((u8 *)cam + 0x110);
    cur = *(s32 *)((u8 *)pos + 4);
    delta = delta - cur;
    if (delta < 0)
        delta += 0xF;
    *(s32 *)((u8 *)pos + 4) = cur + (delta >> 4);

    sub_0806AA64(view, pos);

    timer = (u8 *)cam + 0x2C;
    timerResult = sub_08003740(timer, view);
    if (timerResult == 0) {
        u8 *effectData;
        effectTable = D_080DEA88;
        effectTable += 0x704;
        sub_08003A6C(timer, 0, *(s32 *)effectTable);
        *(s8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22) * 2) + 0x19) = (s8)timerResult;
        effectData = gMainObjTimerCallback;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *(s32 *)effectData);
    }

    sub_0806C6B0(entity, view, pos, pos);
}
