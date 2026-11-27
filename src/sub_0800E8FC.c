extern u8 gMenuState[];
void _call_via_r1(void *, void *);

/* Runs the per-frame update handler of each of the five sub-objects in the
 * render state block's slot table at gMenuState + 0x48. */
void sub_0800E8FC(void) {
    u32 slot = 0;
    u8 *stateBlock = gMenuState;
    void **objSlot = (void **)(stateBlock + 0x48);
    void *obj;
    do {
        obj = *objSlot;
        if (obj != 0)
            _call_via_r1(obj, *(void **)((u8 *)obj + 0x24));
        objSlot++;
        slot++;
    } while (slot <= 4);
}
