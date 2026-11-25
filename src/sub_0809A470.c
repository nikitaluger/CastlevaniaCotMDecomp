extern void sub_080C2E68(void *, s32, s32);
extern void sub_08011528(s32, void *);
extern void sub_0809C4E0(s32, s32);
extern s32 sub_080057F8(void);
extern void sub_0809C5FC(void *, u8);
extern void sub_080C31E4(void *, void *, s32);
struct FrameState { u8 flags; u8 indexOffset; u8 _2[6]; void *ptrTable; u8 _C[2]; s16 frameIndex; };
struct ChoiceState { u8 _0[8]; s32 entity; u8 _C[0x11]; u8 choiceFlags[3]; u8 choice; };
struct CodeEntry { u8 _0[2]; u16 code; };

/* Copies a 3x2 choice table to the stack, advances the frame animation and sets a
 * code-driven state on the entity, then (when flagged) picks a value using three
 * flag bytes and forwards it to the entity and to a callback. */
void sub_0809A470(u8 *obj) {
    u8 pairs[3][2];
    s32 animSetId = *(s32 *)(obj + 0x38);
    u8 *config = *(u8 **)(obj + 0x3C);
    u8 *frame = config + 0x34;
    u8 *choice = config + 0x48;
    void **ptrTable;
    s32 frameIndex;
    u8 *result;
    u16 tableCode;
    s32 *callbackEntry;

    sub_080C2E68(pairs, 0x081017C5, 6);
    sub_08011528(animSetId, frame);
    ptrTable = (void **)((struct FrameState *)frame)->ptrTable;
    frameIndex = ((struct FrameState *)frame)->frameIndex + ((struct FrameState *)frame)->indexOffset;
    tableCode = ((struct CodeEntry *)((u8 *)*ptrTable + frameIndex * 4 - 4))->code;
    if (tableCode == 0x54) {
        sub_0809C4E0(((struct ChoiceState *)choice)->entity, 3);
    } else if (tableCode == 0x4B) {
        sub_0809C4E0(((struct ChoiceState *)choice)->entity, 2);
    } else {
        sub_0809C4E0(((struct ChoiceState *)choice)->entity, 0);
    }

    if (((struct FrameState *)frame)->flags & 2) {
        if (((struct ChoiceState *)choice)->choiceFlags[0] & ((struct ChoiceState *)choice)->choiceFlags[1] & ((struct ChoiceState *)choice)->choiceFlags[2]) {
            ((struct ChoiceState *)choice)->choice = pairs[((struct ChoiceState *)choice)->choice][sub_080057F8() & 1];
            result = (u8 *)choice + 0x20;
        } else {
            u8 selected = pairs[((struct ChoiceState *)choice)->choice][0];
            u8 *flagBytes = ((struct ChoiceState *)choice)->choiceFlags;
            u8 firstFlag;
            firstFlag = flagBytes[selected];
            result = (u8 *)choice + 0x20;
            if (firstFlag == 0 && flagBytes[pairs[((struct ChoiceState *)choice)->choice][1]] == 0) {
                *result = pairs[((struct ChoiceState *)choice)->choice][sub_080057F8() & 1];
            } else if (firstFlag != 0) {
                *result = pairs[((struct ChoiceState *)choice)->choice][1];
            } else {
                *result = selected;
            }
        }
        sub_0809C5FC(obj, *result);
        {
            u8 *linked = (u8 *)((u32)(*(s16 *)(obj + 0x22)) * 2 + (u32)obj);
            *(u8 *)(linked + 0x19) = 0;
        }
        callbackEntry = (s32 *)0x08671BB0;
        sub_080C31E4(obj + 0x18, obj + 0x22, *callbackEntry);
    }
}
