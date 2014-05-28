#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main()
{
    //float x = asin(-2.);
    //uint32_t d = *((uint32_t*)&x);
    
    uint32_t d = 0x7FD85250;
    float x = *((float*)&d);
    
    uint32_t sign = (d & 0x80000000) >> 31;
    uint32_t expo = (d & 0x7F800000) >> 23;
    uint32_t mant = (d & 0x007FFFFF);
    
    printf("%f | %08X\n", x, d);
    
    printf("sign = %d\n", sign);
    printf("expo = %02X (= %d)\n", expo, (int)expo - 127);
    printf("mant = %06X (= %f)\n", mant, (1.0 + mant / ((float)(1 << 23))));
    
    return 0;
}
