extern void *D_08671BDC;

s32 sub_08013558(void *, void *, s32);
void sub_08013978(void *, s32);
s32 sub_08013B5C(void *, void *);
void sub_08013C5C(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080141AC(void *, void *);
void sub_080142C0(s32, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E8(void *, void *, s32, void *);

/* Steps an enemy object's AI: refreshes its sprite/state, handles collision
 * and contact effects, fires a script callback when flagged, and dispatches a
 * slot-indexed callback when its action finishes. */
void sub_080567E0(u8 *object)
{
    void *sprite;
    u8 *state;

    sprite = *(void **)(object + 0x38);
    state = *(u8 **)(object + 0x3C);

    sub_08013C5C(object, sprite);
    sub_080141AC(sprite, state);

    if (sub_08013558(sprite, state, *(s32 *)(state + 0x28)) != 0)
        sub_08013978(object, *(s32 *)(state + 0x28));

    sub_080142C0(*(s32 *)(object + 0x28), *(s32 *)(state + 0x28));

    if ((*(u16 *)state & 1) || (*(u8 *)(object + 0x74) != 0))
    {
        u8 *slot = (u8 *)((u32)(*(s16 *)(object + 0x22)) * 2 + (u32)object);
        if (*(u8 *)(slot + 0x1A) != 3)
        {
            *(u8 *)(slot + 0x1B) = 0;
            {
                void **callback = &D_08671BDC;
                sub_080C31E8(object + 0x18, object + 0x22, 3, *callback);
            }
        }
    }

    if (sub_08013B5C(sprite, state) == 0)
    {
        *(u32 *)(object + 0x14) = (u32)0x0866E7B8;
        *(u16 *)(object + 0x22) = (u16)(*(u16 *)(object + 0x22) + 1);

        {
            u8 *slot = (u8 *)((u32)(*(s16 *)(object + 0x22)) * 2 + (u32)object);
            slot[0x19] = (u8)(slot[0x19] + 1);
        }

        {
            s32 slotIndex = (*(s16 *)(object + 0x22)) * 2;
            u8 *slotBase = object + 0x18;
            u8 slotByte = *(slotBase + slotIndex);
            void **dispatchTable = *(void **)(object + 0x14);
            void *dispatchFn = dispatchTable[slotByte];
            sub_080C31E0(object, dispatchFn);
        }

        *(u16 *)(object + 0x22) = (u16)(*(u16 *)(object + 0x22) - 1);
    }

    sub_08013C8C(object, sprite);
}
