#include<stdio.h>
#include<iostream>
#include <filesystem>
#include <map>
#include <sstream> 
#include <locale>
using namespace std;
namespace fpath = std::filesystem;

void rPrint(map<string, uintmax_t> extensionSizes, map<string, int>extensionCount)
{
	auto rit1 = extensionCount.rbegin();
	auto rit2 = extensionSizes.rbegin();


	while (rit1 != extensionCount.rend() && rit2 != extensionSizes.rend()) {

		cout << "Extension: " << rit1->first << " | "
			<< "# file(s): " << rit1->second << " | "
			<< "Total size: " << rit2->second << endl;
		++rit1;
		++rit2;
	}
}

void sPrint(map<string, uintmax_t> extensionSizes, map<string, int>extensionCount, int srCheck)
{
	vector<pair<string, uintmax_t>> sortedSizes(extensionSizes.begin(), extensionSizes.end());
	sort(sortedSizes.begin(), sortedSizes.end(), [](const auto& a, const auto& b) {
		return a.second < b.second;
		});

	if (srCheck == 1) {
		for (const auto& pair : sortedSizes) {
			string extension = pair.first;
			uintmax_t totalSize = pair.second;
			int fileCount = extensionCount[extension];

			cout << "Extension: " << extension << " | "
				<< "# file(s): " << fileCount << " | "
				<< "Total size: " << totalSize << endl;
		}
	}

	if (srCheck == 2)
	{
		for (auto rit = sortedSizes.rbegin(); rit != sortedSizes.rend(); ++rit) {
			string extension = rit->first;
			uintmax_t totalSize = rit->second;
			int fileCount = extensionCount[extension];

			cout << "Extension: " << extension << " | "
				<< "# file(s): " << fileCount << " | "
				<< "Total size: " << totalSize << endl;
		}

	}
}

int main(int argc, char* argv[])
{
	fpath::path dir = fpath::current_path();
	map<string, uintmax_t> extensionSizes;
	map<string, int> extensionCount;
	int result = 0;
	int fileCount = 0;
	string sw;
	int sCheck = 0;
	int srCheck = 0;

	for (const auto& entry : fpath::directory_iterator(dir))
	{
		if (fpath::is_regular_file(entry)) {

			string extension = entry.path().extension().string();
			uintmax_t fileSize = fpath::file_size(entry);

			extensionSizes[extension] += fileSize;
			extensionCount[extension]++;
		}
	}

	auto it1 = extensionSizes.begin();
	auto it2 = extensionCount.begin();

	for (int i = 1; i < argc; i++)
	{
		sw = argv[i];
		if (sw == "-h") {
			printf("\nfileusage [-switches] [--help] [folder]\n");
			printf("switches\n");
			printf("\t-h: display help\n");
			printf("\t-r: reverse order of listing\n");
			printf("\t-s: sort by size\n");
			printf("\t-x: regrex\n");
			printf("foler\n");
			printf("\tstarting folder or current folder if not provided\n");
			sCheck = 1;

		}

		else if (sw == "--help")
		{
			printf("\nfileusage [-switches] [--help] [folder]\n");
			printf("switches\n");
			printf("\t-h: display help\n");
			printf("\t-r: reverse order of listing\n");
			printf("\t-s: sort by size\n");
			printf("\t-x: regrex\n");
			printf("foler\n");
			printf("\tstarting folder or current folder if not provided\n");
			sCheck = 1;
		}

		else if (sw == "-r") {
			sCheck = 1;

			if (srCheck != 2)
			{
				rPrint(extensionSizes, extensionCount);
			}
		}

		else if (sw == "-sr" || sw == "-rs") {
			srCheck = 2;
			sCheck = 1;
			sPrint(extensionSizes, extensionCount, srCheck);
		}


		else if (sw == "-s") {
			srCheck = 1;
			sCheck = 1;
			sPrint(extensionSizes, extensionCount, srCheck);
		}

		else {
			printf("Invalid switch(es)");
			sCheck = 1;
		}
	}

	if (sCheck == 0) {
		while (it1 != extensionSizes.end() && it2 != extensionCount.end())
		{
			cout << "Extension: " << it1->first << " | "
				<< "# file(s): " << it2->second << " | "
				<< "Total size: " << it1->second << endl;
			++it1;
			++it2;
		}
	}

	return 0;
}
