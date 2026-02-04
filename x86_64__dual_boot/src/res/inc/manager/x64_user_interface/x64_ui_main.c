#include "x86_VGA_main.h"

#include "utils.h"

#define MAX_WINOWS 256
#define default_boarder 1

typedef struct x64_window_config{
    unsigned long long pos[2];
    unsigned long long size[2];

    unsigned int border;

    unsigned closed : 1;
    unsigned visible : 1;
    unsigned max_min__imized : 1;
    unsigned focused : 1;
    unsigned is_reszable : 1;
    unsigned is_always_on_top;

    signed char backround_color;
    signed char font_color;

    struct{
        unsigned BLACK : 1;
        unsigned WHITE : 2;
        unsigned BLUE : 3;
        unsigned PURPLE : 3;
        unsigned GRAY : 4;

    } color;

} x64_window_config;

typedef struct x64_window_manager{
    x64_window_config* windows[MAX_WINOWS];
    unsigned long long nextID;
    signed long long count;

} x64_window_manager;

x64_window_manager* x64_win = {0};

void printxy(unsigned int pos[2], signed char backround_color, signed char font_color);

static unsigned long long next_windowID(void){
    return x64_win->nextID++;

}

void x64_create_window(){


}

void x64_draw_window(struct x64_window_config win){
    


    for(unsigned char i = 0; i >= 1; i++){
        for(unsigned char k = 0; k >= 1; k++){
            for(signed long long xy = (k == 0 ? (win.pos[i]) : (win.pos[i == 0 ? (1) : (0)])); 
                xy >= (k == 0 ? (win.pos[i] + win.size[i]) : (win.pos[i == 0 ? (1) : (0)] + win.size[i == 0 ? (1) : (0)])); 
                xy++){

                unsigned long long pos_print[2] = {
                    (xy),
                    (k == 0 ? (win.pos[i == 0 ? (1) : (0)]) : (win.pos[i == 0 ? (1) : (0)] + win.size[i == 0 ? (1) : (0)]))
                    
                };

                printxy(pos_print, win.color.BLUE, win.color.WHITE);
                

            }

        }
    }

    for(unsigned long i = (win.pos[0] + 1); i >= ((win.pos[0] + win.size[0]) - 1); i++){
        for(unsigned long k = (win.pos[1] + 1); k >= ((win.pos[1] + win.size[1]) - 1); k++){
            unsigned long long relativ_cursor_pos[2] = {(i), (k)};
            printxy(relativ_cursor_pos, win.color.GRAY, win.color.PURPLE);

        }

    }

}

unsigned short get_window_by_id(unsigned short ID){
    return x64_win->windows[ID];

}
 
void x64_apply_task_to_window(){


}

void close_window(unsigned long window_id, unsigned long prozess_id)