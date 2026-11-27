s32 sub_080141AC(void *, void *);
void sub_08013C5C(void *, void *);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_080142C0(void *, void *);
void sub_08013AC4(void *);
void sub_080269A8(void *, s32);
void sub_080C31E8(void *, void *, s32, u32);
s32 updateObjectDisplayState(void *, void *);
void sub_080C31E0(u8 *, s32);
void stepAnimationTrack(void *, void *);
void advanceMotion(void *, s32);
void sub_08013C8C(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866D980[];
extern u32 sScriptStepCallbacks[];

/* Updates a weapon/familiar entity: checks its animation state, handles
 * attack events, advances its state callback and applies camera-relative
 * positioning. */
void sub_08025FE0(u8 *self)
{
    u8 *gfxObj;
    u8 *anim;
    u8 *animData;
    u8 *extra;
    u8 *pt;
    u8 *pb;
    u32 idx;
    u32 coordValue;
    u32 b;
    u8 b2;
    u8 *stateSlot;
    s32 idx2;
    s32 zero;
    u32 dummy;
    s32 t;

    gfxObj = *((u8 **) (self + 0x38));
    anim = *((u8 **) (self + 0x3C));
    animData = anim + 0x34;
    extra = anim + 0x48;

    if (sub_080141AC(gfxObj, anim) == 1)
    {
        *((u16 *) extra) = 0;
    }
    else
    {
        *((u16 *) extra) = 1;
    }

    zero = 0;
    *((u32 *) (extra + 0x14)) = zero;

    dummy = 0;
    b = *((s16 *) (extra + dummy));
    if (b == 1)
    {
        sub_08013C5C(self, gfxObj);
        if (sub_08013558(gfxObj, anim, *((void **) (anim + 0x28))) != 0)
        {
            sub_08013978(self, *((void **) (anim + 0x28)));
        }
        sub_080142C0(self, *((void **) (anim + 0x28)));
        b = b & (*((u16 *) anim));
        if (b && ((*((u8 *) (((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self)) + 0x1A))) != 5))
        {
            u32 *animFn;
            sub_08013AC4(self);
            sub_080269A8(self, 0x40);
            *((u32 *) (extra + 0x04)) = 0xB60;
            *((u32 *) (anim + 0x14)) = 0;
            t = *((s32 *) (anim + 0x10));
            t = t + (s32)((u32)t >> 31);
            *((s32 *) (anim + 0x10)) = t >> 1;
            *((u8 *) (((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self)) + 0x1B)) = zero;
            animFn = sScriptStepCallbacks;
            sub_080C31E8(self + 0x18, self + 0x22, 5, *animFn);
        }
    }

    if (updateObjectDisplayState(gfxObj, anim) == 0)
    {
        u8 *p2;
        *((u32 *) (self + 0x14)) = (u32) D_0866D980;
        *((u16 *) (self + 0x22)) = (*((u16 *) (self + 0x22))) + 1;
        p2 = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
        *((u8 *) (p2 + 0x19)) = (*((u8 *) (p2 + 0x19))) + 1;
        idx2 = (*((s16 *) (self + 0x22))) * 2;
        stateSlot = self;
        stateSlot += 0x18;
        b2 = *((u8 *) (((u32) stateSlot) + ((u32) idx2)));
        sub_080C31E0(self, *((s32 *) ((*((u32 *) (self + 0x14))) + (b2 * 4))));
        *((u16 *) (self + 0x22)) = (*((u16 *) (self + 0x22))) - 1;
        if (((*((u16 *) (self + 2))) & 0x8000) == 0)
        {
            stepAnimationTrack(gfxObj, animData);
            advanceMotion(anim, *((s32 *) (extra + 0x04)));
        }
        else
        {
            return;
        }
    }

    sub_08013C8C(self, gfxObj);
    {
        s32 worldOffset = (*((s32 *) (anim + 0x0C))) + (*((s32 *) (extra + 0x14)));
        pt = gCameraState;
        pb = gMainWorkspace;
        pb += 0x18A8;
        idx = (((u32) (*pb)) + 1) * 0x40;
        pt += 0x127C;
        coordValue = *((u32 *) (pt + idx));
        *((u32 *) (gfxObj + 0x18)) = worldOffset - ((coordValue + 0xFFFF8000) & 0xFFFF0000);
    }
}
