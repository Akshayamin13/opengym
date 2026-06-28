#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include "MemberRepository.h"
#include "ContractRepository.h"

int main() {
    pqxx::connection conn("dbname=opengym");
    if (!conn.is_open()) {
        std::cout << "Could not connect to database." << std::endl;
        return 1;
    }

    MemberRepository memberRepo(conn);
    ContractRepository contractRepo(conn);

    int choice = 0;

    while (choice != 7) {
        std::cout << std::endl;
        std::cout << "=== OpenGym ===" << std::endl;
        std::cout << "1. Add member" << std::endl;
        std::cout << "2. List all members" << std::endl;
        std::cout << "3. Find member by ID" << std::endl;
        std::cout << "4. Add contract" << std::endl;
        std::cout << "5. List all contracts" << std::endl;
        std::cout << "6. List contracts for a member" << std::endl;
        std::cout << "7. Quit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Please enter a number (1-7)." << std::endl;
            continue;
        }

        if (choice == 1) {
            int id;
            std::string firstName, lastName, email;
            std::cout << "Enter ID: ";
            std::cin >> id;
            if (std::cin.fail()) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Invalid ID." << std::endl; continue; }
            std::cin.ignore();
            std::cout << "Enter first name: "; std::getline(std::cin, firstName);
            std::cout << "Enter last name: ";  std::getline(std::cin, lastName);
            std::cout << "Enter email: ";      std::getline(std::cin, email);
            memberRepo.addMember(Member(id, firstName, lastName, email));
            std::cout << "Member added!" << std::endl;
        }
        else if (choice == 2) {
            memberRepo.listAll();
        }
        else if (choice == 3) {
            int searchId;
            std::cout << "Enter ID to search: ";
            std::cin >> searchId;
            if (std::cin.fail()) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Invalid ID." << std::endl; continue; }
            Member* found = memberRepo.findById(searchId);
            if (found != nullptr) {
                std::cout << "Found: " << found->firstName << " " << found->lastName << " | " << found->email << std::endl;
            } else {
                std::cout << "No member with ID " << searchId << " found." << std::endl;
            }
        }
        else if (choice == 4) {
            int id, memberId;
            std::string type;
            double fee;
            int activeInput;

            std::cout << "Enter contract ID: ";
            std::cin >> id;
            if (std::cin.fail()) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Invalid input." << std::endl; continue; }

            std::cout << "Enter member ID this contract belongs to: ";
            std::cin >> memberId;
            if (std::cin.fail()) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Invalid input." << std::endl; continue; }

            std::cin.ignore();
            std::cout << "Enter contract type (e.g. Basic, Premium): ";
            std::getline(std::cin, type);

            std::cout << "Enter monthly fee (e.g. 29.99): ";
            std::cin >> fee;
            if (std::cin.fail()) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Invalid fee." << std::endl; continue; }

            std::cout << "Is it active? (1 for yes, 0 for no): ";
            std::cin >> activeInput;

            contractRepo.addContract(Contract(id, memberId, type, fee, activeInput == 1));
            std::cout << "Contract added!" << std::endl;
        }
        else if (choice == 5) {
            contractRepo.listAll();
        }
        else if (choice == 6) {
            int memberId;
            std::cout << "Enter member ID: ";
            std::cin >> memberId;
            if (std::cin.fail()) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Invalid input." << std::endl; continue; }
            contractRepo.listForMember(memberId);
        }
        else if (choice == 7) {
            std::cout << "Goodbye!" << std::endl;
        }
        else {
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    }

    return 0;
}
