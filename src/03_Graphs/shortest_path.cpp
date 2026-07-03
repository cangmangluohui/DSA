#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;
const int INF = INT_MAX / 2; // 防止加法溢出

class ShortestPath{
public:
    ShortestPath(int n) : vertexNum(n), adj(n){}//初始化列表
    void addEdge(int u, int v, int w){//w是权重
        adj[u].emplace_back(v,w);//emplace_back比push_back更高效减少拷贝
    }
    //1. Dijkstra 优先队列版 单源最短路（仅非负边权）
    vector<int> dijkstra(int start) const {
        vector<int> dist(vertexNum, INF);
        dist[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        heap.emplace(0, start);//注意这里第一个是距离，第二个才是节点编号
        while (!heap.empty())
        {
            auto [d, u] = heap.top();
            heap.pop();
            if(d > dist[u]) continue; //dist[u]从起点到节点u的距离
            for(auto [v, w] : adj[u]){
                if(dist[v] > dist[u] + w){//说明有更短路径
                    dist[v] = dist[u] + w;
                    heap.emplace(dist[v], v);
                }
            }
        }
        return dist;
    }
    //2. Bellman-Ford 朴素单源（支持负权，返回true=存在负环）
    bool bellmanFord(int start, vector<int>& dist) const {
        fill(dist.begin(), dist.end(), INF);
        dist[start] = 0;//初始点距离设为0
        for(int i = 1; i <= vertexNum - 1; ++i){//最多v - 1轮次
            bool update = false;//记录该轮是否更新数据
            for(int u = 0; u < vertexNum; ++u){
                for(auto [v, w] : adj[u]){
                    if(dist[u] != INF && dist[v] > dist[u] + w){
                        dist[v] = dist[u] + w;
                        update = true;
                    }
                }
            }
            if(!update) break;
        }
        //检测负环,可认为这是第n轮检测
        for(int u = 0; u < vertexNum; ++u){
            for(auto [v,w] : adj[u]){
                if(dist[u] != INF && dist[v] > dist[u] + w){
                    return true;
                }
            }
        }
        return false;//不存在负环
    }
    //3. SPFA 队列优化Bellman-Ford（负权首选，判负环）
    bool spfa(int start, vector<int>& dist) const{
        fill(dist.begin(), dist.end(), INF);
        dist[start] = 0;
        vector<bool> inQueue(vertexNum, false);//初始都不入队列
        vector<int> cnt(vertexNum, 0);//该点遍历次数
        queue<int> q;

        q.push(start);
        inQueue[start] = true;
        cnt[start] = 1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            inQueue[u] = false;//弹出后即转换成false，入队列为true
            for(auto [v, w] : adj[u]){
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    if(!inQueue[v]){
                        q.push(v);
                        inQueue[v] = true;
                        cnt[v]++;//该节点遍历次数
                        if(cnt[v] > vertexNum) return true;
                    }
                }
            }
        }
        return false;
    }
    //4. Floyd 多源最短路
    vector<vector<int>> floyd() const {
        vector<vector<int>> dist(vertexNum, vector<int>(vertexNum, INF));
        for(int i = 0; i < vertexNum; ++i) dist[i][i] = 0;
        for(int u = 0; u < vertexNum; ++u){
            for(auto [v, w] : adj[u]){
                dist[u][v] = w;
            }
        }
        //三重循环更新距离
        for(int k = 0; k < vertexNum; ++k){//k是中间点
            for(int i = 0; i < vertexNum; ++i){
                for(int j = 0; j < vertexNum; ++j){
                    if(dist[i][k] != INF && dist[k][j] != INF){
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        return dist;
    }
    //打印单源最短
    void printSingleSource(const vector<int>& res, int start) const {
        cout << "起点 " << start << " 到各顶点最短距离：" << endl;
        for (int i = 0; i < vertexNum; ++i) {
            if (res[i] >= INF)
                cout << i << ":不可达 ";
            else
                cout << i << ":" << res[i] << " ";
        }
        cout << "\n" << endl;
    }
    //打印多源
    void printFloydMatrix(const vector<vector<int>>& mat) const {
        cout << "Floyd 任意两点最短路矩阵" << endl;
        for (int i = 0; i < vertexNum; ++i) {
            for (int j = 0; j < vertexNum; ++j) {
                if (mat[i][j] >= INF) cout << "∞" << " ";
                else cout << mat[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
private:
    int vertexNum;
    vector<vector<pair<int,int>>> adj;//邻接表,第二个int表示权重,这里可认为是距离
};
int main(){
    cout << "1.无负环图"  << endl;
    ShortestPath graph(4);
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 7);
    graph.addEdge(2, 3, 3);
    int startNode = 0;

    //1.Dijkstra
    cout << "Dijkstra算法" << endl;
    vector<int> disDij = graph.dijkstra(startNode);
    graph.printSingleSource(disDij, startNode);

    //2.Bellman-Ford
    cout << "Bellman-Ford算法" << endl;
    vector<int> disBell(4);
    bool haveRings1 = graph.bellmanFord(startNode, disBell);
    if(haveRings1) cout << "图存在负环，无合法最短路" << endl;
    else graph.printSingleSource(disBell, startNode);//需要判断是否有负环

    //3.SPFA
    cout << "SPFA算法" << endl;
    vector<int> disSpfa(4);
    bool haveRings2 = graph.spfa(startNode, disSpfa);
    if(haveRings2) cout << "图存在负环，无合法最短路" << endl;
    else graph.printSingleSource(disSpfa, startNode);

    //4.Floyd 多源
    cout << "Floyd算法" << endl;
    vector<vector<int>> floydMat = graph.floyd();
    graph.printFloydMatrix(floydMat);

    //增加负环测试
    cout << "2：带负环图（验证负环检测）" << endl;
    ShortestPath negGraph(3);
    // 构造负环：0→1(-1), 1→2(-1), 2→0(-1) 
    negGraph.addEdge(0, 1, -1);
    negGraph.addEdge(1, 2, -1);
    negGraph.addEdge(2, 0, -1);
    vector<int> disNeg(3);

    cout << "Bellman-Ford检测负环：";
    bool bfNegCycle = negGraph.bellmanFord(0, disNeg);
    cout << (bfNegCycle ? "发现负环" : "无负环") << endl;

    cout << "SPFA检测负环：";
    bool spfaNegCycle = negGraph.spfa(0, disNeg);
    cout << (spfaNegCycle ? "发现负环" : "无负环") << endl;
    return 0;
}