#include <cmath>
#include <iostream>

int main() {
	long double R;
	long double S;
	while(std::cin >> R >> S) {

	// for(
	std::cout << (long long) std::roundl(std::sqrt(R*(S+0.16)/0.067)) << std::endl;
	}
	return 0;
}
