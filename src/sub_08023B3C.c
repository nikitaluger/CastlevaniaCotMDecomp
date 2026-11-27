void setAnimationFrame(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);
s32 sub_08023F34(s32, s32, s32);
void sub_080C31E4(void *, void *, void *);
extern void *gScriptStepCallbackTable;

void sub_0802349C(void *arg0) {
    u8 *obj = arg0;
    u8 new_var;
    s32 off;
    setAnimationFrame(*(void **)(obj + 0x38), (u8 *)*(void **)(obj + 0x3C) + 0x34, 0, 0);
    *(u32 *)(obj + 0x14) = 0x0866D8B0;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
    ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
    off = (*(s16 *)(obj + 0x22)) * 2;
    new_var = 0x18;
    sub_080C31E0(arg0, (void *)((u32 *)*(u32 **)(obj + 0x14))[((u8 *)(new_var + obj))[off]]);
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
}

void releaseProjectileSlotsStep5(void *arg0) {
    s32 var_r3;
    void **var_r2;
    void *temp_r1;

    var_r2 = (void **)(*(u32 *)((u8 *)arg0 + 0x3C) + 0x70);
    var_r3 = 9;
    do {
        temp_r1 = *var_r2;
        if (temp_r1 != NULL) {
            *(u16 *)((u8 *)temp_r1 + 0x6C) = (u16)(*(u16 *)((u8 *)temp_r1 + 0x6C) | 2);
            *var_r2 = NULL;
        }
        var_r2 += 1;
        var_r3 -= 1;
    } while (var_r3 >= 0);
}

void sub_08023A7C(void *arg0) {
    u8 *obj = arg0;
    void *r1 = *(void **)(obj + 0x3C);
    u8 *r5 = (u8 *)r1 + 0x48;
    *((u8 *)*(void **)((u8 *)r1 + 0x28) + 1) = 0;
    *((u8 *)*(void **)(r5 + 4) + 1) = 0;
    if (sub_08023F34(*(s32 *)((u8 *)r1 + 8), *(s32 *)((u8 *)r1 + 0xC), 1) == 0) {
        sub_080C31E0(arg0, *(void **)(obj + 0x24));
        return;
    }
    *(u16 *)(r5 + 2) = 9;
    *((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2) + 0x19) = 0;
    sub_080C31E4(obj + 0x18, obj + 0x22, gScriptStepCallbackTable);
}

// Clears a flag on the entity's two linked sprites; if the graphics state's
// flag byte at +0x34 still has bit 1 set, invoke the entity's fail callback.
void sub_08023B3C(void *entity) {
    u8 *obj = entity;
    void *state = *(void **)(obj + 0x3C);
    u8 *stateFlags = (u8 *)state + 0x34;
    u8 *spriteA;
    u8 *spriteB;
    spriteA = *(u8 **)((u8 *)state + 0x28);
    spriteA[1] &= 0xFB;
    spriteB = *(u8 **)((u8 *)state + 0x4C);
    spriteB[1] &= 0xFE;
    if (stateFlags[0] & 2) {
        sub_080C31E0(entity, *(void **)(obj + 0x24));
    }
}
