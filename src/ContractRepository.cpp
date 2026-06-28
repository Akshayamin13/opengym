#include <iostream>
#include <pqxx/pqxx>
#include "ContractRepository.h"

ContractRepository::ContractRepository(pqxx::connection& connection) : conn(connection) {}

void ContractRepository::addContract(const Contract& c) {
    try {
        pqxx::work txn(conn);
        txn.exec_params(
            "INSERT INTO contracts (id, member_id, type, monthly_fee, active) VALUES ($1, $2, $3, $4, $5)",
            c.id, c.memberId, c.type, c.monthlyFee, c.active
        );
        txn.commit();
    } catch (const std::exception& e) {
        std::cout << "Error adding contract: " << e.what() << std::endl;
    }
}

void ContractRepository::listAll() const {
    try {
        pqxx::work txn(conn);
        pqxx::result result = txn.exec("SELECT id, member_id, type, monthly_fee, active FROM contracts ORDER BY id");
        txn.commit();

        std::cout << "=== Contracts ===" << std::endl;
        std::cout << "Total contracts: " << result.size() << std::endl;
        std::cout << std::endl;

        for (auto row : result) {
            std::cout << "ID: " << row[0].as<int>()
                      << " | Member: " << row[1].as<int>()
                      << " | Type: " << row[2].as<std::string>()
                      << " | Fee: " << row[3].as<double>()
                      << " | Active: " << (row[4].as<bool>() ? "Yes" : "No") << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error listing contracts: " << e.what() << std::endl;
    }
}

void ContractRepository::listForMember(int memberId) const {
    try {
        pqxx::work txn(conn);
        pqxx::result result = txn.exec_params(
            "SELECT id, type, monthly_fee, active FROM contracts WHERE member_id = $1 ORDER BY id",
            memberId
        );
        txn.commit();

        std::cout << "=== Contracts for Member " << memberId << " ===" << std::endl;

        if (result.empty()) {
            std::cout << "No contracts found for this member." << std::endl;
            return;
        }

        for (auto row : result) {
            std::cout << "ID: " << row[0].as<int>()
                      << " | Type: " << row[1].as<std::string>()
                      << " | Fee: " << row[2].as<double>()
                      << " | Active: " << (row[3].as<bool>() ? "Yes" : "No") << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error listing contracts: " << e.what() << std::endl;
    }
}

int ContractRepository::count() const {
    try {
        pqxx::work txn(conn);
        pqxx::result result = txn.exec("SELECT COUNT(*) FROM contracts");
        txn.commit();
        return result[0][0].as<int>();
    } catch (const std::exception& e) {
        std::cout << "Error counting contracts: " << e.what() << std::endl;
        return 0;
    }
}
