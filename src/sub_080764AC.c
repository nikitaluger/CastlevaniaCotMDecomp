struct S_02025FF0 { u8 _[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
s32 allocWorkSlot(void *, s32, s32, s32);
void *allocSpriteObject(void);
void sub_0806D2D0(void *);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);

/* Allocate a child motion object, inherit the parent's facing bit and a global
 * word, clear/bump this entity's script slot and fire the script callback, then
 * invoke the table-driven callback. */
void sub_080764AC(void *arg0) {
    void *child;
    u8 zero;
    u16 flags;
    if (allocWorkSlot(arg0, 0, 0x68, 3) == 0) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    child = allocSpriteObject();
    if (child == NULL) {
        sub_0806D2D0(arg0);
        return;
    }
    *(void **)((u8 *)arg0 + 0x38) = child;
    flags = (u16)((*(u16 *)((u8 *)*(void **)((u8 *)*(void **)((u8 *)arg0 + 0x28) + 0x38) + 2) & 0x10) | *(u16 *)((u8 *)child + 2));
    zero = 0;
    *(u16 *)((u8 *)child + 2) = flags;
    *(u16 *)child = gMainWorkspace.w;
    *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = zero;
    {
        s32 *nv = (s32 *)0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *nv);
    }
    {
        u8 *slot = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        slot[0x19] = (u8)(slot[0x19] + 1);
    }
    {
        s32 slotOff = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        u8 *slots = (u8 *)arg0 + 0x18;
        u8 slotId = *(slots + slotOff);
        u8 **table = *(u8 **)((u8 *)arg0 + 0x14);
        sub_080C31E0(arg0, (s32)table[slotId]);
    }
}
