void SetRussian();

struct MashroomDictionary
{
	char name[20];
	bool eatable;
	int category;
};

void CreateDictionary(MashroomDictionary *md, int *mCount);
void DestroyDictionary(MashroomDictionary *md);
void PrintDictionary(const MashroomDictionary *md);
void SortDictionary(MashroomDictionary *md, const int mCount);
void SaveDictionary(const MashroomDictionary *md);
void printTxt();
char* IsEatebleText(const bool isEatable);