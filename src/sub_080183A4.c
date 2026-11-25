extern void sub_08015974(void);
extern void sub_080161F0(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

/* Tear down the object's attached child objects, run the cleanup helpers and
   dispatch the object's handler. */
void sub_080183A4(void *arg0)
{
    void *self;
    void *field;
    void *state;

    self = arg0;
    field = *(void **)((u8 *)arg0 + 0x3C);
    state = (u8 *)field + 0x48;
    if (*(s32 *)((u8 *)field + 0x28) != 0) {
        sub_080161F0();
    }
    if (*(s32 *)((u8 *)state + 0x34) != 0) {
        sub_080161F0();
    }
    if (*(s32 *)((u8 *)field + 0x2C) != 0) {
        sub_08015974();
    }
    sub_080183EC(self);
    sub_08018410(self);
    sub_08016678(self);
    sub_080C31E0(self, *(s32 *)((u8 *)field + 0x24));
}
