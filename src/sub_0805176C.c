void sub_08013978(void*, void*);
void sub_08013C5C(void*, void*);
void sub_08013C8C(void*, void*);
s32 sub_080141AC(void*, void*);
void sub_080142C0(void*, void*);
s32 sub_08014328(void*, void*, void*);
void sub_080C31E8(void*, void*, s32, s32);

typedef void (*Fn)(void*);
struct S_02025FF0 { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0 D_02025FF0;
extern u32 D_08671BDC;

/* Advances one scripted behaviour step for an entity: handles death/contact,
 * flip requests and opcode dispatch, then copies the owner's position. */
void sub_0805176C(u8 *entity) {
    u8 *parent = *(u8**)(entity + 0x38);
    u8 *component = *(u8**)(entity + 0x3C);
    sub_08013C5C(entity, parent);
    if (sub_080141AC(parent, component) == 1 && *(u8*)(entity + 0x70) == 0) return;

    sub_08013978(entity, *(void**)(component + 0x28));
    sub_080142C0(*(void**)(entity + 0x28), *(void**)(component + 0x28));

    if (*(void**)(entity + 0x28) == (void*)D_02025FF0.v) {
        u8 *stepPtr = (u8*)((s32)((s16)*(s16*)(entity + 0x22) * 2) + (s32)entity);
        if (*(u8*)(stepPtr + 0x1A) != 1) {
            u32 *callTable;
            *(u8*)(stepPtr + 0x1B) = 0;
            callTable = &D_08671BDC;
            sub_080C31E8(entity + 0x18, entity + 0x22, 1, *callTable);
        }
    }

    if (sub_08014328(*(void**)(entity + 0x28), parent, component) == 0) {
        u8 *stepPtr;
        s32 pcOffset;
        u8 *opcodePtr;
        u8 opcode;
        Fn *handlerTable;
        *(u32*)(entity + 0x14) = 0x0866E624;
        *(u16*)(entity + 0x22) = *(u16*)(entity + 0x22) + 1;
        stepPtr = (u8*)((s32)((s16)*(s16*)(entity + 0x22) * 2) + (s32)entity);
        *(u8*)(stepPtr + 0x19) = *(u8*)(stepPtr + 0x19) + 1;
        pcOffset = (s16)*(s16*)(entity + 0x22) * 2;
        opcodePtr = entity + 0x18;
        opcode = *(u8*)(pcOffset + opcodePtr);
        handlerTable = (Fn*)(*(u32*)(entity + 0x14));
        handlerTable[opcode](entity);
        *(u16*)(entity + 0x22) = *(u16*)(entity + 0x22) - 1;
    }

    *(u32*)(component + 0x08) = *(u32*)(entity + 0x4C);
    *(u32*)(component + 0x0C) = *(u32*)(entity + 0x5C);

    if (*(void**)(entity + 0x28) != (void*)D_02025FF0.v) {
        *(u16*)parent = *(u16*)(u8*)*(vu32*)((u8*)(*(void**)(entity + 0x28)) + 0x38);
        *(u16*)(parent + 2) = *(u16*)((u8*)*(vu32*)((u8*)*(vu32*)(entity + 0x28) + 0x38) + 2);
    }

    if (*(u8*)(entity + 0x70) != 0) {
        *(u8*)(*(u8**)(component + 0x28) + 1) = 0;
    }
    sub_08013C8C(entity, parent);
}
