#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class TopologicalSort{
public:
    // 构造：初始化顶点数量
    TopologicalSort(int n){
        vertexNum = n;
        AdjList.resize(n);//n个空vector
        inDegree.resize(n);//n个0
    }
    // 添加有向边 u -> v
    void addEdgeDirected(int u, int v){
        AdjList[u].push_back(v);
        inDegree[v]++;//v的入度加一，可简单理解为v的前置条件加1
    }
    // Kahn算法执行拓扑排序(仅针对有向无环图 (DAG))
    bool KahnSort(){
        queue<int> q;
        topoResult.clear();
        //1.先将入度为0的节点入队列
        for(int i = 0; i < vertexNum; ++i){
            if(inDegree[i] == 0){
                q.push(i);
            }
        }
        //2.循环处理队列
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            topoResult.push_back(cur);
            //遍历当前节点的后继节点
            for(int neighbor : AdjList[cur]){
                inDegree[neighbor]--;
                if(inDegree[neighbor] == 0){
                    q.push(neighbor);
                }
            }
        }
        //3.判断是否有环，有环无解
        if(topoResult.size() != vertexNum){
            return false;
        }
        return true;
    }
    // 打印拓扑排序结果
    void printResult(){
        cout << "拓扑排序序列：";
        for (int node : topoResult) {
            cout << node << " ";
        }
        cout << endl;
    }
private:
    int vertexNum;
    vector<vector<int>> AdjList;//邻接表
    vector<int> inDegree;//每个节点入度数组
    vector<int> topoResult;//存拓扑排序结果
};
int main(){
     // 共5个顶点：0,1,2,3,4
    TopologicalSort graph(5);
    // 构建有向边
    graph.addEdgeDirected(0, 1);
    graph.addEdgeDirected(0, 2);
    graph.addEdgeDirected(1, 3);
    graph.addEdgeDirected(2, 3);
    graph.addEdgeDirected(3, 4);

    bool ok = graph.KahnSort();
    if (ok) {
        graph.printResult();
    } else {
        cout << "图存在环路，无法进行拓扑排序" << endl;
    }
    return 0;
}