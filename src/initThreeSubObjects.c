extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, s32);
struct Sub { u8 _0; u8 active; u8 type; u8 subtype; u16 dataWord; u16 param6; u16 param8; u16 paramA; u16 paramC; u16 paramE; s32 payload; };
struct SubObjects { struct Sub *volatile first; struct Sub *volatile second; struct Sub *volatile third; };
extern u8 gEffectGfxTable[];
extern u16 D_080CF1F8[];
extern u16 D_080CF230[];
extern u16 D_080CF268[];

/* Allocate and initialize three sub-objects from the definition's stat and parameter
 * tables; if any allocation fails, dispatch the entity's pending callback instead. */
void initThreeSubObjects(u8 *entity, u8 *def, s32 payload, struct SubObjects *out) {
    u8 *statsTable;
    void *firstObj;
    void *secondObj;
    void *thirdObj;
    u16 *params;
#define RECORD_OFFSET ((*(s16 *)(def + 0x1C)) * 40)
    params = D_080CF1F8;
    firstObj = allocEffectPart();
    out->first = firstObj;
    if (firstObj == NULL) {
        sub_080C31E0(entity, *(s32 *)(entity + 0x24));
        return;
    }
    ((struct Sub *)firstObj)->active = 0;
    out->first->type = 8;
    out->first->subtype = 1;
    out->first->dataWord = (statsTable = gEffectGfxTable, *(u16 *)(statsTable + RECORD_OFFSET + 4));
    out->first->param6 = params[0];
    out->first->param8 = params[1];
    out->first->paramA = params[2];
    out->first->paramC = params[3];
    out->first->paramE = *(u16 *)(statsTable + RECORD_OFFSET + 6);
    out->first->payload = payload;

    params = D_080CF230;
    secondObj = allocEffectPart();
    out->second = secondObj;
    if (secondObj == NULL) {
        sub_080C31E0(entity, *(s32 *)(entity + 0x24));
        return;
    }
    ((struct Sub *)secondObj)->active = 0;
    out->second->type = 8;
    out->second->subtype = 1;
    out->second->dataWord = *(u16 *)(statsTable + RECORD_OFFSET + 4);
    out->second->param6 = params[0];
    out->second->param8 = params[1];
    out->second->paramA = params[2];
    out->second->paramC = params[3];
    out->second->paramE = *(u16 *)(statsTable + RECORD_OFFSET + 6);
    out->second->payload = payload;

    params = D_080CF268;
    thirdObj = allocEffectPart();
    out->third = thirdObj;
    if (thirdObj == NULL) {
        sub_080C31E0(entity, *(s32 *)(entity + 0x24));
        return;
    }
    ((struct Sub *)thirdObj)->active = 0;
    out->third->type = 8;
    out->third->subtype = 1;
    out->third->dataWord = *(u16 *)(statsTable + RECORD_OFFSET + 4);
    out->third->param6 = params[0];
    out->third->param8 = params[1];
    out->third->paramA = params[2];
    out->third->paramC = params[3];
    out->third->paramE = *(u16 *)(statsTable + RECORD_OFFSET + 6);
    out->third->payload = payload;
#undef RECORD_OFFSET
}
