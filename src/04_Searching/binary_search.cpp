#include <iostream>
#include <vector>
using namespace std;
class BinarySearchItr{
public:
    //升序，假设无重复元素
    int search(vector<int>& nums, int target){
        int l = 0, r = nums.size() - 1;//闭区间，如果是nums.size(),左闭右开
        while (l <= r)
        {
            //注意防溢出
            int mid  = l + (r - l) / 2;
            if(nums[mid] == target) return mid;
            else if(nums[mid] < target) l = mid + 1;//target在右半闭区间
            else r = mid - 1;//在左半闭区间
        }
        return -1;//走完数组，未找到
    }
};

class BinarySearchRec{
public:
    int search(vector<int>& nums, int target){
        if(nums.empty()) return -1;
        return dfs(nums, 0, nums.size() - 1, target);
    }
private:
    int dfs(vector<int>& nums, int l, int r, int target){
        //递归终止条件
        if(l >= r) return -1;
        int mid = l + (r - l) / 2;
        if(nums[mid] == target) return mid;
        else if(nums[mid] < target) return dfs(nums, mid + 1, r, target);
        else return dfs(nums, l, mid - 1, target);
    } 
};
int main()
{
    vector<int> nums = {2, 4, 6, 8, 10, 12, 14, 16};
    int val1 = 10;
    int val2 = 5;
    BinarySearchItr Bs1;
    BinarySearchRec Bs2;
    cout << "===== 迭代二分 =====" << endl;
    int pos1 = Bs1.search(nums, val1);
    if (pos1 != -1)
        cout << val1 << " 下标：" << pos1 << endl;
    else
        cout << val1 << " 不存在" << endl;

    int pos2 = Bs1.search(nums, val2);
    if (pos2 != -1)
        cout << val2 << " 下标：" << pos2 << endl;
    else
        cout << val2 << " 不存在" << endl;

    cout << "\n===== 递归二分 =====" << endl;
    int pos3 = Bs2.search(nums, val1);
    if (pos3 != -1)
        cout << val1 << " 下标：" << pos3 << endl;
    else
        cout << val1 << " 不存在" << endl;

    int pos4 = Bs2.search(nums, val2);
    if (pos4 != -1)
        cout << val2 << " 下标：" << pos4 << endl;
    else
        cout << val2 << " 不存在" << endl;

    return 0;
}