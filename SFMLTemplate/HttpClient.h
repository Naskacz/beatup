#pragma once
#include <string>
#include <vector>
#include <curl/curl.h>
struct Score {
	std::string nickname;
	int score;
	std::string song;
};

class HttpClient
{
public:
	HttpClient(const std::string& serverUrl = "http://localhost:8080");
	~HttpClient();
	bool sendScore(const Score& s, std::string& responseOut);
	bool fetchScores(const std::string& song, std::vector<Score>& outList);
private:
	std::string baseUrl_;
	CURL* curl_;

	static size_t writeCallback(void* contents, size_t size, size_t nmeb, void* userp);
};

