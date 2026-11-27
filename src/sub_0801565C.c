void freeMotionTracker(void);

/* Release the ten objects tracked in the work area's pointer array: for each
 * live entry, set its flag bit 0 and empty the slot. */
void sub_08018410(void *arg0) ;
                 
                
             
                
              
          
                                       
                                  
          
        
                    
                       
                                              
                                 
         
               
            
                     
 

/* Effect countdown: when the timer at +0x1E expires, free both held objects
 * and clear effect flag bit 3 in the object's flags. */
void sub_0801572C(void *arg0, s32 *arg1, s32 *arg2) ;
                  
             
                                                
             
                                            
                                 
                                                         
                                                         
                               
     
 

/* Effect countdown: when the timer at +0x1E expires, free both held objects
 * and clear effect flag bit 2 in the object's flags. */
void sub_0801565C(void *arg0, s32 *arg1, s32 *arg2) {
    s32 remaining;
    s32 zero;
    remaining = *(u16 *)((u8 *)arg0 + 0x1E) - 1;
    zero = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = remaining;
    if ((remaining << 16) <= 0) {
        if (*arg1 != 0) { freeMotionTracker(); *arg1 = zero; }
        if (*arg2 != 0) { freeMotionTracker(); *arg2 = zero; }
        *(u16 *)arg0 &= 0xFFFB;
    }
}
