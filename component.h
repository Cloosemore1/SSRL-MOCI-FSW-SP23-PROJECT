/* component.h */
#include <stdbool.h>
#include <stdint.h>

extern void SET_CLK(bool level);
extern void SET_MOSI(bool level);
extern bool READ_MISO();
extern void clock_transition();
extern void hex_to_bool(uint8_t hex, bool *buf);
extern bool command_valid(bool *buf);
extern int bool_to_int(bool *buf);
