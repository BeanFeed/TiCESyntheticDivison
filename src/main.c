/*
 *--------------------------------------
 * Program Name:
 * Author:
 * License:
 * Description:
 *--------------------------------------
*/
#include <stdlib.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <stdio.h>
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
    for(int i = 0; i < polyLength; i++) {
        char pL[2];
        char prompt[10];
        sprintf(prompt,"Num%d: ",i + 1);
        os_GetStringInput(prompt,pL,2);
        os_SetCursorPos(i + 2,0);
        nums[i] = atof(pL);
    }
    char divStr[2];
    float divNum;
    os_GetStringInput("Dividing Number: ", divStr,2);
    os_SetCursorPos(polyLength + 2,0);
    divNum = atof(divStr);
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
