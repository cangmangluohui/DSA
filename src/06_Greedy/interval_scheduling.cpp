#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//区间结构体
struct Interval
{
    int start;
    int end;
    Interval(int s = 0, int e = 0) : start(s), end(e) {}
};

class IntervalScheduling {
public:
    IntervalScheduling() = default;//空调度器
    //添加活动区间起始和结尾
    void addInterval(int s, int e){
        if(s >= e) return;//非法区间删除
        intervals.emplace_back(s, e);
    }
    //贪心求解最大不重叠区间数量，同时返回选中区间集合
    pair<int, vector<Interval>> selectMaxActivities() const {
        if(intervals.empty()){
            return {0, {}};//空，第一个是数量，空时为0
        }
        //临时数组拷贝一份排序，不修改原数据
        vector<Interval> temp = intervals;
        //贪心核心：按结束时间升序排序
        //Lambda式子常用于自定义排序规则
        sort(temp.begin(), temp.end(), [](const Interval& a, const Interval& b) {
            return a.end < b.end;
        });
        vector<Interval> selected;
        //先选结束最早的第一个
        selected.push_back(temp[0]);
        int lastEnd = temp[0].end;
        for (size_t i = 1; i < temp.size(); ++i) {
            int curStart = temp[i].start;
            int curEnd = temp[i].end;
            // 当前区间起点 >= 上一个终点，不冲突，可以选
            if (curStart >= lastEnd) {
                selected.push_back(temp[i]);
                lastEnd = curEnd;//更新lastEnd
            }
        }
        return {selected.size(), selected};
    }
    //清空所有区间，仅在需要多组区间调度时需要
    void clear() {
        intervals.clear();
    }
    //打印所有原始区间
    void printAllIntervals() const {
        cout << "所有区间：" << endl;
        for (const auto& it : intervals) {
            cout << "[" << it.start << "," << it.end << "] ";
        }
        cout << "\n";
    }

    //打印选中结果
    void printResult(const pair<int, vector<Interval>>& res) const {
        int cnt = res.first;
        const auto& sel = res.second;
        cout << "\n最多可选择活动数量：" << cnt << endl;
        cout << "选中区间：";
        for (const auto& it : sel) {
            cout << "[" << it.start << "," << it.end << "] ";
        }
        cout << "\n";
    }
private:
    vector<Interval> intervals;//初始区间集合
};
int main() {
    IntervalScheduling scheduler;

    //插入测试区间
    scheduler.addInterval(1, 3);
    scheduler.addInterval(2, 5);
    scheduler.addInterval(4, 7);
    scheduler.addInterval(6, 8);
    scheduler.addInterval(5, 9);
    scheduler.addInterval(7, 10);

    scheduler.printAllIntervals();

    auto ans = scheduler.selectMaxActivities();
    scheduler.printResult(ans);
    return 0;
}