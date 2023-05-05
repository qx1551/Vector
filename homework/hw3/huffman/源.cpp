#include <iostream>
#include <string>
#include <unordered_map>
#include "../../../vector/vectordes.h"
#include<queue>
using namespace std;

// 定义 Huffman 编码树的节点
struct HuffmanNode {
    char ch;               // 节点代表的字符
    int freq;              // 字符出现的频率
    HuffmanNode* left;     // 左子节点
    HuffmanNode* right;    // 右子节点

    HuffmanNode(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

// 定义比较器，用于优先队列的排序
struct NodeCompare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

// 统计每个字符出现的频率
unordered_map<char, int> countFrequency(const string& text) {
    unordered_map<char, int> freq;
    for (char ch : text)
        freq[ch]++;
    return freq;
}

// 构建Huffman编码树
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freq) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, NodeCompare> minHeap;

    // 把每个字符转化为Huffman节点放入堆中
    for (const auto& entry : freq) {
        HuffmanNode* node = new HuffmanNode(entry.first, entry.second);
        minHeap.push(node);
    }

    // 构建Huffman编码树，每次从堆中取出两个最小的节点组成一个新的节点，直到堆中只剩下一个节点即为根节点
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();
        int freqSum = left->freq + right->freq;
        HuffmanNode* parent = new HuffmanNode(NULL, freqSum);
        parent->left = left;
        parent->right = right;
        minHeap.push(parent);
    }

    return minHeap.top();
}

// 生成Huffman编码
void generateHuffmanCode(const HuffmanNode* root1, const string& code, unordered_map<char, string>& huffmanCode) {
    if (root1 == nullptr)
        return;
    if (root1->left == nullptr && root1->right == nullptr) { // 到达叶子节点，把编码加入到哈希表中
        huffmanCode[root1->ch] = code;
        return;
    }
    generateHuffmanCode(root1->left, code + "0", huffmanCode);  // 递归处理左子树
    generateHuffmanCode(root1->right, code + "1", huffmanCode); // 递归处理右子树
}


class Node {
public:
    char ch;
    int freq;
    Node* left, * right;

    Node(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        left = right = NULL;
    }

    // 比较运算符重载
    bool operator>(const Node& n2) const {
        return freq > n2.freq;
    }
};

// 构建Huffman编码树
Node* buildHuffmanTree(vector<char>& text) {
    // 统计字符频率
    unordered_map<char, int> freq;
    for (char& ch : text) {
        freq[ch]++;
    }

    // 将字符频率封装成结点并存入优先队列
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    for (auto& p : freq) {
        pq.push(Node(p.first, p.second));
    }

    // 合并结点
    while (pq.size() > 1) {
        Node* n1 = new Node('\0', 0);
        Node* n2 = new Node('\0', 0);
        *n1 = pq.top();
        pq.pop();
        *n2 = pq.top();
        pq.pop();
        Node* parent = new Node('\0', n1->freq + n2->freq);
        parent->left = n1;
        parent->right = n2;
        pq.push(*parent);
    }

    // 返回根结点
    return new Node('\0', 0); // TODO
}

// 生成Huffman编码表
void generateHuffmanCodeTable(Node* root, unordered_map<char, string>& codeTable, string code = "") {
    if (!root) return;
    if (root->ch != '\0') {
        codeTable[root->ch] = code;
    }
    generateHuffmanCodeTable(root->left, codeTable, code + "0");
    generateHuffmanCodeTable(root->right, codeTable, code + "1");
}


