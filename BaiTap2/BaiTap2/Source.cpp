////////////////#include <iostream>
////////////////
////////////////using namespace std;
////////////////
////////////////double median(double x[], int n) {
////////////////	if (n % 2 != 0) {
////////////////		return x[(n - 1) / 2];
////////////////	}
////////////////	return (x[(n-2)/2]+x[n/2])/2;
////////////////}
////////////////
////////////////void sort(double x[], int n) {
////////////////	int i, j, min_index;
////////////////	for (i = 0; i < n - 1; i++)
////////////////	{
////////////////		min_index = i;
////////////////		for (j = i + 1; j < n; j++)
////////////////		{
////////////////			if (x[j] < x[min_index]) {
////////////////				min_index = j;						
////////////////			}
////////////////		}
////////////////		swap(x[min_index], x[i]);
////////////////	}
////////////////}
////////////////
////////////////void swap(double& a, double& b) {
////////////////	double temp = a;
////////////////	a = b;
////////////////	b = temp;
////////////////}
////////////////
////////////////int main() {
////////////////	double x[] = {1,5,7,3,4,1,3.5,0.5,1.9};
////////////////	sort(x,9);
////////////////	for (int i = 0; i < 9; i++)
////////////////	{
////////////////		cout << x[i] << " ";
////////////////	}
////////////////	
////////////////	double rs = median(x, 9);
////////////////	cout<< endl << rs;
////////////////	return 0;
////////////////}
//////////////
//////////////#include <iostream>
//////////////
//////////////using namespace std;
//////////////
//////////////void sort(double arr[], int n) {
//////////////    for (int i = 0; i < n - 1; i++) {
//////////////        for (int j = i + 1; j < n; j++) {
//////////////            if (arr[i] > arr[j]) {
//////////////                double temp = arr[i];
//////////////                arr[i] = arr[j];
//////////////                arr[j] = temp;
//////////////            }
//////////////        }
//////////////    }
//////////////}
//////////////
//////////////double median(double arr[], int n) {
//////////////    sort(arr, n);
//////////////
//////////////    if (n % 2 == 0) {
//////////////        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
//////////////    }
//////////////    else {
//////////////        return arr[n / 2];
//////////////    }
//////////////}
//////////////
//////////////int main() {
//////////////	 /*double arr[] = { 5.5, 2.2, 9.9, 0.0, 4.4, 1.1, 3.3, 7.7, 6.6, 8.8 };*/
//////////////    /*double arr[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };*/
//////////////  /*  double arr[] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6 };*/
//////////////     double arr[] = { 5.5, 2.2, 9.9, 0.0, 4.4, 1.1, 3.3, 7.7, 6.6, 8.8 };
//////////////    int n = sizeof(arr) / sizeof(arr[0]);
//////////////
//////////////    double median_value = median(arr, n);
//////////////
//////////////    cout << "Median: " << median_value << endl;
//////////////
//////////////    return 0;
//////////////}
////////////
////////////// C++ implementation of the approach
////////////#include <iostream>
////////////using namespace std;
////////////
////////////// Initialize the matrix with 0
////////////int maxtrix[1001][1001] = { 0 };
////////////
////////////void initialize()
////////////{
////////////
////////////	// 0C0 = 1
////////////	maxtrix[0][0] = 1;
////////////	for (int i = 1; i < 1001; i++) {
////////////		// Set every nCr = 1 where r = 0
////////////		maxtrix[i][0] = 1;
////////////		for (int j = 1; j < i + 1; j++) {
////////////
////////////			// Value for the current cell of Pascal's triangle
////////////			maxtrix[i][j] = (maxtrix[i - 1][j - 1] + maxtrix[i - 1][j]);
////////////		}
////////////	}
////////////}
////////////
////////////// Function to return the value of nCr
////////////int nCr(int n, int r)
////////////{
////////////	// Return nCr
////////////	return maxtrix[n][r];
////////////}
////////////
////////////// Driver code
////////////int main()
////////////{
////////////	// Build the Pascal's triangle
////////////	initialize();
////////////	int n = 8;
////////////	int r = 3;
////////////	cout << nCr(n, r);
////////////}
////////////
////////////// This code is contributed by ihritik
////////////
////////#include <iostream>
////////using namespace std;
////////
////////int countDigits(char arr[]) {
////////    int count = 0;
////////    int i = 0;
////////
////////    // Đếm số lượng chữ số khác 0 ở đầu chuỗi
////////    while (arr[i] == '0') {
////////        i++;
////////    }
////////
////////    // Duyệt từ chữ số đầu tiên khác 0 đến ký tự kết thúc chuỗi
////////    while (arr[i] != '\0') {
////////        if (arr[i] >= '1' && arr[i] <= '9') {
////////            count++;
////////        }
////////        i++;
////////    }
////////
////////    return count;
////////}
////////
////////int main() {
////////    char arr[] = "003456789";
////////    int result = countDigits(arr);
////////    cout << "Number of digits: " << result << endl;
////////
////////    return 0;
////////}
////////
////////
//////////#include <iostream>
//////////
//////////using namespace std;
//////////
//////////int count_digits(char str[]) {
//////////    int count = 0;
//////////    int i = 0;
//////////    while (str[i] != '\0') {
//////////        if (str[i] >= '1' && str[i] <= '9') {
//////////            count++;
//////////            while (str[i] >= '0' && str[i] <= '9') {
//////////                i++;
//////////            }
//////////        }
//////////        else {
//////////            i++;
//////////        }
//////////    }
//////////    return count;
//////////}
//////////
//////////int main() {
//////////    char str[] = "003456789";
//////////    int count = count_digits(str);
//////////    std::cout << count << endl; // output: 7
//////////
//////////    return 0;
//////////}
//////#include <iostream>
//////using namespace std;
//////
//////int countDigits(char arr[]) {
//////    int count = 0;
//////    int i = 0;
//////
//////    // Duyệt từ đầu đến cuối chuỗi
//////    while (arr[i] != '\0') {
//////        // Nếu là chữ số khác 0 và ở vị trí đầu tiên hoặc đã vượt qua các ký tự 0 ở đầu chuỗi
//////        if (arr[i] >= '1' && arr[i] <= '9' && (i == 0 || arr[i - 1] == '0')) {
//////            count++;
//////        }
//////        i++;
//////    }
//////
//////    return count;
//////}
//////
//////int main() {
//////    char arr[] = "003456789";
//////    int result = countDigits(arr);
//////    cout << "Number of digits: " << result << endl;
//////
//////    return 0;
//////}
////#include <iostream>
////using namespace std;
////
////int countDigits(char arr[]) {
////    int count = 0;
////    int i = 0;
////    
////    if (strlen(arr) > 100) {
////        throw exception("Vuot qua 100 chu so!");
////    }
////
////    // Đếm số lượng chữ số khác 0 ở đầu chuỗi
////    while (arr[i] == '0') {
////        i++;
////    }
////
////    // Duyệt từ chữ số đầu tiên khác 0 đến ký tự kết thúc chuỗi
////    while (arr[i] != '\0') {
////        if (arr[i] >= '1' && arr[i] <= '9') {
////            count++;
////        }
////        i++;
////    }
////
////    return count;
////}
//
////int main() {
////    char arr[] = "003454532540956757567590000556789";
////    int result = countDigits(arr);
////    cout << "Number of digits: " << result << endl;
////
////    return 0;
////}
//#include <iostream>
//using namespace std;
//
//bool isDigit(char c) {
//    return (c >= '0' && c <= '9');
//}
//
//string addCommas(char arr[]) {
//    int n = strlen(arr);
//    string result = "";
//
//    for (int i = 0; i < strlen(arr); i++) {
//        if (isDigit(arr[i])) {
//            throw exception("Khong phai la so!");
//        }
//    }
//
//    if (strlen(arr) > 100) {
//        throw exception("Vuot qua 100 chu so!");
//    }
//
//    int k = 0;
//    while (arr[k] == '0') {
//        k++;
//    }
//
//    if (k == strlen(arr)) return "0";
//
//    int count = 0;
//    for (int i = n - 1; i >= k; i--) {
//        result = arr[i] + result;
//        count++;
//
//        if (count % 3 == 0 && i > 0) {
//            result = "," + result;
//        }
//    }
//
//    return result;
//}
//
//int main() {
//    char arr[] = "003456789";
//    string result = addCommas(arr);
//    std::cout << result << endl;
//
//    return 0;
//}

