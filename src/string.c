int strEqual(const char *str1, const char *str2) {
        while (*str1 && (*str1 == *str2)) {
                str1++;
                str2++;
        }
        return *str1 == *str2;
}

void strCopy(char *dest, const char *src, int n) {
        int i = 0;  
        for (; i < n && src[i] != '\0'; i++) dest[i] = src[i];
        dest[i] = '\0'; 
}

void intToStr(int num, char *str, int size) {
	int i = 0;
	if (num == 0) str[i++] = '0';
	else {
		if (num < 0) {
			str[i++] = '-';
			num = -num;
		}
		while (num > 0 && i < size - 1) {
			str[i++] = (num % 10) + '0';
			num /= 10;
		}
		str[i] = '\0';

		// reverse string to get correct representatiion
		for (int j = 0, k = i - 1; j < k; j++, k--) {
			char tmp = str[j];
			str[j] = str[k];
			str[k] = tmp;
		}
	}
	str[i] = '\0';
}

int strToInt(const char *str) {
	int num = 0, sign = 1; 
	if (*str == '-') { // check for negative number
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9') {
		num = num * 10 + (*str - '0');
		str++;
	}
	return sign * num;
}

