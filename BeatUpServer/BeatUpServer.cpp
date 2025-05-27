#include <crow.h>
#include <pqxx/pqxx>
#include <iostream>


// Konfiguracja po³¹czenia do DB
static const std::string conninfo =
"host=localhost port=5432 dbname=postgres user=postgres password=postgres";

int main()
{
    crow::SimpleApp app;

    // Endpoint POST /score
    CROW_ROUTE(app, "/score").methods(crow::HTTPMethod::POST)
        ([](const crow::request& req) {
        try {
            auto body = crow::json::load(req.body);
            if (!body || !body.has("nickname") || !body.has("score") || !body.has("song"))
                return crow::response(400, "Invalid JSON");

            std::string nickname = body["nickname"].s();
            int score = body["score"].i();
            std::string song = body["song"].s();

            // Budujemy surowe zapytanie SQL
            pqxx::connection C(conninfo);
            pqxx::work txn{ C };
            txn.exec("INSERT INTO scores (nickname, score, song) VALUES (" +
                txn.quote(nickname) + ", " +
                std::to_string(score) + ", " +
                txn.quote(song) + ")");
            txn.commit();

            return crow::response(200, "Score saved.");
        }
        catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
            });

    // Endpoint GET /scores
    CROW_ROUTE(app, "/scores").methods(crow::HTTPMethod::GET)
        ([](const crow::request& req) {
        try {
            pqxx::connection C(conninfo);
            pqxx::work W(C);

            std::string sql = "SELECT nickname, score, song FROM scores";
            if (auto ps = req.url_params.get("song")) {
                sql += " WHERE song = " + W.quote(ps);
            }
            sql += " ORDER BY score DESC LIMIT 10;";

            pqxx::result R = W.exec(sql);

            crow::json::wvalue result;
            int i = 0;
            for (const auto& row : R) {
                result[i]["nickname"] = row["nickname"].c_str();
                result[i]["score"] = row["score"].as<int>();
                result[i]["song"] = row["song"].c_str();
                ++i;
            }
            return crow::response(result);
        }
        catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
            });
    //Endpoint POST /song
    //CROW_ROUTE(app, "/song").methods(crow::HTTPMethod::POST)
    //    ([](const crow::request& req) {
    //    try {
    //        auto body = crow::json::load(req.body);
    //        if (!body || !body.has("name"))
    //            return crow::response(400, "Invalid JSON");

    //        std::string name = body["name"].s();

    //        // Budujemy zapytanie SQL
    //        std::string sql =
    //            "INSERT INTO songs (name) VALUES ('" +
    //            name + "');";

    //        pqxx::connection C(conninfo);
    //        pqxx::work W(C);
    //        W.exec(sql);
    //        W.commit();

    //        return crow::response(200, "Song added.");
    //    }
    //    catch (const std::exception& e) {
    //        return crow::response(500, e.what());
    //    }
    //        });
    app.port(8080).multithreaded().run();
}