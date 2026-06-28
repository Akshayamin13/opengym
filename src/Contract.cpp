#include "Contract.h"

Contract::Contract(int contractId, int memberRef, std::string contractType, double fee, bool isActive) {
    id = contractId;
    memberId = memberRef;
    type = contractType;
    monthlyFee = fee;
    active = isActive;
}