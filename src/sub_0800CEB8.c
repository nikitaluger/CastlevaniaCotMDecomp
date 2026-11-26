extern void postDisplaySprite(s32, s32, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern u8 D_080CAFA8[];
extern u32 D_0866CEF4[];
extern void *gMainObjTimerCallback;
struct RoomState { u8 _0[0x64]; u8 state, prevState, mirror; };
extern struct RoomState D_020278D0;

/* Compare the room's current and previous state bytes; play one of two sounds
 * on a change, then refresh the cached bytes, dispatch the state's callback and
 * advance one script step. */
void sub_0800CEB8(u8 *entity) {
    u8 *stateTable = D_080CAFA8;
    u8 curIndex = D_020278D0.state;
    u8 *curEntry = &stateTable[curIndex * 4];
    u8 prevIndex = D_020278D0.prevState;
    u8 *prevEntry = &stateTable[prevIndex * 4];
    u8 curValue = *curEntry;
    u8 prevValue = *prevEntry;

    if (curValue != prevValue) {
        if (curValue == 0) {
            postDisplaySprite(1, (s32)0x08641588, (s32)0x050000A0, 0x60, 0x10);
        } else {
            postDisplaySprite(1, (s32)0x086415E8, (s32)0x050000A0, 0x60, 0x10);
        }
    }
    {
        u8 stateNow = D_020278D0.state;
        D_020278D0.mirror = stateNow;
        D_020278D0.prevState = stateNow;
        sub_080C31E0(entity, (void *)D_0866CEF4[D_020278D0.state]);
        {
            u8 zero = 0;
            s32 off = *(s16 *)(entity + 0x22);
            off <<= 1;
            off += (u32)entity;
            *(u8 *)(off + 0x19) = zero;
            {
                void **scriptCallbacks = &gMainObjTimerCallback;
                u8 *base = entity + 0x18;
                sub_080C31E4(base, entity + 0x22, *scriptCallbacks);
            }
            {
                s32 off2 = *(s16 *)(entity + 0x22);
                off2 <<= 1;
                off2 += (u32)entity;
                *(u8 *)(off2 + 0x19) = *(u8 *)(off2 + 0x19) + 1;
            }
            {
                s32 idx = (*(s16 *)(entity + 0x22)) * 2;
                u8 *base = entity + 0x18;
                u8 stepId = *(base + idx);
                void **callbacks = *(void **)(entity + 0x14);
                sub_080C31E0(entity, callbacks[stepId]);
            }
        }
    }
}
