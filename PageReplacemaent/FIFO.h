#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<deque>
using namespace std;
#define Capacity 3
class Page {
public:
    int number;//页号
    int modefiy;
    int exist;//是否存在于内存
public:
    Page() {
        this->number = -1;
        this->modefiy = -1;
        this->exist = 0;
    }
    Page(int m_number) {
        this->number = m_number;
        this->modefiy = -1;
        this->exist = 0;

    }
    int getNumber() {
        return this->number;
    }
    int getExist() {
        return this->exist;
    }
    void setExist(int N) {
        this->exist = N;
    }


};
class PageTableElement :public Page {

public:
    PageTableElement(int m_number) {
        this->number = m_number;
        this->exchange = -1;
    }
    PageTableElement(Page m_page) {
        this->number = m_page.getNumber();
        this->exchange = -1;
    }
    int getNumber() {
        return this->number;
    }
    int getExchange() {
        return this->exchange;
    }
    void setExchange(int m_exchange) {
        this->exchange = m_exchange;
    }
    void swap(PageTableElement& N) {
        this->exchange = this->number;
        this->number = N.number;
        N.setExist(1);
    }

private:
    //当前页号
    int exchange;//交换对象
};

void exchangePageTable(PageTableElement& newELement, int number, vector<PageTableElement>& pageTable) {
    int oldNumber = 0;
    for (vector<PageTableElement>::iterator it = pageTable.begin(); it != pageTable.end(); it++) {
        if (it->getNumber() == number) {
            oldNumber=it->getNumber();
            it->swap(newELement);
            it->setExchange(oldNumber);
            pageTable.resize(Capacity);
            break;
        }
    }
}
void insertPageTable(Page& p, vector<PageTableElement>& pageTable, int& sum, deque<int>& log) {
    PageTableElement newElement(p);
    int judge = 0;//标志位====判断是否存在
    for (int i = 0; i < pageTable.size(); i++) {
        if (pageTable[i].getNumber() == newElement.getNumber())
        {
            cout << "pageTable[i]=" << pageTable[i].getNumber();
            cout << "newElement=" << newElement.getNumber();
            judge = 1;
            break;
        }
    }
    if (judge == 0) {
        sum++;
        if (pageTable.size() < Capacity) {
            pageTable.push_back(newElement);
            log.push_back(newElement.getNumber());
        }
        else {
            // cout << "wdnmd1" << endl;
             //cout << log.front() << endl;//!!!!!!无法运行！！！！
            exchangePageTable(newElement, log.front(), pageTable);
        }
        newElement.setExist(1);
    }
}

void PrintPageTable_FIFO(vector<PageTableElement> pageTable) {
    for (int i = 0; i < pageTable.size(); i++) {
        cout << "页号：" << pageTable[i].getNumber();
        cout << "   交换页面号：" << pageTable[i].getExchange() << "  ";
        cout << endl;
    }
}

void FIFO(vector<int> m_arry) {
    int sum = 0;//缺页次数
    vector<Page> arry;
    for (int i = 0; i < m_arry.size(); i++) {
        Page newPage(m_arry[i]);
        arry.push_back(newPage);
    }
    deque<int> log;//记录先进先出的页号，每次与log.front置换
    vector<PageTableElement> pageTable;
    for (int i = 0; i < 10; i++) {
        insertPageTable(arry[i], pageTable, sum, log);
        PrintPageTable_FIFO(pageTable);
        cout << "------------------------------------------------------------" << endl;
    }
    cout << sum;

}

