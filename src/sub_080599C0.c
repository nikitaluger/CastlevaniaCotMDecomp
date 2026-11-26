extern s32 sub_08005820(s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

static inline u16 zeroU16(void) { u16 v = 0; return v; }
static inline u32 zeroU32(void) { u32 v = 0; return v; }

/* Script step: start animation frame 0x14 and clear the pose's motion word;
 * when the animation finishes, choose a left/right direction from the entity's
 * X versus the target, arm a randomized delay, clear the step byte and
 * advance the script. */
void sub_080599C0(void *arg0)
{
    u8 *self = arg0;
    u32 sprite = *(u32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    u8 *pose = work + 0x48;
    s32 direction;
    s32 randomPart;
    s32 delay;
    u16 zero;

    setAnimationFrame(sprite, anim, 0x14, 0);
    *(u32 *)(pose + 8) = zeroU32();
    if ((*anim) & 2) {
        direction = (*(s32 *)(work + 8) > *(s32 *)(work + 0x48)) ? (s32)0xFFFFE000 : 0x2000;
        *(s32 *)(work + 0x10) = direction;
        randomPart = sub_08005820(0x65);
        delay = randomPart + 0x78;
        zero = zeroU16();
        *(u16 *)(pose + 4) = (u16)delay;
        ((u8 *)(self + ((*(s16 *)(self + 0x22)) * 2)))[0x17] = (u8)zero;
        {
            void **handlerTable = (void **)0x08671BB4;
            sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
        }
    }
}