int main()
{
    string text = "I am happy to join with you today in what will go downinhistory as the greatest demonstration for freedom in the history of our nation.Five score years ago, a great American, in whose symbolic shadow we stand today, signed the Emancipation Proclamation. This momentous decree came as a great beacon light of hope to millions of Negro slaves who had been seared in the flames of withering injustice. It came as a joyous daybreak to end the long night of bad captivity.But one hundred years later, the Negro still is not free. One hundred years later, the life of the Negro is still sadly crippled by the manacles of segregation and the chains of discrimination. One hundred years later, the Negro lives on a lonely island of poverty in the midst of avast ocean of material prosperity. One hundred years later, the Negro is still languished in the corners of American society and finds himself an exile in his own land. And so we've come here today to dramatize a shameful condition.In a sense we've come to our nation's capital to cash a check. When the architects of our republic wrote the magnificent words of the Constitution and the Declaration of Independence, they were signing a promissory note to which every American was to fall heir. This note was a promise that all men, yes, black men as well as white men, would be guaranteed the unalienable Rights of Life, Libertyand the pursuit of Happiness.It is obvious today that America has defaulted on this promissory note, insofar as her citizens of color are concerned.Instead of honoring this sacred obligation, America has given the Negro people a bad check, a check which has come back marked insufficient funds.But we refuse to believe that the bank of justice is bankrupt.We refuse to believe that there are insufficient funds in the great vaults of opportunity of this nation.And so, we've come to cash this check, a check that will give us upon demand the riches of freedom and the security of justice.We have also come to this hallowed spot to remind America of the fierce urgency of Now. This is no time to engage in the luxury of cooling off or to take the tranquilizing drug of gradualism. Now is the time to make real the promises of democracy. Now is the time to rise from the dark and desolate valley of segregation to the sunlit path of racial justice. Now is the time to lift our nation from the quicksands of racial injustice to the solid rock of brotherhood. Now is the time to make justice a reality for all of God's children.It would be fatal for the nation to overlook the urgency of the moment.This sweltering summer of the Negro's legitimate discontent will not pass until there is an invigorating autumn of freedom and equality. Nineteen sixty-three is not an end, but a beginning. And those who hope that the Negro needed to blow off steam and will now be content will have a rude awakening if the nation returns to business as usual. And there will be neither rest nor tranquility in America until the Negro is granted his citizenship rights. The whirlwinds of revolt will continue to shake the foundations of our nation until the bright day of justice emerges.But there is something that I must say to my people, who stand on the warm threshold which leads into the palace of justice: In the process of gaining our rightful place, we must not be guilty of wrongful deeds. Let us not seek to satisfy our thirst for freedom by drinking from the cup of bitterness and hatred. We must forever conduct our struggle on the high plane of dignity and discipline. We must not allow our creative protest to degenerate into physical violence. Again and again, we must rise to the majestic heights of meeting physical force with soul force.The marvelous new militancy which has engulfed the Negro community must not lead us to a distrust of all white people, for many of our white brothers, as evidenced by their presence here today, have come to realize that their destiny is tied up with our destiny. And they have come to realize that their freedom is inextricably bound to our freedom.We cannot walk alone.And as we walk, we must make the pledge that we shall always march ahead.We cannot turn back.There are those who are asking the devotees of civil rights, When will you be satisfied   We can never be satisfied as long as the Negro is the victim of the unspeakable horrors of police brutality. We can never be satisfied as long as our bodies, heavy with the fatigue of travel, cannot gain lodging in the motels of the highways and the hotels of the cities. We cannot be satisfied as long as the Negro's basic mobility is from a smaller ghetto to a larger one.We can never be satisfied as long as our children are stripped of their selfhood and robbed of their dignity by signs stating for whites only. We cannot be satisfied as long as a Negro in Mississippi cannot vote and a Negro in New York believes he has nothing for which to vote.No, no, we are not satisfied, and we will not be satisfied until justice rolls down like waters, and righteousness like a mighty stream.I am not unmindful that some of you have come here out of great trials and tribulations.Some of you have come fresh from narrow jail cells.And some of you have come from areas where your quest -- quest for freedom left you battered by the storms of persecutionand staggered by the winds of police brutality.You have been the veterans of creative suffering.Continue to work with the faith that unearned suffering is redemptive.Go back to Mississippi, go back to Alabama, go back to South Carolina, go back to Georgia, go back to Louisiana, go back to the slumsand ghettos of our northern cities, knowing that somehow this situation canand will be changed.Let us not wallow in the valley of despair, I say to you today, my friends.And so even though we face the difficulties of todayand tomorrow, I still have a dream.It is a dream deeply rooted in the American dream.I have a dream that one day this nation will rise upand live out the true meaning of its creed : We hold these truths to be self - evident, that all men are created equal.I have a dream that one day on the red hills of Georgia, the sons of former slavesand the sons of former slave owners will be able to sit down together at the table of brotherhood.I have a dream that one day even the state of Mississippi, a state sweltering with the heat of injustice, sweltering with the heat of oppression, will be transformed into an oasis of freedomand justice.I have a dream that my four little children will one day live in a nation where they will not be judged by the color of their skin but by the content of their character.I have a dream today!I have a dream that one day, down in Alabama, with its vicious racists, with its governor having his lips dripping with the words of interposition and nullification --one day right there in Alabama little black boys and black girls will be able to join hands with little white boys and white girls as sisters and brothers.I have a dream today!I have a dream that one day every valley shall be exalted, and every hilland mountain shall be made low, the rough places will be made plain, and the crooked places will be made straight; and the glory of the Lord shall be revealed and all flesh shall see it together.This is our hope, and this is the faith that I go back to the South with.With this faith, we will be able to hew out of the mountain of despair a stone of hope.With this faith, we will be able to transform the jangling discords of our nation into a beautiful symphony of brotherhood. With this faith, we will be able to work together, to pray together, to struggle together, to go to jail together, to stand up for freedom together, knowing that we will be free one day.And this will be the day this will be the day when all of God's children will be able to sing with new meaning My country tis of thee, sweet land of liberty, of thee I sing.Land where my fathers died, land of the Pilgrim's pride,From every mountainside, let freedom ring!And if America is to be a great nation, this must become true.And so let freedom ring from the prodigious hilltops of New Hampshire.Let freedom ring from the mighty mountains of New York.Pennsylvania.Let freedom ring from the snow-capped Rockies of Colorado.Let freedom ring from the curvaceous slopes of California.But not only that:Let freedom ring from Stone Mountain of Georgia.Let freedom ring from Lookout Mountain of Tennessee.Let freedom ring from every hill and molehill of Mississippi.From every mountainside, let freedom ring.And when this happens, when we allow freedom ring, when we let it ring from every village and every hamlet, from every state and every city, we will be able to speed up that day when all of God's children, black men and white men, Jews and Gentiles, Protestants and Catholics, will be able to join hands and sing in the words of the old Negro spiritual:Free at last! Free at last!Thank God Almighty, we are free at last!";
    vector<char> vtext(text.begin(), text.end());

    // 构建Huffman编码树
    Node* root = buildHuffmanTree(vtext);

    // 生成Huffman编码表
    unordered_map<char, string> codeTable;
    generateHuffmanCodeTable(root, codeTable);

    // 输出Huffman编码表和每个字符出现的频率

    for (auto& p : codeTable) {
        cout << p.first << ": " << p.second << endl;
    }

    cout << "每个字符出现的频率：" << endl;
    unordered_map<char, int> freq;
    for (char& ch : vtext) {
        freq[ch]++;
    }

    for (int i = 'A'; i <= 'Z'; i++) {
        char ch = i + 'a' - 'A';
        cout << ch << ": " << freq[ch] << endl;
    }

    HuffmanNode* root1 = buildHuffmanTree(freq);                // 构建Huffman编码树
    unordered_map<char, string> huffmanCode;                   // 声明Huffman编码的哈希表
    generateHuffmanCode(root1, "", huffmanCode);                // 生成Huffman编码

    cout << "每个字符对应的Huffman编码：" << endl;
    // 输出每个字符以及它对应的Huffman编码
    for (const auto& entry : huffmanCode) {
        cout << entry.first << " : " << entry.second << endl;
    }

    return 0;
}
