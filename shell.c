#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parse.h"   //include declarations for parse-related structs
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include </development/libgphoto2-2.5.0/gphoto2/gphoto2.h>
#include "samples.h"

enum
BUILTIN_COMMANDS { NO_SUCH_BUILTIN=0, EXIT,JOBS};

char *
buildPrompt()
{
    return  "%";
}

int
isBuiltInCommand(char * cmd){
    
    if ( strncmp(cmd, "exit", strlen("exit")) == 0){
        return EXIT;
    }
    return NO_SUCH_BUILTIN;
}


int
main (int argc, char **argv)
{
    
    
    char * cmdLine, shell_prompt[100];
    
    int loop = 1;
    parseInfo *info; //info stores all the information returned by parser.
    struct commandType *com; //com stores command name and Arg list for one command.
    //fprintf(stderr, "Until you fix the exit command press ctrl-c to exit\n");
    Camera	*canon;
  	int	i=0, retval;
  	GPContext *canoncontext = sample_create_context();
    
    
  	gp_camera_new(&canon);
    
    
    
    
    
    
#ifdef UNIX
    
    fprintf(stdout, "This is the UNIX version\n");
#endif
    
#ifdef WINDOWS
    fprintf(stdout, "This is the WINDOWS version\n");
#endif
    
    while(loop){
        //insert your code to print prompt here.
        rl_bind_key('\t', rl_complete);
        snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s[photoshell]$ ", getenv("USER"), getcwd(NULL, 1024));
#ifdef UNIX
        cmdLine = readline(shell_prompt);
        if (cmdLine == NULL) {
            fprintf(stderr, "Unable to read command\n");
            continue;
        }
#endif
        // Add input to history.
        add_history(cmdLine);
        //insert your code about history and !x !-x here
        
        
        //prints the info struct
        //yxcprint_info(info);
        //i=strcmp(cmdLine,"preview");
        if(!strcmp(cmdLine,"preview"))
        {
            CameraFile *file;
            char output_file[32];
            
            fprintf(stderr,"preview %d\n", i);
            retval = gp_file_new(&file);
            if (retval != GP_OK) {
                fprintf(stderr,"gp_file_new: %d\n", retval);
                exit(1);
            }
            
            retval = gp_camera_capture_preview(canon, file, canoncontext);
            if (retval != GP_OK) {
                fprintf(stderr,"gp_camera_capture_preview(%d): %d\n", i, retval);
                exit(1);
            }
            sprintf(output_file, "snapshot-%03d.jpg", i);
            retval = gp_file_save(file, output_file);
            if (retval != GP_OK) {
                fprintf(stderr,"gp_camera_capture_preview(%d): %d\n", i, retval);
                exit(1);
            }
            gp_file_unref(file);
            
            i++;
        }
        if(!strcmp(cmdLine,"gpclose"))
        {
            gp_camera_exit(canon, canoncontext);
        }
        if(!strcmp(cmdLine,"gpopen"))
        {
            printf("Camera init.  Takes about 10 seconds.\n");
            retval = gp_camera_init(canon, canoncontext);
            if (retval != GP_OK) {
                printf("  Retval: %d\n", retval);
                //
                //exit (1);
            }
        }
        if(!strcmp(cmdLine,"rstPicCtr"))
        {
            i=0;
        }
        if(!strcmp(cmdLine,"autofocus"))
        {
            camera_auto_focus (canon, canoncontext);
        }
        if(!strcmp(cmdLine,"exit"))
        {
            loop = 0;
            gp_camera_exit(canon, canoncontext);
            
        }
        // free_info(info);
        free(cmdLine);
    }/* while(1) */
}






