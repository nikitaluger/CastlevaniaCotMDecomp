struct SoundObject {
    u8 pad[0x70];
    u8 flag;
};

/* Script action 0x1E: mark the object at work+0xC8 active (byte +0x70 = 1). */
void sub_080B0974(struct SoundObject *obj) {
    obj->flag = 1;
}
