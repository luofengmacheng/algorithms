/*
 * author:	luo feng
 * date:	2014/5/13
 * source:	LeetCode
 * title:	3Sum
 * language:	C++
 * info:	求一个数列中三个元素和为0的所有情况。方法是将它转换为数列中两个元素和为0的情况，比如，-5,-2,-2,-1,1, 4, 6, 8, 这是一个已经排好序的数列。
 *		先取-5作为一种情况的第一个元素，然后在剩下的元素中找两个元素和为0-(-5)=5的情况，找到了1和4，那么就有(-5,1,4)，然后取第二个元素-2，
 *		将-2作为某种情况的第一个元素，然后在剩下的元素中找两个元素和为0-(-2)=2的情况，剩下的元素包含-5吗？也就是说考虑剩下的元素时
 *		还要考虑之前的元素吗？如果包含-5，那么-5和-2就是一个结果的三个元素中的两个，这种情况应该在考虑-5为第一个元素时已经考虑过了。
 *		因此，在确定第一个元素的时候，只要考虑它之后的元素就行了。在这里，我们确定了第一个元素是-2，那么只要考虑-2之后的两个元素和为2的情况。
 *		结果是-2和4，因此就有(-2,-2,4)，最后，当第一个元素遍历到4时，考虑6和8就行了，然后就结束了。
 *		这里没有讨论结果有重复的情况，比如，-3,-3,2,1求三个元素和为0的情况，结果就有两个(-3,2,1)，其中一个-3是原数列的第一个元素，
 *		另一个-3是原数列的第二个元素。于是，为了让结果不重复，对于已经排序好的数列，当确定第一个元素的时候，两种情况的第一个元素不应该相同，
 *		因此，当遍历确定第一个元素的时候，可以检验前一个元素的第一个值与现在的第一个值是否相同。
 *		当遍历第一个元素为原数列的第一个元素-3时，得到结果(-3,2,1)，当遍历第一个元素为原数列的第二个元素-3时，由于与前一种情况的第一个元素值相同，
 *		因此，略过当前情况，继续遍历。
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <iterator>
using namespace std;

class Solution {
public:
	vector<vector<int> > threeSum(vector<int> &num) {
		vector<vector<int> > vecresult;
		if(num.size() < 3) {
			return vecresult;
		}

		vector<int> triple(3, 0);
		sort(num.begin(), num.end());
		int count = num.size() - 2;
		int prev = num[0];
		unordered_set<int> s;
		for(int i = 0; i < count; ++i) {
			if(i && num[i] == prev) {
				continue;
			}
			s.clear();

			triple[0] = num[i];
			int j = i + 1;
			int k = num.size() - 1;
			while(j < k) {
				int sum = num[j] + num[k];
				if(sum + triple[0] == 0 && s.find(num[j]) == s.end()) {
					s.insert(num[j]);
					triple[1] = num[j];
					triple[2] = num[k];
					vecresult.push_back(triple);
					++j;
					--k;
				}
				else if(sum + triple[0] < 0) {
					++j;
				}
				else {
					--k;
				}
			}
			prev = num[i];
		}

		return vecresult;
	}
};

void print_vec(vector<int> vec)
{
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
}

int main(int argc, char const *argv[])
{
	int arr[] = {-3, -3, -3, 6};
	vector<int> ivec(arr, arr + sizeof(arr) / sizeof(arr[0]));
	Solution sol;
	vector<vector<int> > res = sol.threeSum(ivec);
	for_each(res.begin(), res.end(), print_vec);

	return 0;
}
