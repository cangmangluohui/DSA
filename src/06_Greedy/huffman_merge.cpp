#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

//霍夫曼树节点
struct HuffNode{
    char ch;
    int count;//字符出现频次
    HuffNode* left;
    HuffNode* right;
    HuffNode(char c = '\0', int cnt) : ch(c), count(cnt), left(nullptr), right(nullptr) {}
};

class HuffmanCoding{
public:
    HuffmanCoding():root(nullptr) {}
    ~HuffmanCoding(){//必然产生新节点，需要析构
        destoryTree(root);
    }
    //构建霍夫曼树：用字符-频次表的输入构造树,然后再转换成字符-字符串编码表
    void buildTree(const unordered_map<char, int>& freq){
        //priority_queue<元素类型, 底层容器, 比较器类型> 变量名(比较器实例);小根堆
        priority_queue<HuffNode*,
        vector<HuffNode*>,
        bool (*)(HuffNode*, HuffNode*)> 
        minHeap([](HuffNode* a, HuffNode* b) {return a -> count > b -> count;});
        
        //1. 所有叶子节点入堆
        for(auto& p : freq){
            minHeap.push(new HuffNode(p.first, p.second));
        }
        //只有一种字符时特殊处理
        if(minHeap.size() == 1){
            root = minHeap.top();
            minHeap.pop();
            codeMap[root -> ch] = "0";//键值类型string,故需要打""
            return;
        }

        //2. 贪心合并最小两个节点
        while (minHeap.size() > 1)
        {
            //新建两节点，作为子节点（左右节点）
            HuffNode* left = minHeap.top(); minHeap.pop();
            HuffNode* right = minHeap.top(); minHeap.pop();
            //新建父节点无对应字符，键值为子节点值之和
            HuffNode* parent = new HuffNode('\0', left -> count + right -> count);
            parent -> left = left;
            parent -> right = right;
            minHeap.push(parent);//已完成构建，把该节点添加到树中
        }
        root = minHeap.top();
        minHeap.pop();
        //3. 遍历树生成编码
        codeMap.clear();//防多次使用
        generateCode( root, "");
    }

    //打印所有字符对应编码
    void printAllCode() const{
        cout << "霍夫曼编码表" << endl;
        for(auto& p : codeMap){
            cout << "字符：" << p.first << " 编码：" << p.second << endl;
        }
    }

    //获取单字符对应编码
    string getCode(char c) const{
        auto it = codeMap.find(c);
        if(it == codeMap.end()) return "";
        else return it -> second;
    }

    //得到最小带权路径长度
    int getWPL() const
    {
        return calcWPL(root);
    }

private:
    HuffNode* root;//根节点
    unordered_map<char,string> codeMap;//字符-频次表要转化成字符-字符串（编码）表,有默认构造函数

    //递归释放树内存
    void destoryTree(HuffNode* node){
        if(!node) return;
        destoryTree(node -> left);
        destoryTree(node -> right);
        delete node;
    }

    //递归遍历树生成编码，频次对应字符对应的字符串编码存储在codeMap里
    void generateCode(HuffNode* node, string curCode){
        if(!node) return;
        if(!node -> left && !node -> right){//说明是叶子节点
            codeMap[node -> ch] = curCode;
            return;//到叶子节点后该分支结束，必须返回return
        }
        generateCode(node -> left, curCode + "0");
        generateCode(node -> right, curCode + "1");//字符串拼接用双引号
    }

    //计算最小带权路径长度,私有函数
    int calcWPL(HuffNode* node, int depth = 0) const{
        if(!node) return 0;//注意根节点深度为0
        //带权路径长度：频次*树深度
        if(!node -> left && !node -> right) return node -> count * depth;
        return calcWPL(node -> left, depth + 1) + calcWPL(node -> right, depth + 1);
    }

};
int main(){
    unordered_map<char, int> freq = {
        {'a', 5},
        {'b', 9},
        {'c', 12},
        {'d', 13},
        {'e', 16},
        {'f', 45}
    };
    HuffmanCoding huff;
    huff.buildTree(freq);
    huff.printAllCode();
    cout << "\n最小带权路径长度WPL= " << huff.getWPL() << endl;

    //测试单独查询某个字符编码
    cout << "\n字符 f 的编码：" << huff.getCode('f') << endl;
    return 0; 
}