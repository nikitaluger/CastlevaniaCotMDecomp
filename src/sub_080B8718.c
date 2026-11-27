extern void sub_08005E80(s32 resourceId);
extern void setObjectAnimationFrame(void *sprite, void *animState, s32 animIndex, s32 zero);
extern void sub_080C31E0(void *actor, s32 handler);
extern void sub_080C31E4(void *scriptData, void *scriptIndex, s32 callback);

struct P2A { u8 pad[0x2A]; u8 f2A; };
static inline u8 zero8(void) { return 0; }

/* If the actor's trigger byte is set, highlight its sprite, set up its animation
 * and motion from the script, fire the current script command and advance to the
 * next one; otherwise clear the highlight and the linked object's trigger. */
void sub_080B8718(u8 *arg0) {
    u8 *sprite;
    u8 *motion;
    u8 *animState;
    u8 *scriptData;
    u8 trigger;

    sprite = *(u8 **)(arg0 + 0x38);
    motion = *(u8 **)(arg0 + 0x3C);
    animState = motion + 0x34;
    trigger = *(u8 *)(arg0 + 0x4C);
    if (trigger != 0) {
        struct P2A *spriteFlags = (struct P2A *)sprite;
        u8 zero;
        spriteFlags->f2A |= 0x40;
        zero = zero8();
        setObjectAnimationFrame(sprite, animState, 0x22, 0);
        *(s32 *)(motion + 8) = *(s32 *)(arg0 + 0x5C);
        *(s32 *)(motion + 0xC) = 0x870000;
        sub_08005E80(0x185);
        *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = zero;
        {
            s32 *callbacks = (s32 *)0x08671BB0;
            scriptData = arg0 + 0x18;
            sub_080C31E4(scriptData, arg0 + 0x22, *callbacks);
        }
        {
            u8 *scriptEntry = (u8 *)((u32)(*(s16 *)(arg0 + 0x22) * 2) + (u32)arg0);
            *(u8 *)(scriptEntry + 0x19) = *(u8 *)(scriptEntry + 0x19) + 1;
        }
        scriptData += *(s16 *)(arg0 + 0x22) * 2;
        sub_080C31E0(arg0, *(s32 *)(*(u32 *)(arg0 + 0x14) + *(u8 *)scriptData * 4));
    } else {
        *(u8 *)(sprite + 0x2A) = *(u8 *)(sprite + 0x2A) & 0xBF;
        *(u8 *)(*(u8 **)(arg0 + 0x28) + 0x4C) = trigger;
    }
}
