#ifndef OPMOCK2_HPP_
#define OPMOCK2_HPP_

class OpParameter
{
public:
    std::string name;
    std::string desugaredType;
    std::string castTypeL;
    std::string castTypeR;
    std::string orgTypeL;
    std::string orgTypeR;
    bool isReference;

    OpParameter();

};

class OpRecord;

class OpFunction
{
public:
    std::string name;
    std::string qualifiedName;
    std::vector<std::string> ns;
    int overloads;
    bool isConst;
    bool isStatic;
    bool isExtern;
    bool isVariadic;
    bool returnsVoid;
    bool isInlined;
    bool isVirtual;
    bool isPureVirtual;
    bool isConstructor;
    bool isDestructor;
    bool isOperatorOverload;
    bool isTemplate;
    //volatile?
    //restrict
    //
    OpParameter returnValue; //must go TODO
    std::vector<OpParameter *> parameters;

    std::string retStructType;
    std::string retSignatureLeft;
    std::string retSignatureRight;
    bool retIsReference;

    OpFunction();
    std::string getfixedScopedOverloadedName();
    std::string buildParameters();
    std::string buildParameterNames();
    std::string buildSignature ( OpRecord *one_rec );
};

class OpRecord
{
public:
    std::string name;
    std::string qualifiedName;
    std::vector<std::string> ns;
    std::vector<OpFunction *> methods;
    //std::vector<OpFunction *> constructors;
    //std::vector<OpFunction *> destructors;
    bool isStruct;
    bool isTemplate;
    OpRecord();
};

class NameMap
{
public:
    std::vector< std::vector < std::string > > nsList;
};

#endif

