extern void advanceAnimTrack(void *, void *);
extern void copyPoseAttrs(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);

/*
 * Updates an entity's pose: derives a pose index from its animation state,
 * applies the matching 24-byte pose-table entries to three linked objects,
 * and dispatches a script step when the status flag calls for it.
 */
void updateEntityPose(u8 *arg0)
{
    u8 *self;
    s32 poseIndex;
    void *sprite;
    u8 *motion;
    u8 *status;
    u8 *motionEx;
    u32 idx;

    self = arg0;
    poseIndex = 0;
    sprite = *(void **)(self + 0x38);
    motion = *(u8 **)(self + 0x3C);
    status = motion + 0x34;
    motionEx = motion + 0x48;

    advanceAnimTrack(sprite, status);

    {
        u32 *animTable = *(u32 **)(status + 8);
        s32 animOffset = *(s16 *)(status + 0x0E) + *(u8 *)(status + 1);
        u32 animBase = (u32)*animTable;
        u8 *animEntry = (u8 *)((u32)animOffset * 4 + animBase - 4);
        u16 animValue = *(u16 *)(animEntry + 2);
        idx = animValue - 0x26;
    }

    if (idx <= 0xD) {
        switch (idx) {
        case 0:
            poseIndex = 1;
            break;
        case 1:
        case 3:
        case 4:
        case 6:
        case 7:
        case 9:
        case 10:
        case 12:
            break;
        case 2:
            poseIndex = 2;
            break;
        case 5:
            poseIndex = 3;
            break;
        case 8:
            poseIndex = 4;
            break;
        case 11:
            poseIndex = 5;
            break;
        case 13:
            poseIndex = 6;
            break;
        }
    }

    {
        void *target = *(void **)(motion + 0x28);
        s32 off = poseIndex * 24;
        u8 *poseTable = (u8 *)0x08102F40;
        u8 *poseEntry;

        copyPoseAttrs(target, poseTable + off);

        {
            void *linked = *(void **)(motionEx + 0);
            poseEntry = poseTable + 8;
            copyPoseAttrs(linked, poseEntry + off);
        }

        {
            void *linked = *(void **)(motionEx + 4);
            poseTable += 0x10;
            copyPoseAttrs(linked, poseTable + off);
        }
    }

    if (*(u8 *)status & 2) {
        s16 stepIndex;
        u8 *stepData;
        s32 *scriptFn;

        *(u32 *)(self + 0x4C) = 0;
        *(u8 *)(*(u8 **)(motion + 0x28) + 1) = 0;
        *(u8 *)(*(u8 **)(motionEx + 0) + 1) = 0;
        *(u8 *)(*(u8 **)(motionEx + 4) + 1) = 0;

        stepIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + stepIndex * 2 + 0x19) = 0;

        scriptFn = (s32 *)0x08671BC0;
        stepData = self + 0x18;
        sub_080C31E4(stepData, self + 0x22, *scriptFn);

        stepIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + stepIndex * 2 + 0x19) += 1;

        stepIndex = *(s16 *)(self + 0x22);
        stepData += stepIndex * 2;
        sub_080C31E0(self, *(s32 *)(*(u32 *)(self + 0x14) + (u32)(*stepData) * 4));
    }
}
