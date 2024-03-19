#!/bin/bash
###############################################################################
## ISCTE-IUL: Sistemas Operativos | Operating Systems
##
## Module Name: so_utils_tester.sh
## @author Carlos Coutinho
## Module Description/Explanation:
##      This module performs multiple tests intended to demonstrate (and test)
##      the funcionalities of the module /home/so/utils/bin/so_utils.sh
##
## SYNTAX: so_utils_tester.sh
###############################################################################
# SO_HIDE_DEBUG=1                   ## Uncomment this line to hide all @DEBUG statements
# SO_HIDE_COLOURS=1                 ## Uncomment this line to disable all escape colouring
. /home/so/utils/bin/so_utils.sh    ## This is required to activate the macros so_success, so_error, and so_debug (and others)

so_debug "#1: Colour Tests"
so_debug "#1.1: Foreground Colours"
echo -e "${COLOUR_BLACK}BLACK ${COLOUR_BOLD_BLACK}BOLD_BLACK ${COLOUR_NONE}${COLOUR_FAINT_BLACK}FAINT_BLACK ${COLOUR_NONE}${COLOUR_ITALIC_BLACK}ITALIC_BLACK ${COLOUR_NONE}${COLOUR_UNDERLINE_BLACK}UNDERLINE_BLACK${COLOUR_NONE}"
echo -e "${COLOUR_GRAY}GRAY ${COLOUR_NONE}${COLOUR_BOLD_GRAY}BOLD_GRAY ${COLOUR_NONE}${COLOUR_FAINT_GRAY}FAINT_GRAY ${COLOUR_NONE}${COLOUR_ITALIC_GRAY}ITALIC_GRAY ${COLOUR_NONE}${COLOUR_UNDERLINE_GRAY}UNDERLINE_GRAY${COLOUR_NONE}"
echo -e "${COLOUR_LIGHTGRAY}LIGHTGRAY ${COLOUR_NONE}${COLOUR_BOLD_LIGHTGRAY}BOLD_LIGHTGRAY ${COLOUR_NONE}${COLOUR_FAINT_LIGHTGRAY}FAINT_LIGHTGRAY ${COLOUR_NONE}${COLOUR_ITALIC_LIGHTGRAY}ITALIC_LIGHTGRAY ${COLOUR_NONE}${COLOUR_UNDERLINE_LIGHTGRAY}UNDERLINE_LIGHTGRAY${COLOUR_NONE}"
echo -e "${COLOUR_WHITE}WHITE ${COLOUR_NONE}${COLOUR_BOLD_WHITE}BOLD_WHITE ${COLOUR_NONE}${COLOUR_FAINT_WHITE}FAINT_WHITE ${COLOUR_NONE}${COLOUR_ITALIC_WHITE}ITALIC_WHITE ${COLOUR_NONE}${COLOUR_UNDERLINE_WHITE}UNDERLINE_WHITE${COLOUR_NONE}"
echo -e "${COLOUR_BLUE}BLUE ${COLOUR_NONE}${COLOUR_BOLD_BLUE}BOLD_BLUE ${COLOUR_NONE}${COLOUR_FAINT_BLUE}FAINT_BLUE ${COLOUR_NONE}${COLOUR_ITALIC_BLUE}ITALIC_BLUE ${COLOUR_NONE}${COLOUR_UNDERLINE_BLUE}UNDERLINE_BLUE${COLOUR_NONE}"
echo -e "${COLOUR_LIGHTBLUE}LIGHTBLUE ${COLOUR_NONE}${COLOUR_BOLD_LIGHTBLUE}BOLD_LIGHTBLUE ${COLOUR_NONE}${COLOUR_FAINT_LIGHTBLUE}FAINT_LIGHTBLUE ${COLOUR_NONE}${COLOUR_ITALIC_LIGHTBLUE}ITALIC_LIGHTBLUE ${COLOUR_NONE}${COLOUR_UNDERLINE_LIGHTBLUE}UNDERLINE_LIGHTBLUE${COLOUR_NONE}"
echo -e "${COLOUR_CYAN}CYAN ${COLOUR_NONE}${COLOUR_BOLD_CYAN}BOLD_CYAN ${COLOUR_NONE}${COLOUR_FAINT_CYAN}FAINT_CYAN ${COLOUR_NONE}${COLOUR_ITALIC_CYAN}ITALIC_CYAN ${COLOUR_NONE}${COLOUR_UNDERLINE_CYAN}UNDERLINE_CYAN${COLOUR_NONE}"
echo -e "${COLOUR_LIGHTCYAN}LIGHTCYAN ${COLOUR_NONE}${COLOUR_BOLD_LIGHTCYAN}BOLD_LIGHTCYAN ${COLOUR_NONE}${COLOUR_FAINT_LIGHTCYAN}FAINT_LIGHTCYAN ${COLOUR_NONE}${COLOUR_ITALIC_LIGHTCYAN}ITALIC_LIGHTCYAN ${COLOUR_NONE}${COLOUR_UNDERLINE_LIGHTCYAN}UNDERLINE_LIGHTCYAN${COLOUR_NONE}"
echo -e "${COLOUR_GREEN}GREEN ${COLOUR_NONE}${COLOUR_BOLD_GREEN}BOLD_GREEN ${COLOUR_NONE}${COLOUR_FAINT_GREEN}FAINT_GREEN ${COLOUR_NONE}${COLOUR_ITALIC_GREEN}ITALIC_GREEN ${COLOUR_NONE}${COLOUR_UNDERLINE_GREEN}UNDERLINE_GREEN${COLOUR_NONE}"
echo -e "${COLOUR_LIGHTGREEN}LIGHTGREEN ${COLOUR_NONE}${COLOUR_BOLD_LIGHTGREEN}BOLD_LIGHTGREEN ${COLOUR_NONE}${COLOUR_FAINT_LIGHTGREEN}FAINT_LIGHTGREEN ${COLOUR_NONE}${COLOUR_ITALIC_LIGHTGREEN}ITALIC_LIGHTGREEN ${COLOUR_NONE}${COLOUR_UNDERLINE_LIGHTGREEN}UNDERLINE_LIGHTGREEN${COLOUR_NONE}"
echo -e "${COLOUR_RED}RED ${COLOUR_NONE}${COLOUR_BOLD_RED}BOLD_RED ${COLOUR_NONE}${COLOUR_FAINT_RED}FAINT_RED ${COLOUR_NONE}${COLOUR_ITALIC_RED}ITALIC_RED ${COLOUR_NONE}${COLOUR_UNDERLINE_RED}UNDERLINE_RED${COLOUR_NONE}"
echo -e "${COLOUR_LIGHTRED}LIGHTRED ${COLOUR_NONE}${COLOUR_BOLD_LIGHTRED}BOLD_LIGHTRED ${COLOUR_NONE}${COLOUR_FAINT_LIGHTRED}FAINT_LIGHTRED ${COLOUR_NONE}${COLOUR_ITALIC_LIGHTRED}ITALIC_LIGHTRED ${COLOUR_NONE}${COLOUR_UNDERLINE_LIGHTRED}UNDERLINE_LIGHTRED${COLOUR_NONE}"
echo -e "${COLOUR_MAGENTA}MAGENTA ${COLOUR_NONE}${COLOUR_BOLD_MAGENTA}BOLD_MAGENTA ${COLOUR_NONE}${COLOUR_FAINT_MAGENTA}FAINT_MAGENTA ${COLOUR_NONE}${COLOUR_ITALIC_MAGENTA}ITALIC_MAGENTA ${COLOUR_NONE}${COLOUR_UNDERLINE_MAGENTA}UNDERLINE_MAGENTA${COLOUR_NONE}"
echo -e "${COLOUR_LIGHTMAGENTA}LIGHTMAGENTA ${COLOUR_NONE}${COLOUR_BOLD_LIGHTMAGENTA}BOLD_LIGHTMAGENTA ${COLOUR_NONE}${COLOUR_FAINT_LIGHTMAGENTA}FAINT_LIGHTMAGENTA ${COLOUR_NONE}${COLOUR_ITALIC_LIGHTMAGENTA}ITALIC_LIGHTMAGENTA ${COLOUR_NONE}${COLOUR_UNDERLINE_LIGHTMAGENTA}UNDERLINE_LIGHTMAGENTA${COLOUR_NONE}"
echo -e "${COLOUR_YELLOW}YELLOW ${COLOUR_NONE}${COLOUR_BOLD_YELLOW}BOLD_YELLOW ${COLOUR_NONE}${COLOUR_FAINT_YELLOW}FAINT_YELLOW ${COLOUR_NONE}${COLOUR_ITALIC_YELLOW}ITALIC_YELLOW ${COLOUR_NONE}${COLOUR_UNDERLINE_YELLOW}UNDERLINE_YELLOW${COLOUR_NONE}"
echo -e "${COLOUR_LIGHTYELLOW}LIGHTYELLOW ${COLOUR_NONE}${COLOUR_BOLD_LIGHTYELLOW}BOLD_LIGHTYELLOW ${COLOUR_NONE}${COLOUR_FAINT_LIGHTYELLOW}FAINT_LIGHTYELLOW ${COLOUR_NONE}${COLOUR_ITALIC_LIGHTYELLOW}ITALIC_LIGHTYELLOW ${COLOUR_NONE}${COLOUR_UNDERLINE_LIGHTYELLOW}UNDERLINE_LIGHTYELLOW${COLOUR_NONE}"
echo
so_debug "#1.2: Background Colours"
echo -e "${COLOUR_BACK_BLACK}BACK_BLACK ${COLOUR_BACK_BOLD_BLACK}BACK_BOLD_BLACK ${COLOUR_NONE}${COLOUR_BACK_FAINT_BLACK}BACK_FAINT_BLACK ${COLOUR_NONE}${COLOUR_BACK_ITALIC_BLACK}BACK_ITALIC_BLACK ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_BLACK}BACK_UNDERLINE_BLACK${COLOUR_NONE}"
echo -e "${COLOUR_BACK_GRAY}BACK_GRAY ${COLOUR_NONE}${COLOUR_BACK_BOLD_GRAY}BACK_BOLD_GRAY ${COLOUR_NONE}${COLOUR_BACK_FAINT_GRAY}BACK_FAINT_GRAY ${COLOUR_NONE}${COLOUR_BACK_ITALIC_GRAY}BACK_ITALIC_GRAY ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_GRAY}BACK_UNDERLINE_GRAY${COLOUR_NONE}"
echo -e "${COLOUR_BACK_LIGHTGRAY}BACK_LIGHTGRAY ${COLOUR_NONE}${COLOUR_BACK_BOLD_LIGHTGRAY}BACK_BOLD_LIGHTGRAY ${COLOUR_NONE}${COLOUR_BACK_FAINT_LIGHTGRAY}BACK_FAINT_LIGHTGRAY ${COLOUR_NONE}${COLOUR_BACK_ITALIC_LIGHTGRAY}BACK_ITALIC_LIGHTGRAY ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_LIGHTGRAY}BACK_UNDERLINE_LIGHTGRAY${COLOUR_NONE}"
echo -e "${COLOUR_BACK_WHITE}BACK_WHITE ${COLOUR_NONE}${COLOUR_BACK_BOLD_WHITE}BACK_BOLD_WHITE ${COLOUR_NONE}${COLOUR_BACK_FAINT_WHITE}BACK_FAINT_WHITE ${COLOUR_NONE}${COLOUR_BACK_ITALIC_WHITE}BACK_ITALIC_WHITE ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_WHITE}BACK_UNDERLINE_WHITE${COLOUR_NONE}"
echo -e "${COLOUR_BACK_BLUE}BACK_BLUE ${COLOUR_NONE}${COLOUR_BACK_BOLD_BLUE}BACK_BOLD_BLUE ${COLOUR_NONE}${COLOUR_BACK_FAINT_BLUE}BACK_FAINT_BLUE ${COLOUR_NONE}${COLOUR_BACK_ITALIC_BLUE}BACK_ITALIC_BLUE ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_BLUE}BACK_UNDERLINE_BLUE${COLOUR_NONE}"
echo -e "${COLOUR_BACK_LIGHTBLUE}BACK_LIGHTBLUE ${COLOUR_NONE}${COLOUR_BACK_BOLD_LIGHTBLUE}BACK_BOLD_LIGHTBLUE ${COLOUR_NONE}${COLOUR_BACK_FAINT_LIGHTBLUE}BACK_FAINT_LIGHTBLUE ${COLOUR_NONE}${COLOUR_BACK_ITALIC_LIGHTBLUE}BACK_ITALIC_LIGHTBLUE ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_LIGHTBLUE}BACK_UNDERLINE_LIGHTBLUE${COLOUR_NONE}"
echo -e "${COLOUR_BACK_CYAN}BACK_CYAN ${COLOUR_NONE}${COLOUR_BACK_BOLD_CYAN}BACK_BOLD_CYAN ${COLOUR_NONE}${COLOUR_BACK_FAINT_CYAN}BACK_FAINT_CYAN ${COLOUR_NONE}${COLOUR_BACK_ITALIC_CYAN}BACK_ITALIC_CYAN ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_CYAN}BACK_UNDERLINE_CYAN${COLOUR_NONE}"
echo -e "${COLOUR_BACK_LIGHTCYAN}BACK_LIGHTCYAN ${COLOUR_NONE}${COLOUR_BACK_BOLD_LIGHTCYAN}BACK_BOLD_LIGHTCYAN ${COLOUR_NONE}${COLOUR_BACK_FAINT_LIGHTCYAN}BACK_FAINT_LIGHTCYAN ${COLOUR_NONE}${COLOUR_BACK_ITALIC_LIGHTCYAN}BACK_ITALIC_LIGHTCYAN ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_LIGHTCYAN}BACK_UNDERLINE_LIGHTCYAN${COLOUR_NONE}"
echo -e "${COLOUR_BACK_GREEN}BACK_GREEN ${COLOUR_NONE}${COLOUR_BACK_BOLD_GREEN}BACK_BOLD_GREEN ${COLOUR_NONE}${COLOUR_BACK_FAINT_GREEN}BACK_FAINT_GREEN ${COLOUR_NONE}${COLOUR_BACK_ITALIC_GREEN}BACK_ITALIC_GREEN ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_GREEN}BACK_UNDERLINE_GREEN${COLOUR_NONE}"
echo -e "${COLOUR_BACK_LIGHTGREEN}BACK_LIGHTGREEN ${COLOUR_NONE}${COLOUR_BACK_BOLD_LIGHTGREEN}BACK_BOLD_LIGHTGREEN ${COLOUR_NONE}${COLOUR_BACK_FAINT_LIGHTGREEN}BACK_FAINT_LIGHTGREEN ${COLOUR_NONE}${COLOUR_BACK_ITALIC_LIGHTGREEN}BACK_ITALIC_LIGHTGREEN ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_LIGHTGREEN}BACK_UNDERLINE_LIGHTGREEN${COLOUR_NONE}"
echo -e "${COLOUR_BACK_RED}BACK_RED ${COLOUR_NONE}${COLOUR_BACK_BOLD_RED}BACK_BOLD_RED ${COLOUR_NONE}${COLOUR_BACK_FAINT_RED}BACK_FAINT_RED ${COLOUR_NONE}${COLOUR_BACK_ITALIC_RED}BACK_ITALIC_RED ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_RED}BACK_UNDERLINE_RED${COLOUR_NONE}"
echo -e "${COLOUR_BACK_LIGHTRED}BACK_LIGHTRED ${COLOUR_NONE}${COLOUR_BACK_BOLD_LIGHTRED}BACK_BOLD_LIGHTRED ${COLOUR_NONE}${COLOUR_BACK_FAINT_LIGHTRED}BACK_FAINT_LIGHTRED ${COLOUR_NONE}${COLOUR_BACK_ITALIC_LIGHTRED}BACK_ITALIC_LIGHTRED ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_LIGHTRED}BACK_UNDERLINE_LIGHTRED${COLOUR_NONE}"
echo -e "${COLOUR_BACK_MAGENTA}BACK_MAGENTA ${COLOUR_NONE}${COLOUR_BACK_BOLD_MAGENTA}BACK_BOLD_MAGENTA ${COLOUR_NONE}${COLOUR_BACK_FAINT_MAGENTA}BACK_FAINT_MAGENTA ${COLOUR_NONE}${COLOUR_BACK_ITALIC_MAGENTA}BACK_ITALIC_MAGENTA ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_MAGENTA}BACK_UNDERLINE_MAGENTA${COLOUR_NONE}"
echo -e "${COLOUR_BACK_LIGHTMAGENTA}BACK_LIGHTMAGENTA ${COLOUR_NONE}${COLOUR_BACK_BOLD_LIGHTMAGENTA}BACK_BOLD_LIGHTMAGENTA ${COLOUR_NONE}${COLOUR_BACK_FAINT_LIGHTMAGENTA}BACK_FAINT_LIGHTMAGENTA ${COLOUR_NONE}${COLOUR_BACK_ITALIC_LIGHTMAGENTA}BACK_ITALIC_LIGHTMAGENTA ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_LIGHTMAGENTA}BACK_UNDERLINE_LIGHTMAGENTA${COLOUR_NONE}"
echo -e "${COLOUR_BACK_YELLOW}BACK_YELLOW ${COLOUR_NONE}${COLOUR_BACK_BOLD_YELLOW}BACK_BOLD_YELLOW ${COLOUR_NONE}${COLOUR_BACK_FAINT_YELLOW}BACK_FAINT_YELLOW ${COLOUR_NONE}${COLOUR_BACK_ITALIC_YELLOW}BACK_ITALIC_YELLOW ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_YELLOW}BACK_UNDERLINE_YELLOW${COLOUR_NONE}"
echo -e "${COLOUR_BACK_LIGHTYELLOW}BACK_LIGHTYELLOW ${COLOUR_NONE}${COLOUR_BACK_BOLD_LIGHTYELLOW}BACK_BOLD_LIGHTYELLOW ${COLOUR_NONE}${COLOUR_BACK_FAINT_LIGHTYELLOW}BACK_FAINT_LIGHTYELLOW ${COLOUR_NONE}${COLOUR_BACK_ITALIC_LIGHTYELLOW}BACK_ITALIC_LIGHTYELLOW ${COLOUR_NONE}${COLOUR_BACK_UNDERLINE_LIGHTYELLOW}BACK_UNDERLINE_LIGHTYELLOW${COLOUR_NONE}"

