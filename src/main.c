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


int main(void)
{
    os_ClrHome();
    os_SetCursorPos(0,0);
    int polyLength;
    char pL[5];
    os_GetStringInput("Polynomial Length: ", pL,5);
    os_SetCursorPos(1,0);
    polyLength = strtod(pL, NULL);
    float nums[polyLength];
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
    char divStr[2];
    float divNum;
    os_GetStringInput("Dividing Number: ", divStr,2);
    os_SetCursorPos(polyLength + 2,0);

    divNum = strtof(str_replace(divStr,'\x1A','-'), NULL);
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
    //while(!os_GetCSC());
    return 0;
}
