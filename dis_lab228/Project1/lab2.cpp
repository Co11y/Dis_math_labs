#include <iostream>
#include <conio.h>
#include <math.h>

//find real length of set
int length(char *set) {
	int i = 1;
	if (set[0] == 'm')
	{
		return 0;
	}
	while (true) {
		if (set[i] == 'm') {
			return i;
		}
		i++;
	}
}

// print on maximalki 
void printe(char * arr) {
	int size = length(arr);
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
}

// initialise array 
void initialise(char *set, int set_size) {
	for (int i = 0; i < set_size; i++) {
		set[i] = 'm';
	}
}

//check if element from set is unic
bool is_unic(char *set, char element) {
	int i = 0;
	while (true) {
		if (set[i] == 'm') {
			return true;
		}
		else if (set[i] == element) {
			return false;
		}
		i++;
	}
}

// setting and filling with elements sets
void set_set(char * set) {
	int size = 16;
	initialise(set, size);
	std::cout << " starting adding elemnts" << std::endl;
	std::cout << "your elemnt should be unic, press esc to stop" << std::endl;
	for (int i = 0; i < size;) {
		char elm;
		/*printe(set);*/
		system("cls");
		std::cout << "print here your number(print f to stop adding elements): ";
		std::cin >> elm;
		if (elm == 'f') {
			break;
		}
		else if (is_unic(set, elm)) {
			set[i] = (char)elm;
			i++;
		}
		else {
			std::cout << "type another elemnt " << std::endl;
		}
	}
}

void create_universum(char * arr, char * arr1, char * universum) {
	initialise(universum, 16);
	int i = 0;

	int k = 0;
	int size = length(arr);
	for (; i < size; i++) {
		char element = arr[i];
		if (is_unic(universum, element)) {
			universum[k] = element;
			k++;
		}
	}
	i = 0;
	size = length(arr1);
	for (; i < size; i++) {
		char element = arr1[i];
		if (is_unic(universum, element)) {
			universum[k] = element;
			k++;
		}
	}
}

// difference operation
void difference(char * set, char * universum, char * result) {
	int size_universum = length(universum);
	for (int i = 0; i < size_universum; i++) {
		if (is_unic(set, universum[i])) {
			result[length(result)] = universum[i];
		}
	}
}

// make bit set
int to_bit(char * set, char * universum) {
	int bit = 0;
	int size = length(universum);
	for (int i = 0; i < size; i++)
	{
		if (!is_unic(set, universum[i]))
		{
			bit = bit | (int)pow(2, i);
		}
	}
	return bit;
}

void to_array(int* bit_boolean, char* universum, int size)
{
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < 15; i++)
		{
			if (bit_boolean[k] & ((int)(pow(2, i))))
			{
				/*boolean_result[length(boolean_result)] = universum[i];*/
				std::cout << universum[i] << ' ';
			}
		}
		std::cout << std::endl;
	}
}


int main() {
	// creating set objects
	char arr[16];
	char arr1[16];
	char universum[16];
	char result[16];
	int bit_boolean[16];
	char boolean_result[16];

	// initialising objects
	set_set(arr);
	set_set(arr1);
	create_universum(arr, arr1, universum);
	initialise(result, 16);
	initialise(boolean_result, 16);
	difference(arr, universum, result);

	// creating vectors
	int bit_result_operation = to_bit(result, universum);
	int k = 0;
	// bug is here
	for (int i = 0; i <= bit_result_operation; i++) {
		if ( (bit_result_operation & i) == i) {
			bit_boolean[k] = i;
			k++;
		}
	}
	std::cout << bit_boolean[0] << " " << bit_boolean[1] << " " << bit_boolean[2] << " " << std::endl;
	int bool_size = pow(2, length(result));
	to_array(bit_boolean, universum, bool_size);

	
	system("pause");
}
