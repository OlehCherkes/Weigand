#include <iostream>
#include <cstdint>
#include <array>
#include <bitset>
#include <vector>
#include <numeric>

const uint8_t keySize = 10;

enum T_Weigand {
	WEIGAND_26,
	WEIGAND_32,
	WEIGAND_34,
	WEIGAND_35,
	WEIGAND_37,
	WEIGAND_64,
	WEIGAND_80
};

/*---------------	Shift bit	----------------------*/
//template <std::size_t N>
//void shiftArray(std::array<uint8_t, N>& arr, int shiftAmount) {
//	for (auto& element : arr) {
//		element = element << shiftAmount;
//	}
//}

//std::optional<>;
//std::pair<array, bool>
//std::tupple <array, bool, size>

/*---------------	Set Key	----------------------*/
//std::array<uint8_t, keySize> setKey() {
//	std::array<uint8_t, keySize> key;
//	uint8_t input = 0;
//	uint8_t index = 0;
//	std::cout << "Entrer key (enter character '/' to comlete input): " << std::endl;
//	while (std::cin >> input) {
//		if (input == '/')
//			break;
//		key[index] = input;
//		index++;
//	}
//
//	std::cout << "Your key: ";
//	for (int i = 0; i < index; i++) {
//		std::cout << key[i];
//	}
//
//	return key;
//}

bool checkParity(const std::vector<bool>& binaryArray) {
	bool first = false;;
	bool second = false;
	auto i = 0;

	for (auto b : binaryArray)
	{
		if (!b)
		{
			i++;
			continue;
		}

		if (i < std::ceil(binaryArray.size() / 2))
		{
			first = !first;
		}
		else
		{
			second = !second;
		}
	}

	//std::cout << "First part of kay: " << static_cast<int>(first) << std::endl;
	//std::cout << "Second part of key: " << static_cast<int>(second) << std::endl;

	return first ^ second;
}

void setBits(const std::vector<bool>& binaryArray, std::array<uint8_t, keySize>& keyArr, bool checkParity)
{
	std::cout << "SUCCESSFUL CARD READ" << std::endl;

	auto iB = binaryArray.begin() + 1;
	auto iE = binaryArray.end() - 1;

	if (checkParity == false) {
		iB = binaryArray.begin();
		iE = binaryArray.end();
	}

	auto iDst = keyArr.begin();
	uint8_t b = 0x80;
	*iDst = 0;

	while (iB != iE)
	{
		if (*iB++)
		{
			*iDst |= b;
		}

		b >>= 1;

		if (0 == b)
		{
			*iDst++ = 0;
			b = 0x80;
		}
	}
}

void printKey(const std::array<uint8_t, keySize>& keyArr) {
	std::cout << "YOUR KEY: ";
	for (const auto& value : keyArr) {
		std::cout << std::hex << static_cast<int>(value);
	}
	std::cout << std::endl;
}

std::array <uint8_t, keySize> countKey(std::string binaryString, T_Weigand weigan)
{
	std::array<uint8_t, keySize> keyArr;
	std::vector<bool> binaryArray;

	for (const auto& i : binaryString) {
		binaryArray.push_back(i == '1');
	}

	std::cout << "Your binary: ";
	for (const auto& bin : binaryArray) {
		std::cout << bin;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	switch (weigan)
	{
		case WEIGAND_26:
		{
			binaryArray.resize(26);
			if (!checkParity(binaryArray))
			{
				std::cout << "!!! CARD FAILED !!!" << std::endl;
				keyArr.fill(0);
				break;
			}

			setBits(binaryArray, keyArr, true);
			printKey(keyArr);

			break;
		}

		case WEIGAND_32:
		{
			binaryArray.resize(32);

			setBits(binaryArray, keyArr, false);
			printKey(keyArr);

			break;
		}


		case WEIGAND_34:
		{
			binaryArray.resize(34);

			if (!checkParity(binaryArray))
			{
				std::cout << "!!! CARD FAILED !!!" << std::endl;
				keyArr.fill(0);
				break;
			}

			setBits(binaryArray, keyArr, true);
			printKey(keyArr);

			break;
		}

		case WEIGAND_35:
			binaryArray.resize(35);

			if (!checkParity(binaryArray))
			{
				std::cout << "!!! CARD FAILED !!!" << std::endl;
				keyArr.fill(0);
				break;
			}

			setBits(binaryArray, keyArr, true);
			printKey(keyArr);

		    break;

		case WEIGAND_37:
			binaryArray.resize(37);

			if (!checkParity(binaryArray))
			{
				std::cout << "!!! CARD FAILED !!!" << std::endl;
				keyArr.fill(0);
				break;
			}

			setBits(binaryArray, keyArr, true);
			printKey(keyArr);

		    break;

		case WEIGAND_64:
		{
			binaryArray.resize(64);

			setBits(binaryArray, keyArr, false);
			printKey(keyArr);

			break;
		}

		case WEIGAND_80:
		{
			binaryArray.resize(80);

			setBits(binaryArray, keyArr, false);
			printKey(keyArr);

			break;
		}

		default:
			std::cout << "UNCNOWN CARD" << std::endl;
			break;
	}

	return keyArr;
}


int main() {
	countKey("01001101010010101001100010000000000000000000000", WEIGAND_26);

	return 0;
}