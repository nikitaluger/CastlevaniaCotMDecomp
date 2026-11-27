extern void *sScriptStepCallbacks;
extern void _call_via_r1(void *, void *);
extern void _call_via_r3(void *, void *, s32, void *);

extern s32 sub_080141AC(s32, void *);
extern void sub_08013C5C(void *, s32);
extern s32 sub_08013558(s32, void *, void *);
extern void sub_08013978(void *, void *);
extern void spawnChildPair(void *, void *, void *, void *, void *);
extern s32 sub_0804FFEC(s32, void *, void *, void *);
extern void sub_080142C0(void *, void *);
extern void sub_08013AC4(void *);
extern void sub_08005E80(s32);
extern s32 sub_08050260(void *, s32);
extern void stepAnimationTrack(s32, void *);
extern void sub_080502D0(s32, void *);
extern void sub_08013C8C(void *, s32);

/* One update tick of a weapon/projectile entity: test its sub-objects for a hit and apply
 * the damage/knockback response, handle the attack-end flag (clear sub-object state and
 * issue callback 3), dispatch the current state handler from the D_0866E5A8 table, then
 * clear the sub-objects' state and run the final cleanup. */
void sub_0804FA5C(u8 *self) {
    s32 parent = *(s32 *)(self + 0x38);
    u8 *obj = *(u8 **)(self + 0x3C);
    u8 *objSub = obj + 0x34;
    u8 *objState = obj + 0x48;
    u8 *slot;

    if (sub_080141AC(parent, obj) == 1) {
        u8 *hit0 = *(u8 **)(objState + 0x20);
        u8 zero = 0;
        *(u8 *)(hit0 + 1) = zero;
        *(u8 *)(*(u8 **)(objState + 0x24) + 1) = zero;
        slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (slot[0x1A] != 0) goto doHits;
        goto end;
    }

doHits:
    *(u8 *)(*(u8 **)(objState + 0x20) + 1) = 5;
    *(u8 *)(*(u8 **)(objState + 0x24) + 1) = 5;
    sub_08013C5C(self, parent);
    if (sub_08013558(parent, obj, *(void **)(obj + 0x28)) != 0) {
        sub_08013978(self, *(void **)(obj + 0x28));
        spawnChildPair(self, *(void **)(objState + 0x20), *(void **)(objState + 0x24), obj + 0x70, obj + 0x74);
    } else {
        if (sub_0804FFEC(parent, obj, *(void **)(objState + 0x20), *(void **)(objState + 0x24)) != 0) {
            sub_08013978(self, *(void **)(obj + 0x28));
            spawnChildPair(self, *(void **)(objState + 0x20), *(void **)(objState + 0x24), obj + 0x70, obj + 0x74);
        }
    }

    sub_080142C0(self, *(void **)(obj + 0x28));
    if (*(u16 *)obj & 1) {
        u8 *hit0 = *(u8 **)(objState + 0x20);
        u8 zero = 0;
        *(u8 *)(hit0 + 1) = zero;
        *(u8 *)(*(u8 **)(objState + 0x24) + 1) = zero;
        slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (slot[0x1A] != 3) {
            *(u16 *)objState = zero;
            sub_08013AC4(self);
            sub_08005E80(0x8A);
            slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(slot + 0x1B) = 0;
            { void **callbackSlot = &sScriptStepCallbacks;
              _call_via_r3(self + 0x18, self + 0x22, 3, *callbackSlot); }
        }
    }

    if (sub_08050260(self, parent) != 0) goto finish;

    *(u32 *)(self + 0x14) = 0x0866E5A8;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    {
        u8 *slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        slot[0x19] = (u8)(slot[0x19] + 1);
    }
    {
        s32 stateIdx = (*(s16 *)(self + 0x22)) * 2;
        u8 *slotArea = self + 0x18;
        u8 stateByte = *(slotArea + stateIdx);
        void **handlers = *(void **)(self + 0x14);
        void *handler = handlers[stateByte];
        _call_via_r1(self, handler);
    }
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    if ((*(u16 *)(self + 2) & 0x8000) != 0) goto end;
    stepAnimationTrack(parent, objSub);

finish:
    sub_080502D0(parent, obj);
    sub_08013C8C(self, parent);

end:
    ;
}
