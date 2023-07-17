#include <iostream>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main() {
	unsigned long long n;
	printf("Nhap so nguyen khong am: ");
//	scanf("%lld", &n);
	cin>>n;
//	int co_so = 1;
//	
//	int chu_so_hang_tram = n/co_so%10;
//	printf("So da nhap: %llu", n);

	while(n/1000!=0){
		cout<<","<<n;		
		n=n/1000;

	}

//	cout<<chu_so_hang_tram;
}
