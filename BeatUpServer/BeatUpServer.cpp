#include <crow.h>
#include <pqxx/pqxx>
#include <iostream>


// Konfiguracja po³¹czenia do DB
static const std::string conninfo =
"host=localhost port=5432 dbname=postgres user=postgres password=postgres";

int main()
{
    crow::SimpleApp app;
    try {
        pqxx::connection C(conninfo);
        pqxx::work txn{ C };

        // Tworzymy tabelê scores jeœli nie istnieje
        txn.exec(R"(
            CREATE TABLE IF NOT EXISTS scores (
                id SERIAL PRIMARY KEY,
                nickname VARCHAR(255) NOT NULL,
                score INTEGER NOT NULL,
                beatmap VARCHAR(255) NOT NULL
            );
        )");

        txn.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "B³¹d tworzenia tabeli: " << e.what() << std::endl;
        return 1; // koñczymy program, bo nie da siê dzia³aæ bez tabeli
    }
    // Endpoint POST /score
    CROW_ROUTE(app, "/score").methods(crow::HTTPMethod::POST)
        ([](const crow::request& req) {
        try {
            auto body = crow::json::load(req.body);
            if (!body || !body.has("nickname") || !body.has("score") || !body.has("beatmap"))
                return crow::response(400, "Invalid JSON");

            std::string nickname = body["nickname"].s();
            int score = body["score"].i();
            std::string beatmap = body["beatmap"].s();

            // Budujemy surowe zapytanie SQL
            pqxx::connection C(conninfo);
            pqxx::work txn{ C };
            txn.exec("INSERT INTO scores (nickname, score, beatmap) VALUES (" +
                txn.quote(nickname) + ", " +
                std::to_string(score) + ", " +
                txn.quote(beatmap) + ")");
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

            std::string sql = "SELECT nickname, score, beatmap FROM scores";
            if (auto ps = req.url_params.get("beatmap")) {
                sql += " WHERE beatmap = " + W.quote(ps);
            }
            sql += " ORDER BY score DESC LIMIT 10;";

            pqxx::result R = W.exec(sql);

            crow::json::wvalue result;
            int i = 0;
            for (const auto& row : R) {
                result[i]["nickname"] = row["nickname"].c_str();
                result[i]["score"] = row["score"].as<int>();
                result[i]["beatmap"] = row["beatmap"].c_str();
                ++i;
            }
            return crow::response(result);
        }
        catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
            });
    app.port(8080).multithreaded().run();
}