echo;echo
so_debug "#2 Test SUCCESS macro" "#2.1 with step name only" "#2.2 with step name and more info" "#2.3 with info without step name"
so_success "S1.2.3"         # This macro shows only @SUCCESS and step name
so_success "S4.5.6" "#2.2" "This is the same as previous but also can show strings" 'and also values:' 123 "and even variables:$HOME" "putting all within square brackets so don't loose spaces or line breaks"
so_success "" "#2.3" "This is the same as the previous" "but does not show the step name (not to be used in the SO assignment)"

echo;echo
so_debug "#3 Test ERROR macro" "#3.1 with step name only" "#3.2 with step name and more info" "#3.3 with info without step name"
so_error "S1.2.3"           # This macro shows only @ERROR and step name
so_error "S4.5.6" "#3.2" "This is the same as previous but also can show strings" 'and also values:' 123 "and even variables:$HOME" "putting all within square brackets so you don't loose spaces or line breaks"
so_error "" "#3.3" "This is the same as the previous" "but does not show the step name (not to be used in the SO assignment)"

echo;echo
so_debug "#4 Test DEBUG macro" "#4.1 shows only the invoking script name and line number" "#4.2 with script name, line number and more info" "#4.3 disable DEBUG"
so_debug                    # This macro shows only @DEBUG, the invoking script name and line number
so_debug "#4.2" "This is the same as previous but also can show strings" 'and also values:' 123 "and even variables:$HOME" "putting all within square brackets so you don't loose spaces or line breaks"
so_debug "#4.2" "A good practice is to always keep an eye on your variables, e.g., check variable var_abc" "var_abc:$var_abc"
var_abc=12345
so_debug "#4.2" "Same as previously, but AFTER setting the variable var_abc" "var_abc:$var_abc"

