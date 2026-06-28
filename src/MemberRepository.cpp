#include <iostream>
#include <pqxx/pqxx>
#include "MemberRepository.h"

MemberRepository::MemberRepository(pqxx::connection& connection) : conn(connection) {}

void MemberRepository::addMember(const Member& m) {
    try {
        pqxx::work txn(conn);
        txn.exec_params(
            "INSERT INTO members (id, first_name, last_name, email) VALUES ($1, $2, $3, $4)",
            m.id, m.firstName, m.lastName, m.email
        );
        txn.commit();
    } catch (const std::exception& e) {
        std::cout << "Error adding member: " << e.what() << std::endl;
    }
}

void MemberRepository::listAll() const {
    try {
        pqxx::work txn(conn);
        pqxx::result result = txn.exec("SELECT id, first_name, last_name, email FROM members ORDER BY id");
        txn.commit();

        std::cout << "=== Gym Members ===" << std::endl;
        std::cout << "Total members: " << result.size() << std::endl;
        std::cout << std::endl;

        for (auto row : result) {
            std::cout << "ID: " << row[0].as<int>()
                      << " | " << row[1].as<std::string>()
                      << " " << row[2].as<std::string>()
                      << " | " << row[3].as<std::string>() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error listing members: " << e.what() << std::endl;
    }
}

int MemberRepository::count() const {
    try {
        pqxx::work txn(conn);
        pqxx::result result = txn.exec("SELECT COUNT(*) FROM members");
        txn.commit();
        return result[0][0].as<int>();
    } catch (const std::exception& e) {
        std::cout << "Error counting members: " << e.what() << std::endl;
        return 0;
    }
}

Member* MemberRepository::findById(int id) {
    static Member found(0, "", "", "");

    try {
        pqxx::work txn(conn);
        pqxx::result result = txn.exec_params(
            "SELECT id, first_name, last_name, email FROM members WHERE id = $1",
            id
        );
        txn.commit();

        if (result.empty()) {
            return nullptr;
        }

        auto row = result[0];
        found = Member(
            row[0].as<int>(),
            row[1].as<std::string>(),
            row[2].as<std::string>(),
            row[3].as<std::string>()
        );
        return &found;
    } catch (const std::exception& e) {
        std::cout << "Error finding member: " << e.what() << std::endl;
        return nullptr;
    }
}