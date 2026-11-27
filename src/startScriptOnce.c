void sub_08098684(void *obj, u8 script, u8 param);

/* Start the given script on this object only when it is not already running. */
void startScriptOnce(void *obj, u8 script, u8 param) {
    u8 index = script;
    if (*(u8 *)((u8 *)obj + 0x24) != index) {
        sub_08098684(obj, index, param);
    }
}
