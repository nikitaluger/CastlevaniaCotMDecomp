extern void sub_08015974(void);
extern void unlinkAndFreeObject(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);
extern void sub_0801BB90(void *);
extern void sub_0801BBB4(void *);

/* Release the actor's effect handles and spawned objects, clear its extra
   object slots, then dispatch its handler at field+0x24. */
void sub_0801BB48(void *arg0)
{
    void *self;
    void *field;
    void *state;

    self = arg0;
    field = *(void **)((u8 *)arg0 + 0x3C);
    state = (u8 *)field + 0x48;
    if (*(s32 *)((u8 *)field + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)state + 0x34) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)field + 0x2C) != 0) {
        sub_08015974();
    }
    sub_0801BB90(self);
    sub_0801BBB4(self);
    sub_08016678(self);
    sub_080C31E0(self, *(s32 *)((u8 *)field + 0x24));
}
