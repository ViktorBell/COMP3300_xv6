#include "types.h"
#include "stat.h" //Note this include is not actually necessary here but I am adding it just in case
#include "user.h"

// Prints out the name of the OS as xv6 when the 'uname' command is used from the shell
/* Note: I looked into retrieving the OS information dynamically instead of just hard-coding it, and potentially trying to add flags similar to those found in standard linux,
however due to the simplified nature of xv6 as an operating system and it being run in an emulator it doesn't have the same access to system and hardware information 
that a full linux distro would have
*/
int main(int argc, char *argv[]){
    printf(1, "xv6\n");
    exit();

}