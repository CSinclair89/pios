#include "string.h"
#include "hashmap.h"
#include "list.h"

int* twoSum(int *nums, int target, char *key, char *diffStr) {

	HashMap map;
	init_hashmap(&map);

        for (int i = 0; i < (sizeof(nums) / sizeof(nums[0])); i++) {
                int diff = target - nums[i];

                // convert diff to a string
                intToStr(diff, diffStr, sizeof(diffStr));
                
                // check if diff exists as key in hashmap
                int index = getValue(&map, diffStr);
                if(containsKey(&map, diffStr) > 0) esp_printf(putc, "{%d, %d}\n", index, i);
                
                // add current number to hash map
                intToStr(nums[i], key, sizeof(key));
                addEntry(&map, key, i);
  
}
