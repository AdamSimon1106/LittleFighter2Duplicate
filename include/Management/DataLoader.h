#include<string>
#include<vector>

class DataLoader {
public:
	DataLoader(std::string pathToIndex);
	void parseDataIndex();
	void printPaths() const;
	bool loadCharacterDat();
	std::string getCurrentlyLoadingFile() const;
private:
	int m_currentIndex = 0;
	std::string m_currentFile;
	std::string m_pathToIndex;
	std::vector<std::pair<std::string, std::string>> m_datPaths;
};