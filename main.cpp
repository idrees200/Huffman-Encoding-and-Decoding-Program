#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

class heap {
public:
    class node {
    public:
        char data;
        int frequency;
        vector<int> indices;
        int asci;
        int* binary;
        node* left;
        node* right;

        node() {
            binary = new int[8];
            frequency = 0;
            left = nullptr;
            right = nullptr;
        }

        node(int f, char a) {
            data = a;
            frequency = f;
            binary = new int[8];
            left = nullptr;
            right = nullptr;
        }

        node(int f) {
            frequency = f;
            left = nullptr;
            right = nullptr;
        }

        void calcasci() {
            asci = int(data);
        }

        void calcbinary() {
            int mod = 0;
            int div = asci;
            int c = 0;
            while (div != 0) {
                mod = div % 2;
                binary[c] = mod;
                c++;
                div = div / 2;
            }
            for (int i = 0; i < 8; i++) {
                if (binary[i] != 0 && binary[i] != 1) {
                    binary[i] = 0;
                }
            }
        }
    };

    vector<node*> arr;
    int cs;

    heap() {
        cs = 0;
    }

    int paren(int i) {
        return i / 2;
    }

    int lef(int i) {
        return (2 * i);
    }

    int rig(int i) {
        return (2 * i) + 1;
    }

    void insert() {
        ifstream u("input_huff.txt");
        string text;
        getline(u, text);
        ofstream o("textlen.txt");
        o << text.length();
        int len = text.length();

        for (int i = 0; i < len; i++) {
            bool b = false;
            for (int a = 0; a < arr.size(); a++) {
                if (arr[a]->data == text[i]) {
                    arr[a]->frequency++;
                    arr[a]->indices.push_back(i);
                    b = true;
                }
            }
            if (!b) {
                insertKey(1, text[i], i);
            }
        }
        buildheap();
    }

    void printf1() {
        ofstream o("encoded.txt");
        for (int i = 0; i < arr.size(); i++) {
            for (int j = 0; j < 8; j++)
                o << arr[i]->binary[j];
        }
    }

    void huffman_tree() {
        this->buildheap();
        node* left, * right, * top = new node();
        while (cs > 0) {
            left = heapmin();
            right = heapmin();
            if (left && right) {
                top = new node(left->frequency + right->frequency, '!');
                top->left = left;
                top->right = right;
                arr.push_back(top);
                this->cs++;
                this->buildheap();
            }
            else
                break;
        }
    }

    void buildheap() {
        for (int i = (cs / 2); i >= 1; i--) {
            min_heapify(i);
        }
    }

    void min_heapify(int i) {
        int left = lef(i);
        int right = rig(i);
        int smallest = i;
        if (left <= cs && arr[left]->frequency < arr[i]->frequency) {
            smallest = left;
        }
        if (right <= cs && arr[right]->frequency < arr[smallest]->frequency) {
            smallest = right;
        }
        if (smallest != i) {
            swap(arr[i], arr[smallest]);
            min_heapify(smallest);
        }
    }

    void printf2() {
        ofstream o("dd.txt");
        o << arr.size() << endl;
        for (int i = 0; i < arr.size(); i++) {
            o << arr[i]->data << endl;
            o << arr[i]->frequency << endl;
            o << arr[i]->indices.size() << endl;
            for (int j = 0; j < arr[i]->indices.size(); j++) {
                o << arr[i]->indices[j] << endl;
            }
        }
        o.close();
    }

    void printf3() {
        ifstream o("dd.txt");
        int size;
        o >> size;
        heap a;
        int news = 0;
        int p = 0;
        for (int i = 0; i < size; i++) {
            node* temp = new node();
            o >> temp->data;
            o >> temp->frequency;
            o >> news;
            for (int j = 0; j < news; j++) {
                o >> p;
                temp->indices.push_back(p);
            }
            a.arr.push_back(temp);
        }
        o.close();

        ifstream u("textlen.txt");
        int len;
        u >> len;
        char* text = new char[len];
        ofstream y("DECODEd.txt");

        for (int i = 0; i < a.arr.size(); i++) {
            for (int j = 0; j < a.arr[i]->indices.size(); j++) {
                text[a.arr[i]->indices[j]] = a.arr[i]->data;
            }
        }
        y << text;
        y.close();
    }

    node* heapmin() {
        return arr[1];
    }

    void insertKey(int k) {
        arr.resize(cs + 1);
        int i = cs;
        arr[i] = new node(k);
        cs++;
        while (i != 0 && arr[paren(i)]->frequency > arr[i]->frequency) {
            swap(arr[i], arr[paren(i)]);
            i = paren(i);
        }
    }

    void insertKey(int k, char a, int o) {
        arr.resize(cs + 1);
        int i = cs;
        arr[i] = new node(k, a);
        cs++;
        arr[i]->calcasci();
        arr[i]->calcbinary();
        arr[i]->indices.push_back(o);
        while (i != 0 && arr[paren(i)]->frequency > arr[i]->frequency) {
            swap(arr[i], arr[paren(i)]);
            i = paren(i);
        }
    }

    void print() {
        cout << "MIN HEAP : " << endl;
        for (int a = 0; a < arr.size(); a++) {
            cout << arr[a]->data << " ";
            cout << "FREQUENCY : " << arr[a]->frequency << " ";
            cout << "ASCII :" << arr[a]->asci << " ";
            cout << endl;
        }
    }
};

int main() {
    heap temp;
    temp.insert();
    temp.print();
    cout << "FILE ENCODED SUCCESSFULLY!" << endl;
    temp.printf1();
    cout << "DO YOU WANT TO DECODE THE FILE TOO?" << endl;
    cout << "PRESS 1 FOR YES & 2 FOR NO" << endl;
    int x;
    cin >> x;
    if (x == 1) {
        temp.printf2();
        temp.printf3();
        cout << "FILE DECODED SUCCESSFULLY" << endl;
    }
    return 0;
}
