/*
 * author:	luo feng
 * date:	2013/10/30
 * source:	剑指Offer
 * URL:		http://zhedahht.blog.163.com/blog/static/2541117420071128950682/
 * language:	C++
 */
//问题描述：一个整型数组里除了两个数字之外，其它的数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度O(n)，空间复杂度O(1)。

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

class Solution {
public:
    unsigned int find_first_bit_set(int num)
    {
        int index_bit = 0;

        while((num & 1) == 0 && (index_bit < 32)) {
            num = num >> 1;
            ++index_bit;
        }

        return index_bit;
    }

    bool is_set(int num, unsigned int index_bit)
    {
        num = num >> index_bit;

        return (num & 1);
    }

    void find_nums_appear_once(vector<int> &ivec, int &num1, int &num2)
    {
        if(ivec.size() < 2)
            return;

        int result_xor = 0;
        for(vector<int>::iterator iter = ivec.begin();
                                  iter != ivec.end(); ++iter) {
            result_xor ^= *iter;
        }

        unsigned int index_bit_set = find_first_bit_set(result_xor);

        num1 = num2 = 0;
        for(vector<int>::iterator iter = ivec.begin();
                                  iter != ivec.end(); ++iter) {
            if(is_set(*iter, index_bit_set))
                num1 ^= *iter;
            else
                num2 ^= *iter;
        }
    }

    int last_bit_set(int num)
    {
        return num & ~(num -1);
    }

    void find_nums_appear_once_three(vector<int> ivec, int &num1, int &num2, int &num3)
    {
        //问题2描述：一组数字，有三个出现了一次，其它的出现了两次，找到出现一次的元素
        if(ivec.size() < 3)
            return;

        int result_xor = 0;
        for(vector<int>::iterator iter = ivec.begin();
                                  iter != ivec.end(); ++iter) {
            result_xor ^= *iter;
        }

        int flags = 0;
        for(vector<int>::iterator iter = ivec.begin();
                                  iter != ivec.end(); ++iter) {
            flags ^= last_bit_set(result_xor ^ (*iter));
        }
        flags = last_bit_set(flags);

        int first = 0;
        for(vector<int>::iterator iter = ivec.begin();
                                  iter != ivec.end(); ++iter) {
            if(last_bit_set(result_xor ^ (*iter)) == flags)
                first ^= *iter;
        }

        num1 = first;

        for(vector<int>::iterator iter = ivec.begin();
                                  iter != ivec.end(); ++iter) {
            if(*iter == first) {
                ivec.erase(iter);
                break;
            }
        }

        find_nums_appear_once(ivec, num2, num3);
    }
};

int main(int argc, char *argv[])
{
    vector<int> ivec;
    ivec.push_back(1);
    ivec.push_back(1);
    ivec.push_back(21);
    ivec.push_back(9);
    ivec.push_back(8);

    int a = 0, b = 0, c = 0;
    Solution sol;
    sol.find_nums_appear_once_three(ivec, a, b, c);
    cout<<a<<"\t"<<b<<"\t"<<c<<endl;

    return 0;
}
