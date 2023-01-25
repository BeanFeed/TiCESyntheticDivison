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
#include <stdio.h>
int main(void)
{
    os_ClrHome();
    os_SetCursorPos(0,0);
    int polyLength;
    char pL[1];
    os_GetStringInput("Polynomial Length: ", pL,1);
    polyLength = atoi(pL);
    float nums[polyLength];
    for(int i = 0; i < polyLength; i++) {
        char pL[2];
        char prompt[10];
        sprintf(prompt,"Num%d: ",i);
        os_GetStringInput(prompt,pL,2);
        nums[i] = atof(pL);
    }
    char divStr[2];
    float divNum;
    os_GetStringInput("Dividing Number: ", divStr,2);
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
    return 0;
}
