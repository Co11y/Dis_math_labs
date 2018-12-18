#include <iostream>

int factorial(int n) {
	if (n >= 1)
		return n * factorial
		(n - 1);
	else
		return 1;
}

int combination(int number, int k) {

	return factorial(number) / (factorial(k)* factorial(number - k));

}
char plus_or_minus(int j) {
	if (((j + 1) % 2) == 1)
		return '+';
	else
		return '-';
}

int main() {

	int n = 12;
	int p = n;
	for (int i = 0; i <= n; i++, p--) {
		std::cout << plus_or_minus(i) << combination(n, i) << " x^" << p << " y^" << i << std::endl;
	}
	
	system("pause");






}
