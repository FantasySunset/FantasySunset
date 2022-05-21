#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<deque>
//#include"FIFO.h"
using namespace std;
#define Capacity 3
class Page {
public:
    int number;//ҳ��
    int modefiy;
    int exist;//�Ƿ�������ڴ�
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
    //��ǰҳ��
    int exchange;//��������
};

void exchangePageTable(PageTableElement& newELement, int number, vector<PageTableElement>& pageTable) {
    int oldNumber = 0;
    for (vector<PageTableElement>::iterator it = pageTable.begin(); it != pageTable.end(); it++) {
        if (it->getNumber() == number) {
            oldNumber = it->getNumber();
            it->swap(newELement);
            it->setExchange(oldNumber);
            break;
        }
    }
}
void insertPageTable(Page& p, vector<PageTableElement>& pageTable, int& sum, deque<int>& log) {
    PageTableElement newElement(p);
    int judge = 0;//��־λ====�ж��Ƿ����
    for (int i = 0; i < pageTable.size(); i++) {
        if (pageTable[i].getNumber() == newElement.getNumber())
        {
            cout << "pageTable[i]=" << pageTable[i].getNumber();
            cout << "   newElement=" << newElement.getNumber()<<endl;
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
            //pageTable.resize(Capacity);
            // cout << "wdnmd1" << endl;
             //cout << log.front() << endl;//!!!!!!�޷����У�������
            exchangePageTable(newElement, log.front(), pageTable);
            log.pop_front();
            log.push_back(newElement.getNumber());
        }
        newElement.setExist(1);
    }
}

void PrintPageArry(vector<Page> N) {
    for (int i = 0; i < N.size(); i++) {
        cout << "ҳ�ţ�" << N[i].getNumber();
        cout << "   �Ƿ����ҳ���ڣ�" << N[i].getExist() << "  ";
        cout << endl;
    }
}
void PrintPageTable(vector<PageTableElement> pageTable) {
    for (int i = 0;i<pageTable.size(); i++) {
        cout << "ҳ�ţ�" << pageTable[i].getNumber();
        cout << "   ����ҳ��ţ�" << pageTable[i].getExchange() << "  ";
        cout << endl;
    }
}
void PrintDeque(deque<int> log) {

}
void FIFO(vector<int> m_arry) {
    int sum = 0;//ȱҳ����
    vector<Page> arry;
    for (int i = 0; i < m_arry.size(); i++) {
        Page newPage(m_arry[i]);
        arry.push_back(newPage);
    }
    deque<int> log;//��¼�Ƚ��ȳ���ҳ�ţ�ÿ����log.front�û�
    vector<PageTableElement> pageTable;
    for (int i = 0; i < 10; i++) {
        insertPageTable(arry[i], pageTable, sum, log);
        PrintPageTable(pageTable);
        PrintDeque(log);
        cout << "------------------------------------------------------------" << endl;
    }
    cout << sum;

}
void PrintArry(vector<int> arry) {
    for (vector<int>::iterator it = arry.begin();it!=arry.end(); it++) {
        cout<< *it<<"  ";
    }
    cout << endl;
}
int main() {
    srand((int)time(NULL));
    vector<int> arry;
    for (int i = 0; i < 10; i++) {
        arry.push_back(rand()%10);
    }
    PrintArry(arry);
    FIFO(arry);
    //LRU(arry);
}