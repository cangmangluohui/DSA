#include <iostream>
#include <vector>
using namespace std;
class BinarySearchVariants{
public:
    //1. 升序数组查找左边界，允许重复元素
    int leftBound(const vector<int>& nums, int target){
        int l = 0, r = nums.size() - 1;
        int res = -1;//数组中若含多个目标值，需要额外变量
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if(nums[mid] == target){
                res = mid;
                r = mid - 1;//已找到，往左侧找有没有更小的下标
            }
            else if(nums[mid] < target){
                l = mid + 1;
            }
            else{
                r = mid - 1;
            }
        }
        return res;
    }
    //2. 升序数组查找右边界
    int rightBound(const vector<int>& nums, int target){
        int l = 0, r = nums.size() - 1;
        int res = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if(nums[mid] == target){
                res = mid;
                l = mid + 1;//已找到，往右侧找有没有更小的下标,右侧是l变化
            }
            else if(nums[mid] < target){
                l = mid + 1;
            }
            else{
                r = mid - 1;
            }
        }
        return res;
    }
    // 3. 查找插入位置：target插入后仍有序，返回插入下标
    // 本质：找的位置是第一个大于或等于 target 的元素的下标
    int insertIndex(const vector<int>& nums, int target){
        int l = 0, r = nums.size() - 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if(nums[mid] < target){
                l = mid + 1;//关键，找到第一个大于或等于target的值下标
            }
            else{
                r = mid - 1;
            }
        }
        return l;
    }
    // 4. 第一个严格大于 target 的元素下标，不存在返回-1
    int firstGreater(const vector<int>& nums, int target){
        int l = 0, r = nums.size() - 1;
        int res = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if(nums[mid] > target){
                res = mid;//暂存，并往左找是否还有大于target元素
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return res;
    }
    // 5. 最后一个严格小于 target 的元素下标，不存在返回-1
    int lastLess(const vector<int>& nums, int target){
        int l = 0, r = nums.size() - 1;
        int res = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if(nums[mid] < target){
                res = mid;//暂存，并往右找是否还有小于target元素
                l = mid + 1;
            }
            else r = mid - 1;
        }
        return res;
    }
    // 6. 统计target出现次数：左右边界相减+1，不存在返回0
    int countTarget(const vector<int>& arr, int target) {
        int l = leftBound(arr, target);
        if (l == -1) return 0;//如果没有左边界，直接返回0
        int r = rightBound(arr, target);
        return r - l + 1;
    }
    // 7. 升序数组旋转后找最小值（无重复元素）
    int MinRotate(const vector<int>& nums) {
        int l = 0;
        int r = nums.size() - 1;
        if (nums[l] < nums[r]) return nums[l];//未旋转，返回首元素
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] > nums[r]) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return nums[l];
    }
    // 8. 旋转数组查找目标值（无重复），存在返回下标，否则-1
    int searchRotate(vector<int>& nums, int target){
        int l = 0, r = nums.size() - 1;
        int res = -1;//因为无重复值，此处定义变量可删除
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if(nums[mid] == target) {
                res = mid;
                return res;
            };
            //下面要分左半区间或右半区间是否有序研究
            if(nums[l] < nums[mid]){
                //左半有序，并考虑nums[mid]与target的大小关系
                //target位置有三种情况，其中在左半区间内只有一种
                if(target >= nums[l] && nums[mid] > target) r = mid - 1;
                else l = mid + 1;
            }
            else{
                //依然看target的位置情况，其中在右半区只有一种
                if(target > nums[mid] && target <= nums[r]) l = mid + 1;
                else r = mid - 1;
            }
        }
        return res;
    }
};
int main(){
    BinarySearchVariants bs;
    vector<int> nums = {1, 2, 2, 2, 3, 4, 5, 7, 9};
    int target = 2;

    cout << "原始数组: ";
    for (int x : nums) cout << x << " ";
    cout << "\n目标值 target = " << target << "\n\n";

    // 1.左边界
    int leftPos = bs.leftBound(nums, target);
    cout << "1.左边界(第一个等于" << target << "): " << leftPos << endl;

    // 2.右边界
    int rightPos = bs.rightBound(nums, target);
    cout << "2.右边界(最后一个等于" << target << "): " << rightPos << endl;

    // 3.出现次数
    int cnt = bs.countTarget(nums, target);
    cout << "3.目标出现总次数: " << cnt << endl;

    // 4.插入位置
    int insertPos = bs.insertIndex(nums, 6);
    cout << "4.数字6插入位置: " << insertPos << endl;

    // 5.第一个大于target
    int fg = bs.firstGreater(nums, target);
    cout << "5.第一个大于" << target << "的下标: " << fg << endl;

    // 6.最后一个小于target
    int fl = bs.lastLess(nums, target);
    cout << "6.最后一个小于" << target << "的下标: " << fl << "\n\n";

    // 旋转数组测试
    vector<int> rotateArr = {4, 5, 6, 7, 0, 1, 2};
    cout << "旋转数组: ";
    for (int x : rotateArr) cout << x << " ";
    cout << endl;
    cout << "旋转数组最小值: " << bs.MinRotate(rotateArr) << endl;
    cout << "在旋转数组查找元素0下标: " << bs.searchRotate(rotateArr, 0) << endl;
    cout << "在旋转数组查找元素9下标: " << bs.searchRotate(rotateArr, 9) << endl;

    return 0;
}