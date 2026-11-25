/* Propagate an object's state to its two children, then walk the object's entry
 * table from the current index, spawning each entry's object at its offset until
 * a terminating entry is reached; record the next index and return the terminator. */
void sub_08000E98(s32, s32, s32, s32, s32);

s32 sub_080988DC(void *arg0)
{
    u8 *obj = (u8 *)arg0;
    s32 entryIndex = *(u8 *)(obj + 0x25);
    u8 *statePtr = obj + 0x35;
    u8 state = *statePtr;
    s32 stateFlag;
    s32 callbackOffset;
    u8 *entry;
    u8 stateTemp;
    u16 frameTemp;

    {
        s32 invertedState = ~(s8)state;
        stateFlag = (u32)((0 - invertedState) | invertedState) >> 31;
    }

    if (*(u8 **)(obj + 0x14) != 0)
        (*(u8 **)(obj + 0x14))[0x54] = state;
    {
        u8 *childB = *(u8 **)(obj + 0x18);
        if (childB != 0) {
            stateTemp = *statePtr;
            *(u8 *)(childB + 0x54) = stateTemp;
        }
    }

    entryIndex -= 1;
    callbackOffset = stateFlag << 2;
    {
        u8 *nextIndexPtr = obj + 0x26;
        do {
            u8 *callbackSlot;
            entryIndex += 1;
            entry = (u8 *)*(void **)(obj + 0x20) + entryIndex * 0x10;
            callbackSlot = entry + 4;
            sub_08000E98(1, *(s32 *)(callbackSlot + callbackOffset),
                         *(s32 *)(obj + 0x0C) + ((u32)entry[1] << 5),
                         (u32)*(u16 *)(entry + 2) << 5, 0x10);
            {
                u8 *childA = *(u8 **)(obj + 0x14);
                if (childA != 0) {
                    frameTemp = *(u16 *)(entry + 0x0C);
                    *(u16 *)(childA + 0x4C) = frameTemp;
                }
            }
            {
                u8 *childB = *(u8 **)(obj + 0x18);
                if (childB != 0) {
                    frameTemp = *(u16 *)(entry + 0x0E);
                    *(u16 *)(childB + 0x4C) = frameTemp;
                }
            }
        } while (*entry == 0);
        entryIndex += 1;
        *nextIndexPtr = entryIndex;
    }
    return *entry + 1;
}
