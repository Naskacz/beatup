#pragma once
#include <string>
#include <vector>
#include <curl/curl.h>
struct Score {
	std::string nickname; // nazwa gracza
	int score; // wynik gracza
	std::string beatmap; // nazwa beatmapy, na której zosta³ osi¹gniêty wynik
};

class HttpClient
{
public:
	HttpClient(const std::string& serverUrl = "http://localhost:8080");
	~HttpClient();
	bool sendScore(const Score& s, std::string& responseOut);
	bool fetchScores(const std::string& beatmap, std::vector<Score>& outList);
private:
	std::string baseUrl_; // adres serwera
	CURL* curl_; // wskaŸnik do obiektu CURL

	static size_t writeCallback(void* contents, size_t size, size_t nmeb, void* userp);
};