so_debug "#4.3" "I will now enable SO_HIDE_DEBUG"
so_debug "#4.3" "Now you still see debug messages"
SO_HIDE_DEBUG=1             # This line hides all following @DEBUG statements
so_debug "#4.3" "Now you DON'T see any more debug messages"
so_success "" "I bet you did not see the previous debug message, saying \"Now you DON'T see any more debug messages\""
SO_HIDE_DEBUG=
so_debug "#4.3" "Now you should see debug messages again"

echo;echo
so_debug "#5 Test disable escape colouring messages" "#5.1 using an environment variable" "#5.2 Calling so_utils.sh with an argument"
so_debug "#5.1 Test colours disabling using an environment variable"
SO_HIDE_COLOURS=1           # This line enables the variable to HIDE all following escape colours of the statements defined using so_define_colours.sh
. /home/so/utils/bin/so_utils.sh    # To change the colouring, you need to invoke again so_utils.sh
so_success "S1.3.5" "#5.1 this has the same information as the base macro" "but displays the information COLOURLESS" "(with no escape colours)" "$HOME" "Info 4"
so_error "S1.3.5" "#5.1 this has the same information as the base macro" "but displays the information COLOURLESS" "(with no escape colours)" "$HOME" "Info 4"
so_debug "#5.1 this has the same information as the base macro" "but displays the information COLOURLESS" "(with no escape colours)" "$HOME" "Info 4"
SO_HIDE_COLOURS=            # This line disables the variable to SHOW all following escape colours of the statements defined using so_define_colours.sh
. /home/so/utils/bin/so_utils.sh    # To change the colouring, you need to invoke again so_utils.sh
so_success "S2.4.6" "#5.1 this has the same information as the base macro" "and displays the information COLOURFUL" "Feature 2" "$HOME" "Info 4"
so_error "S2.4.6" "#5.1 this has the same information as the base macro" "but displays the information COLOURFUL" "Feature 2" "$HOME" "Info 4"
so_debug "#5.1 this has the same information as the base macro" "but displays the information COLOURFUL" "Feature 2" "$HOME" "Info 4"

