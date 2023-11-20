#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include <assert.h>


/*void Swap(void* point1, void* point2, int typeSize)
{
    if (typeSize == sizeof(uint64_t))
    {
        uint64_t temp = *(uint64_t *)point1;
        *(uint64_t *)point1 = *(uint64_t *)point2;
        *(uint64_t *)point2 = temp;
    }

    if (typeSize == sizeof(uint32_t))
    {
        uint32_t temp = *(uint32_t *)point1;
        *(uint32_t *)point1 = *(uint32_t *)point2;
        *(uint32_t *)point2 = temp;
    }

    if (typeSize == sizeof(uint16_t))
    {
        uint16_t temp = *(uint16_t *)point1;
        *(uint16_t *)point1 = *(uint16_t *)point2;
        *(uint16_t *)point2 = temp;
    }

    if (typeSize == sizeof(uint8_t))
    {
        uint8_t temp = *(uint8_t *)point1;
        *(uint8_t *)point1 = *(uint8_t *)point2;
        *(uint8_t *)point2 = temp;
    }
}*/

void SwapOpt(void* point1, void* point2, int typeSize)
{
    void *temp = (void *)calloc(sizeof(uint64_t), sizeof(uint8_t));
    int pos = 0;

    //static_assert(sizeof(uint64_t) == 8);

    while (typeSize >>= 3)
    {
        memcpy(temp, (void *)((uint8_t *)point1 + pos), sizeof(uint64_t));
        memcpy((void *)((uint8_t *)point1 + pos), (void *)((uint8_t *)point2 + pos), sizeof(uint64_t));
        memcpy((void *)((uint8_t *)point2 + pos), temp, sizeof(uint64_t));
        pos += 8;
    }
    if (typeSize & 0x04)
    {
        memcpy(temp, (void*)((uint8_t *)point1 + pos), sizeof(uint32_t));
        memcpy((void*)((uint8_t *)point1 + pos), (void*)((uint8_t *)point2 + pos), sizeof(uint32_t));
        memcpy((void*)((uint8_t *)point2 + pos), temp, sizeof(uint32_t));
        pos += 4;
    }
    if (typeSize & 0x02)
    {
        memcpy(temp, (void*)((uint8_t *)point1 + pos), sizeof(uint16_t));
        memcpy((void*)((uint8_t *)point1 + pos), (void*)((uint8_t *)point2 + pos), sizeof(uint16_t));
        memcpy((void*)((uint8_t *)point2 + pos), temp, sizeof(uint16_t));
        pos += 2;
    }
    if (typeSize & 0x01)
    {
        memcpy(temp, (void*)((uint8_t *)point1 + pos), sizeof(uint8_t));
        memcpy((void*)((uint8_t *)point1 + pos), (void*)((uint8_t *)point2 + pos), sizeof(uint8_t));
        memcpy((void*)((uint8_t *)point2 + pos), temp, sizeof(uint8_t));        
    }
}