#include <iostream>
#include <string>
#define M_PI 3.14159265358979323846
using namespace std;

struct Complex {
    double real;
    double imaginary;
};

//Liên hợp
Complex conjugate(Complex c1) {
    Complex result;
    result.real = c1.real;
    result.imaginary = -c1.imaginary;
    return result;
}

//Nghịch đảo số phức
Complex reciprocal(Complex c) {
    Complex result;
    double denominator = c.real * c.real + c.imaginary * c.imaginary;
    result.real = c.real / denominator;
    result.imaginary = -c.imaginary / denominator;
    return result;
}

//Cộng
Complex add(Complex c1, Complex c2) {
    Complex result;
    result.real = c1.real + c2.real;
    result.imaginary = c1.imaginary + c2.imaginary;
    return result;
}

//Trừ
Complex subtract(Complex c1, Complex c2) {
    Complex result;
    result.real = c1.real - c2.real;
    result.imaginary = c1.imaginary - c2.imaginary;
    return result;
}

//Nhân
Complex multiply(Complex c1, Complex c2) {
    Complex result;
    result.real = c1.real * c2.real - c1.imaginary * c2.imaginary;
    result.imaginary = c1.real * c2.imaginary + c1.imaginary * c2.real;
    return result;
}

//Chia
Complex divide(Complex c1, Complex c2) {
    Complex result;
    double denominator = c2.real * c2.real + c2.imaginary * c2.imaginary;
    result.real = (c1.real * c2.real + c1.imaginary * c2.imaginary) / denominator;
    result.imaginary = (c1.imaginary * c2.real - c1.real * c2.imaginary) / denominator;
    return result;
}