so_debug "#5.2 Test colours disabling passing disable/enable-colours as argument to so_utils.sh"
. /home/so/utils/bin/so_utils.sh disable-colours    # passing disable-colours to HIDE all following escape colours of the statements defined using so_define_colours.sh
so_success "S1.1.1" "#5.2 this has the same information as the base macro" "but displays the information COLOURLESS" "(with no escape colours)" "$HOME" "Info 4"
so_error "S1.1.1" "#5.2 this has the same information as the base macro" "but displays the information COLOURLESS" "(with no escape colours)" "$HOME" "Info 4"
so_debug "#5.2 this has the same information as the base macro" "but displays the information COLOURLESS" "(with no escape colours)" "$HOME" "Info 4"
. /home/so/utils/bin/so_utils.sh                    # passing no arguments to maintain disabled colouring
so_success "S2.2.2" "#5.2 this has the same information as the base macro" "but displays the information COLOURLESS" "(with no escape colours)" "$HOME" "Info 4"
so_error "S2.2.2" "#5.2 this has the same information as the base macro" "but displays the information COLOURLESS" "(with no escape colours)" "$HOME" "Info 4"
so_debug "#5.2 this has the same information as the base macro" "but displays the information COLOURLESS" "(with no escape colours)" "$HOME" "Info 4"
. /home/so/utils/bin/so_utils.sh enable-colours     # passing enable-colours to SHOW all following escape colours of the statements defined using so_define_colours.sh
so_success "S3.3.3" "#5.2 this has the same information as the base macro" "and displays the information COLOURFUL" "Feature 2" "$HOME" "Info 4"
so_error "S3.3.3" "#5.2 this has the same information as the base macro" "but displays the information COLOURFUL" "Feature 2" "$HOME" "Info 4"
so_debug "#5.2 this has the same information as the base macro" "but displays the information COLOURFUL" "Feature 2" "$HOME" "Info 4"
. /home/so/utils/bin/so_utils.sh # passing no arguments will maintain enabled colouring (default)
so_success "S4.4.4" "#5.2 this has the same information as the base macro" "and displays the information COLOURFUL" "Feature 2" "$HOME" "Info 4"
so_error "S4.4.4" "#5.2 this has the same information as the base macro" "but displays the information COLOURFUL" "Feature 2" "$HOME" "Info 4"
so_debug "#5.2 this has the same information as the base macro" "but displays the information COLOURFUL" "Feature 2" "$HOME" "Info 4"

