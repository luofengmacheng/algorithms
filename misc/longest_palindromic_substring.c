/*
 * author:	luo feng
 * date:	2013/10/16
 * title:	Longest Palindromic Substring
 * info:	最长回文子串
 * solution URL:http://blog.csdn.net/hopeztm/article/details/7932245
                http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
 * remark:	对最笨的方法进行了两次改进，但是由于两次改进都使用了动态内存分配，因此，改进后的时间比最笨的办法时间还长，而且，随着字符串长度的增加，所分配的内存空间成倍增加，耗费的时间更长，当然，如果能够采用静态分配空间的话，相信改进方法还是可以带来时间上的减少，只是这样不够灵活
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/* 最笨的办法，从第一个开始逐个判断，分偶数和奇数的情况分别向两边扩散，当找到第一个不一样的字符时结束 */
void longest_pal_substr1(char *str, int size, char *substr)
{
    int i = 0;
    int mid = 0, max_mid = 0, radius = 0, max_len = 0;
    int is_even = 0;

    while(i < size) {
        mid = i;
        radius = 0;
        while(mid-radius >= 0 &&
              mid+radius < size &&
              str[mid-radius] == str[mid+radius])
            radius++;
        if(2*radius-1 > max_len) {
            max_mid = mid;
            max_len = 2*radius-1;
            is_even = 1;
        }
        mid = i;
        radius = 0;
        while(mid-radius >= 0 &&
              mid+1+radius < size &&
              str[mid-radius] == str[mid+1+radius])
            radius++;
        if(2*radius > max_len) {
            max_mid = mid;
            max_len = 2*radius;
            is_even = 2;
        }
        i++;
    }
    if(is_even == 1) {
        strncpy(substr, str+max_mid-(max_len-1)/2, max_len);
    }
    else if(is_even == 2) {
        strncpy(substr, str+1+max_mid-max_len/2, max_len);
    }
    substr[max_len] = '\0';
}

void add_flag(char *str, int size)
{
    int i = 0, j = 0, len = size;
    int f_len = len+len+1;

    i = len-1;
    f_len--;
    while(i >= 0) {
        str[f_len--] = '#';
        str[f_len--] = str[i--];
    }
    str[0] = '#';
}

void remove_flag(char *str, int size)
{
    int i = 0, j = 0;

    i = 1;
    while(i < size) {
        str[j] = str[i];
        i += 2;
        j++;
    } 
}

/* 优化一：向数组中添加标志符#来分隔所有的字符，将奇数长度的回文串和偶数长度的回文串统一起来，不过由于其中多次用到了内存动态分配，可能略显麻烦 */
void longest_pal_substr2(char *str, int size, char *substr)
{
    char *newstr = (char*)calloc(size*2+1, sizeof(char));
    strncpy(newstr, str, size);
    add_flag(newstr, size);

    int i = 0, mid = 0, radius = 0;
    int len = size*2+1;
    int max_radius = 0, max_mid = 0;
    while(i < len) {
        mid = i;
        radius = 1;
        while(mid-radius > 0 &&
              mid+radius < len &&
              newstr[mid-radius] == newstr[mid+radius])
            radius++;
        radius--;
        if(radius > max_radius) {
            max_mid = mid;
            max_radius = radius;
        }
        i++;
    }

    int sub_len = 2*max_radius+1;
    char *new_substr = (char*)calloc(sub_len, sizeof(char));
    strncpy(new_substr, newstr+max_mid-max_radius, sub_len);
    remove_flag(new_substr, sub_len);
    strncpy(substr, new_substr, max_radius);
    
    free(new_substr);
    free(newstr);
}

#define min(a, b) (a)<=(b) ? (a) : (b)

/* 优化二：使用Manacher's Algorithm */
void longest_pal_substr3(char *str, int size, char *substr)
{
    int newlen = 2*size+1;
    char *newstr = (char*)calloc(newlen, sizeof(char));
    int *P = (int*)calloc(newlen, sizeof(int));
    strncpy(newstr, str, size);
    add_flag(newstr, size);

    int i = 0, i_mirror = 0;
    int center = 0, radius = 0;
    for(i = 0; i < newlen; i++) {
        i_mirror = 2*center-i;

        P[i] = (radius>i) ? min(radius-i, P[i_mirror]) : 0;

        while(newstr[i+1+P[i]] == newstr[i-1-P[i]])
            P[i]++;

        if(i+P[i] > radius) {
            center = i;
            radius = i+P[i];
        }
    }

    int max_len = 0;
    int center_index = 0;
    for(i = 0; i < newlen; i++) {
        if(P[i] > max_len) {
            max_len = P[i];
            center_index = i;
        }
    }

    //printf("center: %d\tmax_len: %d\n", center_index, max_len);
    int sub_len = 2*max_len+1;
    char *new_substr = (char*)calloc(sub_len, sizeof(char));
    strncpy(new_substr, newstr+center_index-max_len, sub_len);
    //printf("%s\n", new_substr);
    remove_flag(new_substr, sub_len);
    strncpy(substr, new_substr, max_len);

    free(P);
    free(newstr);
}

int main(int argc, char *argv[])
{
    long start_sec, finish_sec, start_usec, finish_usec;
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    start_sec = tv.tv_sec;
    start_usec = tv.tv_usec;

    char arr[] = "abacbaabcccccbaedljfkaljkdlfjkajfdkajskkhdsjdfhkshjdfhsjfhkdjhsjkfhdkjshdjfkshdfdjskhdjkfshdkjfhsfjsakjdfkaj";
    char buf[512] = "";
    longest_pal_substr3(arr, strlen(arr), buf);
    printf("%s\n", buf);

    gettimeofday(&tv, &tz);
    finish_sec = tv.tv_sec;
    finish_usec = tv.tv_usec;

    double duration = (double)(finish_usec-start_usec)/1000+(finish_sec-start_sec)*1000;
    printf("Runtime: %.3fms\n", duration);

    return 0;
}
