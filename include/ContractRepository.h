#ifndef CONTRACT_REPOSITORY_H
#define CONTRACT_REPOSITORY_H

#include <vector>
#include <string>
#include <pqxx/pqxx>
#include "Contract.h"

class ContractRepository {
private:
    pqxx::connection& conn;

public:
    ContractRepository(pqxx::connection& connection);

    void addContract(const Contract& c);
    void listAll() const;
    void listForMember(int memberId) const;
    int count() const;
};

#endif
