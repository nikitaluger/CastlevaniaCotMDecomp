extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
extern void unlinkAndFreeObject(void *);
extern void clearObjectSlot(void *);
extern s32 gMenuScriptCallback[];
extern s32 gMainObjTimerCallbacks[];

/* Advance the actor's model animation by 8 frames; if its restart flag is
 * set, reload the 0x78 timer, clear the level's counter at +0x17 and run the
 * handler at gMenuScriptCallback[0] with argument 3. */
void sub_0801F838(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 model = *(s32 *)(self + 0x38);
    u8 *anim = *(u8 **)(self + 0x3C);
    u8 *animFlags = anim + 0x34;
    u8 *timers = anim + 0x48;
    s32 *handlerTable;

    setAnimationFrame(model, animFlags, 8, 0);
    if (*(u8 *)animFlags & 2) {
        s16 level;
        u8 zero = 0;
        *(u16 *)(timers + 6) = 0x78;
        level = *(s16 *)(self + 0x22);
        *(u8 *)(self + level * 2 + 0x17) = zero;
        handlerTable = gMenuScriptCallback;
        sub_080C31E8(self + 0x18, self + 0x22, 3, *handlerTable);
    }
}

void destroyObject(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *timers = work + 0x48;

    clearObjectSlot(arg0);
    if (*(u32 *)(work + 0x28) != 0) {
        unlinkAndFreeObject(*(void **)(work + 0x28));
    }
    if (*(u32 *)(timers + 4) != 0) {
        unlinkAndFreeObject(*(void **)(timers + 4));
    }
    sub_080C31E0(arg0, *(s32 *)(work + 0x24));
}

/* Unregister this actor from the 10-entry active-slot table at +0x70 of the
 * object referenced through self+0x8C, unless the actor is flagged as
 * persistent (bit 1 of +0x6C). */
void clearObjectSlot(void *arg0)
{
    if (!(2 & *(u16 *)((u8 *)arg0 + 0x6C)))
    {
        u32 *slots = *(u32 **)(*(u8 **)((u8 *)arg0 + 0x8C) + 0x3C);
        u32 zero = 0;
        u32 *slot = slots + 0x1C;
        s32 i = 9;
        do
        {
            if (*slot == (u32)arg0)
                *slot = zero;
            slot++;
        } while (--i >= 0);
    }
}

/* Advance the actor's model animation by 3 frames and tick the timer at
 * work+0x48; when it underflows, reset it and advance the command script. */
void sub_0802459C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    u8 *timer = work + 0x48;
    s32 *handlerTable;

    setAnimationFrame(*(s32 *)(self + 0x38), anim, 3, 0);
    *(u16 *)timer = *(u16 *)timer - 1;
    if ((s16)*(u16 *)timer < 0) {
        s16 level;
        *(u16 *)timer = 0;
        level = *(s16 *)(self + 0x22);
        *(u8 *)(self + level * 2 + 0x19) = 0;
        handlerTable = gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
    }
}
