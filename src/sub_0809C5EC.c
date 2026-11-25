struct ChargedObject {
    u8 pad[0x8C];
    u8 state;
};

/* Put the object into its released state once the charge attack fires. */
void sub_0809C5EC(struct ChargedObject *obj) {
    obj->state = 2;
}
