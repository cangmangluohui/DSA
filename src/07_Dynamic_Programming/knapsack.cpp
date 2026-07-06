#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Knapsack{
public:
    Knapsack(const vector<int>& w, const vector<int>& v,int cap):
    weight(w), value(v), capacity(cap), itemNum(w.size()){
        dp.assign(itemNum + 1, vector<int>(capacity + 1, 0));
    }
    //DP核心计算：填充二维dp表
    int calcMaxVal(){
        //i：前i件物品（1~itemNum）
        for(int i = 1; i < itemNum + 1; ++i){
            int w = weight[i - 1];
            int v = value[i - 1];
            //j：背包当前容量
            for(int j = 0; j < capacity + 1; ++j){
                if(j < w){
                    dp[i][j] = dp[i - 1][j];// 装不下第i件，只能继承前i-1件结果
                }
                else{
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w] + v);// 可选：不拿 / 拿第i件，取最大值
                }
            }
        }
        return dp[itemNum][capacity];
    }
    //回溯二维dp表，得到哪些物品被选中
    vector<bool> getSelectItems(){
        vector<bool> choose(itemNum, false);
        int j = capacity;
        //从后往前推
        for(int i = itemNum; i >= 1; --i){
            int w = weight[i - 1];
            int v = value[i - 1];
            if(j >= w && dp[i][j] == dp[i - 1][j - w] + v){//判断条件里是==不能用=
                choose[i - 1] = true;
                j -= w;
            }
        }
        return choose;
    }
    //打印完整结果
    void printResult(){
        int maxVal = calcMaxVal();
        cout << "最大总价值： " << maxVal << endl;
        vector<bool> sel = getSelectItems();
        cout << "被选中的物品下标（从0开始）： ";
        for(int i = 0; i < itemNum; ++i){
            if(sel[i]) cout << i << " ";
        }
    }

private:
    vector<int> weight;// 物品重量
    vector<int> value;// 物品价值
    int capacity;// 背包容量
    int itemNum;//物品总数
    vector<vector<int>> dp;//二维dp，dp[i][j]：前i个物品，容量j的最大价值
};
int main(){
    vector<int> w = {2, 3, 4, 5};
    vector<int> v = {3, 4, 5, 6};
    int cap = 8;
    Knapsack k(w, v, cap);
    k.printResult();
    return 0;
}