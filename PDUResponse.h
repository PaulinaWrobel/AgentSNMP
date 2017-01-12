#ifndef PDURESPONSE_H
#define PDURESPONSE_H

#include <string>
#include "defines.h"
#include "BerTree.h"
#include "SNMPDeserializer.h"
#include "SNMPSerializer.h"
#include "Tree.h"

class PDUResponse {
public:
    PDUResponse();
    ~PDUResponse();
    bool getPermissions(std::string communityString);
    // void makeResponsePDU(BerTree &dbt, BerTree &sbt);
    void makeResponsePDU(SNMPDeserializer &di, SNMPSerializer &si, Tree &tree);
    void makeSkelPDU(SNMPSerializer &si);
    void makeWrongOidPDU(SNMPDeserializer &di, SNMPSerializer &si);
    void makeWrongValuePDU(SNMPSerializer &si, Tree &tree);
    bool checkOidExistence(SNMPDeserializer &di, Tree &tree);
    bool checkOidExistenceNext(SNMPDeserializer &di, Tree &tree);
    bool checkValueCorectness(Tree &tree);

    char requestType;
    std::list<char> requestID;
    bool permissionRead;
    bool permissionWrite;
    int errorIndex;
    int errorValue;
    std::vector<int> oidList;
    std::vector<int> valueList;

};




#endif /* PDURESPONSE_H */