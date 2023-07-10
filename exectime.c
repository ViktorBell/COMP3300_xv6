/* Note:
 This program does not currently compile. The logic is all there, however it wasn't until after writing it that I realized that xv6 is not implementing stdlib.c in the same way that Unix does. Therefore I believe that the way in which I am attempting to create 2 dynamic arrays to parse the command line input as a sort of 'mini'-shell parser needs to be ammended. Digging through the xv6 files I have discovered that there us an implementation of malloc in ulib.c, however sbrk() may be required, and there is no implementation of 'realloc'.xv6 has strings and string operations however I'm not sure if the way I'm attempting to perform the string operations below is equivalent. A re-write taking this into account is needed so that the CL input can be parsed into commands and arguments properly.
*/

#include "types.h"
#include "stat.h" //Note this include is not actually necessary here but I am adding it just in case
#include "user.h"
#include "stddef.h" //Needed for NULL


/*
// Sets command char limit to 25 (current largest command is 9 char)
#define MAX_COMMAND_LENGTH 26

// Sets argument char limit to 512 (should cover almost all cases but could be increased to 4096)
#define MAX_ARGUMENT_LENGTH  513
*/

int main(int argc, char *argv[]){

    /*
    // List of xv6 commands (constructed from UPROGS list in Makefile)
    char *commandList[] = {
        "cat",
        "echo",
        "forktest",
        "grep",
        "init",
        "kill",
        "ln",
        "ls",
        "mkdir",
        "rm",
        "sh",
        "stressfs",
        "usertests",
        "wc",
        "zombie",
        "uname",
        "exectime"
        };


    int commandCapacity = 10; // initial size for currentCommandsArray; holds 10 commands by default

    // Dynamically sizable array that will hold all of the commands parsed from the CLI
    char **currentCommandsArray = malloc(commandCapacity*sizeof(char*));

    // Dynamically sizable array that will hold all of the arguments parsed from the CLI. Note each index will hold the argument(s) string for each respective command
    char **currentArgsArray = malloc(commandCapacity*sizeof(char*));

    for (int i = 0; i < commandCapacity; i++) {
        
        currentCommandsArray[i] = malloc(MAX_COMMAND_LENGTH * sizeof(char));
        currentCommandsArray[i][0] = '\0'; // Initialize to empty string

        currentArgsArray[i] = malloc(MAX_ARGUMENT_LENGTH * sizeof(char));
        currentArgsArray[i][0] = '\0'; // Initialize to empty string
    }

    char *currentCommand = malloc(MAX_ARGUMENT_LENGTH * sizeof(char)); // String that contains the 'current command' (argv[i])
    currentCommand[0] = '\0';

    int numCommands = 0;
    int numArguments = 0;

    int isCommand = 0;
    */

    /* Gets the correct value for numCommands by cross referencing the command line input with the commandList.
    Note: Does not account for edge cases like 'echo ls' where the string of the argument also happens to be a command
    */
    /*
    for(int i = 1; i < argc; i++){

        strcpy(currentCommand, argv[i]); //currentCommand = argv[i];
        isCommand = 0;

        for(int j = 0; j < (sizeof(commandList)/sizeof(commandList[0])); j++){

            if(strcmp(currentCommand, commandList[j]) == 0){
                
                isCommand = 1;
                numArguments = 0; // Resets arg count for this command
                strcpy(currentCommandsArray[numCommands], currentCommand);//currentCommandsArray[numCommands] = currentCommand;
                numCommands++;


                // Adds space for another 2 commands as required and allocates memory for the potential associated strings
                if (numCommands == commandCapacity) {
                    commandCapacity += 2;

                    currentCommandsArray = realloc(currentCommandsArray, commandCapacity * sizeof(char*));

                    currentArgsArray = realloc(currentArgsArray, commandCapacity*sizeof(char));


                    for (int k = numCommands; k < commandCapacity; k++) {
                        currentCommandsArray[k] = malloc(MAX_COMMAND_LENGTH * sizeof(char));
                        currentCommandsArray[k][0] = '\0'; // Initialize to empty string

                        currentArgsArray[k] = malloc(MAX_ARGUMENT_LENGTH * sizeof(char));
                        currentArgsArray[k][0] = '\0'; // Initialize to empty string
                    }
                }


                }
                break;
            }

        }
        // If not a command then it is an agrument of the previous command and is added to that commands associated string of arguments in currentArgsArray
        if(isCommand == 0){

            //
            strcat(currentArgsArray[numCommands], " ");
            strcat(currentArgsArray[numArguments], currentCommand);
            numArguments++;
            

        }


    }
    
    
    

    int tickTracker = uptime();
    printf(1, "Command Count ('argc' actual): %d\n", numCommands); 
    printf(1, "Start Time: %d\n", tickTracker); //Prints tick count when exectime commences

    //Iterates through all of the command line arguments (starts @ 1 so that exectime is counted as it is the 1st argument)
    for(int i = 1; i < numCommands; i++){
        
        int pid = fork();
        
        // handles fork error
        if(pid < 0){

            printf(1, "fork failed\n");

            exit();
        }

        // Child Process case 
        if(pid == 0){

            // Takes the current command (agrv[i]), and associated arguments so that it can replace the current process image appropraitely
            int execSuccess = exec(currentCommandsArray[i], currentArgsArray[i]);

            if( execSuccess < 0){
                printf(1, "exec failed code: %d\n", execSuccess);
            }
            
            
            exit();


        }
        // Parent process case (exectime is curproc)
        else{
            wait(); // Needs to wait for the current command's process to return before continuing
        }



    }
    

    
    tickTracker = uptime();
    printf(1, "End Time: %d\n", tickTracker); //Prints tick count after all command processes have finished executing

    exit();
    */

    /* Original exectime.c Logic:
    Note: The below code runs a rudimentary version of the exectime function that will show the time to completion for a single command and argument, it's command line input parsing is very simplistic.
    */
    

    int tickTracker = uptime();
    //argc--;
    printf(1, "Argument Count (argc): %d\n", argc); 
    printf(1, "Start Time: %d\n", tickTracker); //Prints tick count when exectime commences

    //Iterates through all of the command line arguments (starts @ 1 so that exectime is counted as it is the 1st argument)
    for(int i = 1; i < argc; i++){
        
        int pid = fork();
        
        // handles fork error
        if(pid < 0){

            printf(1, "fork failed\n");

            exit();
        }

        // Child Process case 
        if(pid == 0){

            char *args[] = {argv[i], argv[i+1], NULL}; // Assumes commands have a single argument/parameter (non-robust solution)

            // Takes the current command (agrv[i]), and associated arguments so that it can replace the current process image appropraitely
            int execSuccess = exec(argv[i], args);

            // This should notify of failed command execution however it causes a bug where it prints when it tries to exec() command arguments instead of commands. Ex 'exectime wc README' get failure when trying to exec README
            if( execSuccess < 0){
                printf(1, "exec failed code: %d\n", execSuccess);
            }
            
            
            exit();


        }
        // Parent process case (exectime is curproc)
        else{
            wait(); // Needs to wait for the current command's process to return before continuing
        }



    }

    //if( pid )
    tickTracker = uptime();
    printf(1, "End Time: %d\n", tickTracker); //Prints tick count after all command processes have finished executing

    exit();
    

}


   