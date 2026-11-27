extern void *gTrigFuncPtr;
extern void *gScriptStepCallbacks;

s32 setAnimationFrame(void *, void *, s32, s32);
s32 sub_08014990(void *);
s32 sub_0803F758(void *, s32, s32, s16);
s32 divInt32(s32, s32);
s32 sub_080C31E0(s32, void *);
void sub_080C31E8(void *, void *, s32, void *);

static inline u8 bz(void) { u8 v = 0; return v; }

/* Steps an object's pose and horizontal movement: advances an animation index,
 * periodically retargets its velocity toward the player and fires a despawn
 * callback, otherwise pushes it left or right according to its facing flag. */
void sub_0803EEEC(void *object)
{
    void *sprite;
    u8 *state;
    u8 *ctrl;
    void **angleFunc;
    s32 zero;
    u8 *flagByte;

    sprite = *(void **)((u8 *)object + 0x38);
    state = *(u8 **)((u8 *)object + 0x3C);
    {
        u8 *pose = state + 0x34;
        ctrl = state + 0x48;
        setAnimationFrame(sprite, pose, 7, 0);
    }

    if (*(s16 *)(ctrl + 0x0C) > 0x3C) {
        *(s16 *)(ctrl + 0x0C) = 0;
    }

    angleFunc = &gTrigFuncPtr;
    *(s32 *)(ctrl + 0x08) = sub_080C31E0(divInt32(*(s16 *)(ctrl + 0x0C) << 16, 0x3C), *angleFunc) << 1;

    {
        s16 nextIndex = *(s16 *)(ctrl + 0x0C) + 1;
        zero = 0;
        *(s16 *)(ctrl + 0x0C) = nextIndex;
    }

    *(s16 *)(ctrl + 0x0E) = *(s16 *)(ctrl + 0x0E) - 1;
    if (*(s16 *)(ctrl + 0x0E) < 0) {
        s32 xPos, yPos;
        s16 idx;
        *(s32 *)(state + 0x14) = zero;
        *(s32 *)(state + 0x10) = zero;
        xPos = *(s32 *)(state + 0x08);
        yPos = *(s32 *)(state + 0x0C);
        *(s32 *)(ctrl + 0x14) = sub_0803F758(object, xPos, yPos, (s16)sub_08014990(sprite));
        *(u16 *)(ctrl + 0x0E) = 0x14;
        *(s32 *)(ctrl + 0x08) = zero;
        idx = *(s16 *)((u8 *)object + 0x22);
        flagByte = (u8 *)((idx * 2) + (u32)object) + 0x19;
        *flagByte = bz();
        {
            void **callback = &gScriptStepCallbacks;
            sub_080C31E8((u8 *)object + 0x18, (u8 *)object + 0x22, 1, *callback);
        }
    } else {
        if (sub_08014990(sprite) > 0) {
            *(s32 *)(state + 0x10) = 0x4000;
        } else {
            *(s32 *)(state + 0x10) = 0xFFFFC000;
        }
    }
}
