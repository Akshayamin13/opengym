#ifndef MEMBER_REPOSITORY_H
#define MEMBER_REPOSITORY_H

#include <vector>
#include <string>
#include <pqxx/pqxx>
#include "Member.h"

class MemberRepository {
private:
    pqxx::connection& conn;

public:
    MemberRepository(pqxx::connection& connection);

    void addMember(const Member& m);
    void listAll() const;
    int count() const;
    Member* findById(int id);
};

#endif
