#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
class GraphTraversal{
public:
    GraphTraversal(int n){
        vertexNum = n;
        AdjList.resize(n);
        AdjMatrix.assign(n, vector<int>(n, 0));
        visited.assign(n, false);
    }
    //添加无向边u<->v
    void addEdgeUndirected(int u, int v){
        AdjList[u].push_back(v);
        AdjList[v].push_back(u);
        AdjMatrix[u][v] = 1;
        AdjMatrix[v][u] = 1;
    }
    // 添加有向边 u -> v
    void addEdgeDirected(int u, int v){
        AdjList[u].push_back(v);
        AdjMatrix[u][v] = 1;
    }
    // DFS递归实现（深度优先）
    void dfsRec(int start){
        if(visited[start]) return;
        cout << start << " ";
        visited[start] = true;
        for(int neighbor : AdjList[start]){
            if(!visited[neighbor]){
                dfsRec(neighbor);
            }
        }
    }
    // 重置访问标记数组（遍历前必须清空标记）
    void resetVisited(){
        fill(visited.begin(), visited.end(), false);
    }
    // DFS迭代实现
    void dfsItr(int start){
        resetVisited();
        stack<int> st;
        st.push(start);
        while (!st.empty())
        {
            int cur = st.top();
            st.pop();
            if(!visited[cur]) continue;
            cout << cur << " ";
            visited[cur] = true;
            //逆序入栈，使得遍历结果与递归法一致
            for(auto it = AdjList[cur].rbegin(); it != AdjList[cur].rend(); ++it){
                int neighbor = *it;
                if(!visited[neighbor]){
                    st.push(neighbor);
                }
            } 
        }
    }
    // BFS 队列迭代版（广度优先、层序遍历）
    void bfs(int start){
        resetVisited();
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            cout << cur << " ";
            for(int neighbor : AdjList[cur]){
                if(!visited[neighbor]){
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        
    }
    // 遍历非联通图的连通分量
    void traverseAllComponent(){
        resetVisited();
        cout << "\n=== 遍历全图所有连通分量 ===" << endl;
        for(int i = 0; i < vertexNum; ++i){
            if(!visited[i]){
                cout << "连通分量起点： " << i << "DFS: ";
                dfsRec(i);
                cout << endl;
            }
        }
    }
    //打印邻接表
    void printAdjList(){
        cout << "\n===== 邻接表 =====" << endl;
        for (int i = 0; i < vertexNum; ++i) {
            cout << "顶点" << i << ": ";
            for (int v : AdjList[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
    //打印邻接矩阵
    void printAdjMatrix(){
        cout << "\n===== 邻接矩阵 =====" << endl;
        for (int i = 0; i < vertexNum; ++i) {
            for (int j = 0; j < vertexNum; ++j) {
                cout << AdjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
private:
    int vertexNum;//顶点个数
    vector<vector<int>> AdjList;//无需频繁插拔中间元素，不用list，邻接表
    vector<vector<int>> AdjMatrix;//邻接矩阵
    vector<bool> visited;//标记是否访问
};
int main(){
    GraphTraversal graph(6);
    graph.addEdgeUndirected(0, 1);
    graph.addEdgeUndirected(0, 2);
    graph.addEdgeUndirected(1, 3);
    graph.addEdgeUndirected(1, 4);
    graph.addEdgeUndirected(2, 5);
    graph.addEdgeUndirected(4, 5);

    graph.printAdjList();
    graph.printAdjMatrix();

    int startNode = 0;
    cout << "\n起点 = " << startNode << endl;
    graph.resetVisited();

    cout << "\nDFS 递归遍历：";
    graph.dfsRec(startNode);

    cout << "\nDFS 迭代遍历：";
    graph.dfsItr(startNode);

    cout << "\nBFS 层序遍历：";
    graph.bfs(startNode);
    // 测试非连通图遍历（当前图连通，只有一个分量）
    graph.traverseAllComponent();
    cout << endl;
    return 0;
}