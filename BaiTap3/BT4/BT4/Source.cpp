#include <iostream>
using namespace std;

struct Data {
	int value;
	int count;
};

struct Bag {
private:
	Data data[1000] = {};
	// số phần tử hiện có trong túi
	int size;
public:
	// Hàm tạo
	Bag() {
		size = 0;
	}

	// Thêm một phần tử vào túi
	void add(int value) {
		//nếu tồn tại phần tử thì tăng count lên
		for (int i = 0; i < size; i++) {
			if (data[i].value == value) {
				data[i].count++;
				return;
			}
		}
		//nếu không thì tạo data mới
		data[size].value = value;
		data[size].count = 1;
		size++;
	}

	// Xóa một phần tử khỏi túi
	void remove(int value) {
		for (int i = 0; i < size; i++) {
			//nếu tồn tại thì giảm count đi
			if (data[i].value == value) {
				data[i].count--;
				//count = 0 thì bỏ node data
				if (data[i].count == 0) {
					for (int j = i; j < size - 1; j++) {
						data[j] = data[j + 1];
					}
					size--;
				}
				return;
			}
		}
	}

	// Xóa hết một phần tử khỏi túi
	void removeAll(int value) {
		for (int i = 0; i < size; i++) {
			if (data[i].value == value) {
				for (int j = i; j < size - 1; j++) {
					data[j] = data[j + 1];
				}
				size--;
				i--;
			}
		}
	}

	// Đếm số lần xuất hiện của một phần tử trong túi
	int count(int value) {
		for (int i = 0; i < size; i++) {
			if (data[i].value == value) {
				return data[i].count;
			}
		}
		return 0;
	}

	// Kiểm tra hai túi có bằng nhau không
	bool isBagsEqual(Bag& bag2) {
		if (this->size != bag2.size) {
			return false;
		}
		for (int i = 0; i < this->size; i++) {
			if (this->count(this->data[i].value) != bag2.count(bag2.data[i].value)) {
				return false;
			}
		}
		return true;
	}

	// Kiểm tra một túi có là túi con của túi khác không
	bool isSubsetOf(Bag other) {
		for (int i = 0; i < size; i++) {
			if (count(data[i].value) > other.count(data[i].value)) {
				return false;
			}
		}
		return true;
	}



	//gộp 2 túi với nhau
	Bag bagUnion(Bag& bag2) {
		Bag result;
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->count(this->data[i].value); j++) {
				result.add(this->data[i].value);
			}
		}
		result.display();
		for (int i = 0; i < bag2.size; i++) {
			bool found = false;
			for (int j = 0; j < result.size; j++) {
				if (result.data[j].value == bag2.data[i].value) {
					result.data[j].count += bag2.data[i].count;
					found = true;
					break;
				}
			}
			if (!found) {
				result.add(bag2.data[i].value);
			}
		}
		return result;
	}

	//in các phần tử trong túi
	void display() {
		if (size == 0) {
			cout << "Bag is empty.\n";
			return;
		}
		cout << "Bag content (value, count):\n";
		for (int i = 0; i < size; i++) {
			cout << "(" << data[i].value << ", " << data[i].count << ")" << "\n";
		}
	}
};
int main() {

	Bag bag1, bag2;

	bag1.add(1);
	bag1.add(2);
	bag1.add(3);
	bag1.add(2);

	//bag1
	cout << "Bag1:\n";
	bag1.display();

	bag2.add(2);
	bag2.add(1);
	bag2.add(2);
	bag2.add(3);

	//bag2
	cout << "Bag2:\n";
	bag2.display();

	//lấy số lần xuất hiện của giá trị 2 trong bag1
	std::cout << "Number of occurrences of 2 in bag1: " << bag1.count(2) << std::endl;

	//kiểm tra 2 bang có bằng nhau
	if (bag1.isBagsEqual(bag2)) {
		std::cout << "bag1 and bag2 are equal" << std::endl;
	}
	else {
		std::cout << "bag1 and bag2 are not equal" << std::endl;
	}

	//kiểm tra có phải subset
	if (bag1.isSubsetOf(bag2)) {
		std::cout << "bag1 is a subset of bag2" << std::endl;
	}
	else {
		std::cout << "bag1 is not a subset of bag2" << std::endl;
	}
	//gộp 2 bag
	Bag bag3 = bag1.bagUnion(bag2);
	//bag2
	cout << "bagUnion bag1 and bag2:\n";
	bag3.display();

	cout << "Remove all value 2 in bagUnion:\n";
	bag3.removeAll(2);
	bag3.display();
	return 0;
}