// Tính module của số phức
double modulus(Complex c) {
    return sqrt(c.real * c.real + c.imaginary * c.imaginary);
}

// Tính argument của số phức
double argument(Complex c) {
    if (c.real == 0 && c.imaginary == 0) {
        // Số phức không có argument
        return 0;
    }
    else if (c.real == 0) {
        if (c.imaginary > 0) {
            // Số phức nằm trên trục ảo dương
            return  M_PI/ 2;
        }
        else {
            // Số phức nằm trên trục ảo âm
            return -M_PI / 2;
        }
    }
    else {
        double arg = atan(c.imaginary / c.real);
        if (c.real < 0 && c.imaginary >= 0) {
            // Số phức nằm trong góc phần tư thứ hai
            arg += M_PI;
        }
        else if (c.real < 0 && c.imaginary < 0) {
            // Số phức nằm trong góc phần tư thứ ba
            arg -= M_PI;
        }
        return arg;
    }
}

// Lấy phần thực
double real(Complex c) {
    return c.real;
}

// Lấy phần ảo
double imaginary(Complex c) {
    return c.imaginary;
}

// Lấy căn bậc 2
Complex squareRoot(Complex c) {
    double mod = sqrt(c.real * c.real + c.imaginary * c.imaginary);
    double arg = argument(c) / 2;
    Complex result;
    result.real = sqrt(mod) * cos(arg);
    result.imaginary = sqrt(mod) * sin(arg);
    return result;
}


//Xuất
void print(Complex c) {
    if (c.imaginary >= 0) {
        cout << c.real << " + " << c.imaginary << "i" << endl;
    }
    else {
        cout << c.real << " - " << -c.imaginary << "i" << endl;
    }
}

int main() {

    //Thử giải phương trình 3x^2 + 2x + 5
    cout << "Chuong trinh giai phuong trinh bac 2 ax^2 + bx + c = 0 (co nghiem phuc):" << endl;
    cout << "Nhap a: ";
    int a1 = 0;
    cin >> a1;
    cout << "Nhap b: ";
    int b1 = 0;
    cin >> b1;
    cout << "Nhap c: ";
    int c1 = 0;
    cin >> c1;

    //Bieu dien a,b,c dang so phuc
    Complex a = { a1, 0 };
    Complex b = { b1, 0 };
    Complex c = { c1, 0 };
    //Cac tham so
    Complex d = { 4, 0 };  //so 4
    Complex e = { -1, 0 }; //so -1
    Complex f = { 2, 0 };  //so 2
    Complex delta = squareRoot(subtract(multiply(b, b), multiply(d, multiply(a, c))));

    Complex x1 = divide(add(multiply(e,b),delta),multiply(f,a));
    Complex x2 = divide(subtract(multiply(e, b), delta), multiply(f, a));

    string str1 = "";
    if (x1.imaginary != 0) {
        str1 += " + " +  to_string(x1.imaginary) + "i";
    }

    string str2 = "";
    if (x2.imaginary != 0) {
        str2 += " + " + to_string(x2.imaginary) + "i";
    }
    cout << "Phuong trinh " << a.real << "x^2 + " << b.real << "x + " << c.real << " = 0 co hai nghiem la:" << endl;
    cout << "x1 = " << x1.real << str1 << endl;
    cout << "x2 = " << x2.real << str2 << endl;

    return 0;
}