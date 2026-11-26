/* identical to sub_080191DC (matched), with its names changed by decompdecomp */
extern vu32 gMainWorkspace;
extern vu32 gMainObjTimerCallback;

void *sub_0805FAEC(s32, s32);
void sub_080161F0(void);
void sub_080C31E0(void *, u32);
void sub_080C31E4(void *, void *, u32);
void setAnimationFrame(u32, void *, u32, u32);

struct MainObj {
    u8 pad_0x00[0x22];
    s16 unk_0x22;
    u32 unk_0x24;
    u8 pad_0x28[0x38 - 0x28];
    u32 unk_0x38;
    u32 unk_0x3C;
};

struct SubObj {
    u8 pad_0x00[0x24];
    u32 unk_0x24;
    u32 unk_0x28;
    u8 pad_0x2C[0x34 - 0x2C];
    u8 unk_0x34;
};

struct ResultObj {
    u8 pad_0x00[0x4C];
    s16 unk_0x4C;
    u8 pad_0x4E[0x54 - 0x4E];
    s16 unk_0x54;
};

/* Release the object referenced by the sub-object at +0x28 (its pointer is
 * still in r0 at the call), then run that sub-object's script continuation. */
void sub_0802A030(struct MainObj *obj) {
    struct SubObj *sub = (struct SubObj *)obj->unk_0x3C;
    if (sub->unk_0x28 != 0) {
        sub_080161F0();
    }
    sub_080C31E0(obj, sub->unk_0x24);
}

void *sub_080191FC(s32 arg0, s32 arg1) {
    struct ResultObj *r2;
    s32 var_r0;
    s32 var_r1;
    void *temp_r0;

    temp_r0 = sub_0805FAEC(*(vu32 *)((u8 *)&gMainWorkspace + 0x1870), 0x89);
    if (temp_r0 == NULL) {
        return NULL;
    }
    var_r0 = arg0;
    if (var_r0 < 0) {
        var_r0 += 0xFFFF;
    }
    ((struct ResultObj *)temp_r0)->unk_0x4C = (s16)(var_r0 >> 16);
    var_r1 = arg1;
    if (var_r1 < 0) {
        var_r1 += 0xFFFF;
    }
    ((struct ResultObj *)temp_r0)->unk_0x54 = (s16)(var_r1 >> 16);
    return temp_r0;
}

void MainObj_CallUpdate2(struct MainObj *arg0) {
    u8 *r4 = (u8 *)arg0->unk_0x3C + 0x34;
    setAnimationFrame(arg0->unk_0x38, r4, 0x34, 0);
    if ((r4[0] & 2) != 0) {
        sub_080C31E0(arg0, arg0->unk_0x24);
    }
}

void sub_08019170(struct MainObj *arg0) {
    u8 *r1;
    u8 *temp;
    s16 idx;

    setAnimationFrame(arg0->unk_0x38, (u8 *)arg0->unk_0x3C + 0x34, 0x2B, 1);
    idx = arg0->unk_0x22;
    temp = (u8 *)arg0 + idx * 2;
    if (temp[0x19] > 0x1E) {
        temp[0x19] = 0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, gMainObjTimerCallback);
    }
}
