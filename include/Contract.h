#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>

class Contract {
public:
    int id;
    int memberId;
    std::string type;
    double monthlyFee;
    bool active;

    Contract(int contractId, int memberRef, std::string contractType, double fee, bool isActive);
};

#endif