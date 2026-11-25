typedef void (*Fn)(void *);

void sub_080C31E0(void *a, Fn b);
s32 sub_08014900(s32);

/* Actor update: clear the pose field when the horizontal distance test fails,
 * install the script table at 0x0866E01C and run one script step, then (when
 * work flag bit 0 is set) stop movement and clamp the velocity. */
void sub_0803DA88(void *arg0)
{
    u8 *entity = (u8 *)arg0;
    u8 *work = *(u8 **)(entity + 0x3C);
    u8 *pose = work + 0x48;
    s32 distance;
    s32 zero;

    distance = sub_08014900(*(s32 *)(work + 0x08));
    if ((u32)(distance + 0xFFD00000) > 0x00100000U) {
        *(u16 *)(pose + 0x02) = 0;
    }

    *(u32 *)(entity + 0x14) = 0x0866E01C;

    {
        u16 nextStep = *(u16 *)(entity + 0x22) + 1;
        zero = 0;
        *(u16 *)(entity + 0x22) = nextStep;
    }

    *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x19) += 1;
    {
        s16 stepIndex = *(s16 *)(entity + 0x22);
        struct S_18 { u8 pad[0x18]; u8 scriptBytes[0x200]; };
        u8 scriptByte = ((struct S_18 *)entity)->scriptBytes[stepIndex * 2];
        u32 *scriptTable = *(u32 **)(entity + 0x14);
        sub_080C31E0(entity, (Fn)scriptTable[scriptByte]);
    }
    *(s16 *)(entity + 0x22) = *(s16 *)(entity + 0x22) - 1;

    if (*(u16 *)(work + 0x02) & 1) {
        *(u32 *)(work + 0x10) = zero;
        *(u16 *)(pose + 0x02) = 0;
        if (*(s32 *)(work + 0x14) < 0) {
            *(s32 *)(work + 0x14) = 0;
        }
    }
}
