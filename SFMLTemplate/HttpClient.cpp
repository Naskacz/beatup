#include "HttpClient.h"
#include <sstream>
#include <iostream>

HttpClient::HttpClient(const std::string& serverUrl)
    : baseUrl_(serverUrl), curl_(curl_easy_init())
{
}

HttpClient::~HttpClient() {
    if (curl_) curl_easy_cleanup(curl_);
}

size_t HttpClient::writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    auto* s = static_cast<std::string*>(userp);
    s->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool HttpClient::sendScore(const Score& s, std::string& responseOut) {
    if (!curl_) return false;

    std::string url = baseUrl_ + "/score";
    std::ostringstream json;
    json << R"({"nickname":")" << s.nickname
        << R"(","score":)" << s.score
        << R"(,"song":")" << s.song << R"("})";

    std::string jsonStr = json.str();
    std::cout << "Sending JSON: " << jsonStr << "\n";

    curl_easy_reset(curl_);
    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_, CURLOPT_POST, 1L);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, jsonStr.c_str());
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, jsonStr.size());

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &responseOut);

    CURLcode res = curl_easy_perform(curl_);
    curl_slist_free_all(headers);

    return (res == CURLE_OK);
}

bool HttpClient::fetchScores(const std::string& song, std::vector<Score>& outList) {
    if (!curl_) return false;
    std::ostringstream url;
    url << baseUrl_ << "/scores";
    if (!song.empty()) url << "?song=" << curl_easy_escape(curl_, song.c_str(), 0);
    std::string resp;
    curl_easy_reset(curl_);
    curl_easy_setopt(curl_, CURLOPT_URL, url.str().c_str());
    curl_easy_setopt(curl_, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &resp);

    CURLcode res = curl_easy_perform(curl_);
    if (res != CURLE_OK) return false;

    // Proste parsowanie JSON (bez biblioteki) – wyci¹gamy nickname i score
    // W produkcji u¿yj nlohmann::json
    size_t pos = 0;
    while ((pos = resp.find("{", pos)) != std::string::npos) {
        Score sc;
        auto kn = resp.find(R"("nickname":")", pos);
        if (kn == std::string::npos) break;
        kn += 12;
        auto ke = resp.find("\"", kn);
        sc.nickname = resp.substr(kn, ke - kn);

        auto ks = resp.find(R"("score":)", ke);
        if (ks == std::string::npos) break;
        ks += 8;

        size_t score_end = resp.find_first_of(",}", ks);
        if (score_end == std::string::npos) score_end = resp.size();
        std::string score_str = resp.substr(ks, score_end - ks);

        sc.score = std::stoi(score_str);

        auto ksid = resp.find(R"("song":")", ks);
		if (ksid == std::string::npos) break;
        ksid += 8;
        auto song_end = resp.find("\"", ksid);
		if (song_end == std::string::npos) break;
        sc.song = resp.substr(ksid, song_end - ksid);

        outList.push_back(sc);
        pos = song_end + 1;
    }
    return true;
}
