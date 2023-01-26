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

char *str_replace(char *str, char rep, char with) {
    char *ptr = str;
    while ((ptr = strchr (ptr, rep)) != NULL) *ptr++ = with;
    return str;
}

char *shortenStrF(char *str)
{
    while(str[(strlen(str)) - 1] == '0') {
        str[(strlen(str)) - 1] = '\0';
    }
    if(str[(strlen(str)) - 1] == '.') {
        str[(strlen(str)) - 1] = '\0';
    }
    return str;
}

int main(void)
{
    os_ClrHome();
    os_SetCursorPos(0,0);
    int polyLength;
    char pL[5];
    os_GetStringInput("Polynomial Length: ", pL,5);
    os_SetCursorPos(1,0);
    polyLength = strtod(pL, NULL);
    float nums[10];
    dbg_printf("polyLength: %d\n",polyLength);

    for(int i = 0; i < polyLength; i++) {
        char p[5];
        char prompt[10];
        sprintf(prompt,"Num%d: ",i + 1);
        os_GetStringInput(prompt,p,5);
        dbg_printf("input: %s\n", p);
        os_SetCursorPos(i + 2,0);
        char *newpL = str_replace(p,'\x1A','-');
        nums[i] = strtof(newpL,NULL);
        free(newpL);
        //dbg_printf("inputAsNum: %f\n", atof(newpL));
        dbg_printf("inputAsNum: %f\n", nums[i]);
        //free(newpL);
        //dbg_printf("first: %f\n", nums[1]);
    }
    dbg_printf("first: %f\n", nums[0]);
    char divStr[10];
    float divNum;
    os_GetStringInput("Dividing Number: ", divStr,10);
    os_SetCursorPos(polyLength + 2,0);

    divNum = strtof(str_replace(divStr,'\x1A','-'), NULL);
    char out[20];
    char buf[20];
    sprintf(buf,"%f", nums[0]);
    sprintf(out,"%s", shortenStrF(buf));
    float outNums[10];
    outNums[0] = nums[0];
    for(int i = 1; i < polyLength; i++) {
        float nextNum = (outNums[i-1] * divNum) + nums[i];
        dbg_printf("Next Num: %f\n", nextNum);
        outNums[i] = nextNum;
    }
    for(int i = 1; i < polyLength; i++) {
        char buf1[20];
        sprintf(buf1,"%f",outNums[i]);
        sprintf(out,"%s, %s",out, shortenStrF(buf1));
    }
    os_PutStrLine(out);
    os_SetCursorPos(polyLength + 3,0);
    os_PutStrLine("Press Any Key To Exit");
    while(!os_GetCSC());
    return 0;
}
