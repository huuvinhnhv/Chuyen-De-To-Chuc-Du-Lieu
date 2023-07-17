#include <iostream>
using namespace std;
struct Data {
    int value;
    int count;
    Data* next;
};
struct Bag {
private:
    Data* hashTable[1000] = {};
    int size;

public:
    //hàm khởi tạo
    Bag() {
        size = 0;
    }

    //hàm băm sử dụng thuật toán FNV
    int hash(int value) {
        unsigned int h = 2166136261;
        char* p = (char*)&value;
        for (int i = 0; i < sizeof(int); i++) {
            h = (h * 16777619) ^ p[i];
        }
        return h % 1000;
    }

    //thêm phần tử vào túi
    void add(int value) {
        int index = hash(value);
        Data* data = hashTable[index];
        while (data != NULL && data->value != value) {
            data = data->next;
        }
        if (data != NULL) {
            data->count++;
        }
        else {
            data = new Data{ value, 1, hashTable[index] };
            hashTable[index] = data;
            size++;
        }
    }

    //xóa 1 phần tử ra khỏi túi
    void remove(int value) {
        int index = hash(value);
        Data* data = hashTable[index];
        Data* prev = NULL;
        while (data != NULL && data->value != value) {
            prev = data;
            data = data->next;
        }
        if (data != NULL) {
            data->count--;
            if (data->count == 0) {
                if (prev == NULL) {
                    hashTable[index] = data->next;
                }
                else {
                    prev->next = data->next;
                }
                delete data;
                size--;
            }
        }
    }

    //xóa tất cả phần tử value có trong túi
    void removeAll(int value) {
        int index = hash(value);
        Data* data = hashTable[index];
        Data* prev = NULL;
        while (data != NULL) {
            if (data->value == value) {
                if (prev == NULL) {
                    hashTable[index] = data->next;
                }
                else {
                    prev->next = data->next;
                }
                Data* tmp = data;
                data = data->next;
                delete tmp;
                size--;
            }
            else {
                prev = data;
                data = data->next;
            }
        }
    }

    //đếm số lân xuất hiện của phần tử trong túi
    int count(int value) {
        int index = hash(value);
        Data* data = hashTable[index];
        while (data != NULL && data->value != value) {
            data = data->next;
        }
        if (data != NULL) {
            return data->count;
        }
        return 0;
    }

    //kiểm tra 2 túi có bắng nhau
    bool isBagsEqual(Bag& bag2) {
        if (size != bag2.size) {
            return false;
        }
        for (int i = 0; i < 1000; i++) {
            Data* data1 = hashTable[i];
            Data* data2 = bag2.hashTable[i];
            while (data1 != NULL && data2 != NULL) {
                if (data1->value != data2->value || data1->count != data2->count) {
                    return false;
                }
                data1 = data1->next;
                data2 = data2->next;
            }
            if (data1 != NULL || data2 != NULL) {
                return false;
            }
        }
        return true;
    }

    //hàm thêm phần tử hỗ trợ thêm một node data vào mảng Data
    //phục vụ cho hàm bagUnion
    void add2(Data& data) {
        int index = hash(data.value);
        Data* existingData = hashTable[index];
        Data* prevData = NULL;
        while (existingData != NULL && existingData->value != data.value) {
            prevData = existingData;
            existingData = existingData->next;
        }
        if (existingData != NULL) {
            existingData->count += data.count;
        }
        else {
            Data* newData = new Data{ data.value, data.count, hashTable[index] };
            hashTable[index] = newData;
            size++;
        }
    }

    //gộp 2 túi
    Bag bagUnion(Bag& bag2) {
        Bag result;
        for (int i = 0; i < 1000; i++) {
            Data* data = this->hashTable[i];
            while (data != NULL) {
                int value = data->value;
                int count = data->count;
                result.add2(*data);
                data = data->next;
            }
            data = bag2.hashTable[i];
            while (data != NULL) {
                int value = data->value;
                int count = data->count;
                result.add2(*data);
                data = data->next;
            }
        }
        return result;
    }

    //kiểm tra có là túi con
    bool isSubsetOf(Bag other) {
        if (other.size==0) return false;
        // Lặp qua các phần tử của bag
        for (int i = 0; i < 1000; i++) {
            Data* data = this->hashTable[i];
            while (data != NULL) {
                if (other.count(data->value) < data->count) {
                    return false;
                }
                data = data->next;
            }
        }
        return true;
    }

    //in ra tất cả phần tử trong data
    void display() {
        cout << "Bag content (value, count):\n";
        for (int i = 0; i < 1000; i++) {
            Data* data = hashTable[i];
            while (data != NULL) {
                cout <<"("<< data->value << ", " << data->count << ")" << " ";
                data = data->next;
            }
        }
        cout << endl;
    }
};

int main() {
    Bag bag1, bag2;

    // Thêm phần tử vào bag1
    bag1.add(1);
    bag1.add(2);
    bag1.add(2);
    bag1.add(3);
    bag1.add(3);
    bag1.add(3);
    bag1.add(4);
    bag1.add(4);
    bag1.add(4);
    bag1.add(4);

    // Thêm phần tử vào bag2
    bag2.add(2);
    bag2.add(3);
    bag2.add(3);
    bag2.add(4);
    bag2.add(4);
    bag2.add(4);
    bag2.add(4);
    bag2.add(5);
    bag2.add(5);

    cout << "Bag 1:" << endl;
    bag1.display();
    cout << "Bag 2:" << endl;
    bag2.display();

    // Kiểm tra số lần xuất hiện của phần tử trong bag1
    cout << "Dem so luong phan tu 3 trong bag1: " << bag1.count(3) << endl;
    // Gộp 2 bag lại với nhau
    Bag bagUnion = bag1.bagUnion(bag2);
    cout << "Gop bag1 va bag2:" << endl;
    bagUnion.display();

    // Kiểm tra tính bằng nhau giữa bag1 và bagUnion
    if (bag1.isBagsEqual(bagUnion)) {
        cout << "bag1 và bagUnion bang nhau." << endl;
    }
    else {
        cout << "bag1 và bagUnion khong bang nhau." << endl;
    }

    //kiểm tra bag1 có la túi con của bag union
    if (bag1.isSubsetOf(bagUnion)) {
        cout << "bag1 la tui con cua bagUnion." << endl;
    }
    else {
        cout << "bag1 khong la tui con cua bagUnion." << endl;
    }
    return 0;
}
