#include "commodity.h"

COMMODITY_TYPE Commodity::GetType() {
    return type;
}

void Commodity::SetType(COMMODITY_TYPE type) {
    this->type = type;
}