echo;echo
so_debug "#6 Test so_pause_on_all_commands / so_debug_on_all_commands macro" "#6.1 so_pause_on_all_commands" "#6.2 so_release_pause_on_all_commands" "#6.3 so_pause_debug_on_all_commands"
so_debug "#6.1 so_pause_on_all_commands"
so_pause_on_all_commands            # This macro pauses before running each of the next script lines until you press any key (slowly running each script line)
so_success "S5.5.5" "#6.1 this and the following lines will only be shown only after you press any key (or CTRL+C to stop the script)"
so_error "S5.5.5" "#6.1 this and the following lines will only be shown only after you press any key (or CTRL+C to stop the script)"
so_success "S5.5.5" "#6.1 this and the following lines will only be shown only after you press any key (or CTRL+C to stop the script)"

so_debug "#6.2 so_release_pause_on_all_commands"
so_release_pause_on_all_commands    # This macro releases the pausing before running every next script lines
echo
so_success "S6.6.6" "#6.2 this and the following lines will run freely, not stopping at each line anymore"
so_error "S6.6.6" "#6.2 this and the following lines will run freely, not stopping at each line anymore"
so_success "S6.6.6" "#6.2 this and the following lines will run freely, not stopping at each line anymore"
echo

so_debug "#6.3 so_pause_debug_on_all_commands"
so_pause_debug_on_all_commands      # This macro shows the script text of the next lines, stopping before running each of them so you can DEBUG information until you enter an empty line
so_success "S7.7.7" "#6.3 this and the following lines will only be shown only after you press an empty line (or CTRL+C to stop the script)"
so_error "S7.7.7" "#6.3 in the meantime, while showing prompt \"DEBUG>\", you can run any command (e.g., echo $var_abc) or CTRL+C to stop the script"
so_success "S7.7.7" "#6.3 you can even state multiple commands, the script will only continue after you entered an empty line (or CTRL+C to stop the script)"
so_release_pause_on_all_commands    # This macro releases the pausing before running every next script lines

ls /nodir