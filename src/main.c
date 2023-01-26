/*
 *--------------------------------------
 * Program Name:
 * Author:
 * License:
 * Description:
 *--------------------------------------
*/
#include <stdlib.h>
#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <ti/getkey.h>
#include <stdio.h>
#include <debug.h>
#include <ti/tokens.h>

char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

int main(void)
{
    os_ClrHome();
    os_SetCursorPos(0,0);
    int polyLength;
    char pL[5];
    os_GetStringInput("Polynomial Length: ", pL,5);
    os_SetCursorPos(1,0);
    polyLength = atoi(pL);
    float nums[polyLength];
    dbg_printf("polyLength: %d",polyLength);
    for(int i = 0; i < polyLength; i++) {
        char pL[5];
        char prompt[10];
        sprintf(prompt,"Num%d: ",i + 1);
        os_GetStringInput(prompt,pL,5);
        dbg_printf("input: %s\n", pL);
        os_SetCursorPos(i + 2,0);
        //char *newpL = str_replace(pL,"\x1A","-");
        nums[i] = atof(str_replace(pL,"\x1A","-"));
        //dbg_printf("inputAsNum: %f\n", atof(newpL));
        //dbg_printf("inputAsNum2: %f\n", nums[i]);
        //free(newpL);
        //dbg_printf("first: %f\n", nums[1]);
    }
    dbg_printf("first: %f\n", nums[0]);
    char divStr[2];
    float divNum;
    os_GetStringInput("Dividing Number: ", divStr,2);
    os_SetCursorPos(polyLength + 2,0);

    divNum = atof(str_replace(divStr,"\x1A","-"));
    char out[20];
    float outNums[polyLength];
    float prevNum = nums[0];
    outNums[0] = nums[0];
    for(int i = 1; i < polyLength; i++) {
        float nextNum = (prevNum * divNum) + nums[i]; 
        prevNum = nextNum;
        outNums[i] = nextNum;
    }
    int outNumSize = sizeof(outNums);
    for(int i = 0; i < outNumSize; i++) {
        sprintf(out,"%s, %f",out, outNums[i]);
    }
    os_PutStrLine(out);
    while(!os_GetCSC());
    return 0;
}
