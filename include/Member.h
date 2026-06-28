#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member {
public:
    int id;
    std::string firstName;
    std::string lastName;
    std::string email;

    Member(int memberId, std::string fName, std::string lName, std::string mail);
};

#endif
