/* The D_0000xxxx symbols are used only for their addresses: byte offsets into
 * gMainWorkspace materialised as link-time literals. */
extern u8 gMainWorkspace[];
extern u8 D_000018C2[];
extern u8 D_0000173A[];
extern u8 D_000014ED[];
extern u32 gMainObjTimerCallbacks;

extern void stepDelayTimer(void *, u16 *);
extern void sub_08005E80(s32);
extern void cullOffscreenEntity(void *, u16 *);
extern s32 checkGlobalStateChange(void *, u16 *, void *);
extern void sub_0806D588(u16 *, void *);
extern u16 scalePercentSaturate16(u16, s32);
extern s32 divInt32(s32, s32);

typedef void (*Fn2)(void *, void *);
typedef void (*Fn1)(void *);

/* Update a tracking effect: check for global state changes, apply the shared
 * state value, tick its timer and ease its X/Y toward a target; on timeout or
 * target mismatch cancel it through the callback, otherwise play a sound at
 * intervals and hand off to the follow-up routine. */
void updateTrackingEffect(void *arg0) {
    void *data;
    void *buf;
    u16 *obj;
    void *target;
    u8 *gameState;
    s32 timer, soundTimer;
    s16 step;
    s32 posX, posY;
    s32 targetX, targetY;
    s32 zero;
    u16 stateValue;

    data = *(void **)((u8 *)arg0 + 0x6C);
    buf = (u8 *)data + 4;
    obj = *(u16 **)((u8 *)arg0 + 0x38);
    timer = checkGlobalStateChange(arg0, obj, buf);
    if (timer != 0)
        return;
    gameState = gMainWorkspace;
    stateValue = *(u16 *)((u32)gameState + (u32)D_000018C2);
    zero = 0;
    *obj = stateValue;
    *(u16 *)((*(void **)((u8 *)buf + 0x2C)) + 0x0E) = scalePercentSaturate16(*(u16 *)((*(void **)((u8 *)buf + 0x2C)) + 0x0E), 0x63);
    stepDelayTimer((u8 *)data + 0x20, obj);
    target = *(void **)((u8 *)buf + 0x4C);
    if (*(u8 *)((u8 *)target + 1) != *(u8 *)(data + 0x54))
        goto fail;
    timer = *(s32 *)((u8 *)buf + 0x10) - 1;
    *(s32 *)((u8 *)buf + 0x10) = timer;
    if (timer == 0)
        goto fail;
    goto success;
fail:
    *(u8 *)((*(void **)((u8 *)buf + 0x2C)) + 1) = (u8)zero;
    step = *(s16 *)((u8 *)arg0 + 0x22);
    *((u8 *)arg0 + step * 2 + 0x19) = (u8)zero;
    (*(Fn2 *)0x08671BB0)((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22);
    return;
success:
    targetX = *(s32 *)((u8 *)target + 0x0C);
    posX = *(s32 *)((u8 *)data + 4);
    posX = posX + divInt32(targetX - posX, 0x14);
    *(s32 *)((u8 *)data + 4) = posX;
    targetY = *(s32 *)((u8 *)target + 0x10);
    posY = *(s32 *)((u8 *)buf + 4);
    posY = posY + divInt32(targetY - posY, 0x14);
    *(s32 *)((u8 *)buf + 4) = posY;
    soundTimer = *(s32 *)((u8 *)buf + 0x14) - 1;
    *(s32 *)((u8 *)buf + 0x14) = soundTimer;
    if (soundTimer == 0) {
        sub_08005E80(0x14C);
        *(s32 *)((u8 *)buf + 0x14) = 0xA;
    }
    sub_0806D588(obj, buf);
    if (*(u8 *)((u32)gameState + (u32)D_0000173A) == 0x1C || (*(u8 *)((u32)gameState + (u32)D_000014ED) == 0 && *(s32 *)((u8 *)gameState + 0x10) != 0)) {
        (*(Fn1 *)((u8 *)arg0 + 0x24))(arg0);
        return;
    }
    cullOffscreenEntity(arg0, obj);
}
