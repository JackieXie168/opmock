//* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * opmock2.cpp
 * Copyright (C) Pascal Ognibene 2012-2013 <pognibene@gmail.com>
 *
 * opmock is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * opmock is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// opmock3 will introduce breaking changes in APIs and
// refactor headers to extract inlined code (if too complex/not self contained)
// if the inlined code is 'clean' (depends only on the class attributes, does not trigger
//additional dependencies)
// then we may consider keep it and give a choice of using the original implementation
//(by default) or mocking it.
//

//FIXME fonction/methode avec parametres 'valeur par defaut'
//devrait donner des surcharges de la fonction (chacune avec
//un nombre de parametres differents). Il faut donc detecter
//les fonctions ayant des valeurs de parametre par defaut
//en C++ seulement? a priori je n'ai pas besoin de connaitre la valeur par
//defaut, juste le fait qu'il y en ait une.

//FIXME ne gere pas pour l'instant conversion operator


#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"

#include "clang/Frontend/CompilerInstance.h"
#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/Version.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"

#include "clang/Parse/ParseAST.h"
//#include "clang/Frontend/HeaderSearchOptions.h"
//with llvm32 new path
#include "clang/Lex/HeaderSearchOptions.h"

//new for 3.2
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include <clang/Frontend/TextDiagnosticBuffer.h>

#include "clang/Frontend/Utils.h"


#include <cstring>
#include <cstdio>
#include <ctype.h>
#include <vector>
#include <clang/AST/Type.h>

#include <clang/Frontend/ASTUnit.h>
#include <llvm/Support/CommandLine.h>

#include "opmock2.hpp"


#if defined _WIN32 || defined _WIN64 || defined WIN32 || defined WIN64 || defined __WIN32__ || defined __WIN64__
#define PATH_SEP '\\'
#define PATH_SEP_S "\\"
#else
#define PATH_SEP '/'
#define PATH_SEP_S "/"
#endif

void startHeaderFile ( std::string &output, std::string &input_file,
                       std::string &prefix, bool useQuotes, bool useCpp,
                       std::string &coutput, std::string &houtput, std::string &result );


void writeFunctionStruct ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out );

void writeFilesForC ( std::vector<clang::FunctionDecl *> functionList,
                      std::string &output, std::string &input_file,
                      std::string prefix, bool useQuotes );

void writeFilesForCpp ( std::vector<clang::FunctionDecl *> functionList,
                        std::vector<clang::CXXRecordDecl *> classList,
                        std::vector<clang::NamedDecl *> declList,
                        std::string &output, std::string &input_file,
                        std::string prefix, bool useQuotes,
                        std::string &funcToSkip, std::string &funcToKeep );

std::string SplitFilename ( const std::string &str );
std::string SplitPath ( const std::string &str );
std::string removeExt ( std::string &str );
void cleanPath ( std::string &str );
bool returnValueAsAString ( clang::FunctionDecl *fdecl,
                            std::string &retPrefix,
                            std::string &retSuffix,
                            bool useCanonical ); //TODO this function should disappear

void returnValueLR ( clang::FunctionDecl *fdecl,
                     std::string &retPrefix,
                     std::string &retSuffix );

void paramAsString ( clang::ParmVarDecl *pdecl, std::string &prefix, std::string &suffix,
                     bool useCanonical );

void replaceAll ( std::string &str, const std::string &from, const std::string &to );

bool isFunctionVoid ( clang::FunctionDecl *f );
bool isParmArray ( clang::ParmVarDecl *pdecl );
bool isParmPointer ( clang::ParmVarDecl *pdecl );
void tokenizeString ( const std::string &str,
                      std::vector<std::string> &tokens,
                      const std::string &delimiters );


std::string getStructReturnType ( clang::FunctionDecl *fdecl, bool &isReference );

OpParameter *splitParameter ( clang::ParmVarDecl *pdecl,
                              std::map< std::string, NameMap * > &nsmap,
                              int number );

OpFunction *extractFunction ( clang::FunctionDecl *mdecl,
                              std::map<std::string, int> &overloadMap,
                              std::map< std::string, NameMap * > &nsMap );

void writeFunctionBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out );
void writeFunctionMockResetBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out );
void writeFunctionMockWithCallbackBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out );
void writeFunctionMockWithInstanceCallbackBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out );

void writeFunctionVerifyMockBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out );
void writeFunctionExpectAndReturnBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out );

void writeConstructorBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out );
void writeDestructorBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out );

class MyRecursiveASTVisitorCpp
    : public clang::RecursiveASTVisitor<MyRecursiveASTVisitorCpp>
{
public:
    bool VisitDecl ( clang::Decl *d );
    // list of C style functions
    std::vector<clang::FunctionDecl *> functionList;
    // list of classes or struct
    std::vector<clang::CXXRecordDecl *> recordList;

    // full list of classes, structs, typedefs, functions
    // used to work around what looks like a clang limitation :
    // can't get the fully scoped name of a type from a function parameter.
    // I need that to generate C style functions (with no scope) using scoped
    // parameters.
    std::vector<clang::NamedDecl *> declList;

    clang::ASTContext *ast;
private:
};

bool MyRecursiveASTVisitorCpp::VisitDecl ( clang::Decl *d )
{
    // store all declarations for later use
    // don't store function parameters
    /*    clang::NamedDecl *ndecl = clang::dyn_cast<clang::NamedDecl> ( d );
        if ( ndecl )
        {
            clang::ParmVarDecl *parmdecl = clang::dyn_cast<clang::ParmVarDecl> ( d );
            if ( !parmdecl )
            {
                declList.push_back ( ndecl );
            }
        }
    */
    //debug
    /*    std::cout << "Visiting decl : "
                  << d->getDeclKindName() << "\n";
        clang::NamedDecl *ndecl = clang::dyn_cast<clang::NamedDecl> ( d );
        if ( ndecl )
        {
            std::cout <<  "nom decl " << ndecl->getNameAsString() << std::endl;
        }
    */

    if ( d->getKind() == clang::Decl::CXXRecord )
    {
        clang::CXXRecordDecl *rdecl =
            clang::dyn_cast<clang::CXXRecordDecl > ( d );

        clang::SourceLocation loc = d->getLocation();
        if ( ast->getSourceManager().isWrittenInMainFile ( loc ) )
        {
            recordList.push_back ( rdecl );
        }
        else
        {
            clang::SourceLocation loc2 = ast->getSourceManager().getExpansionLoc ( loc );
            if ( ast->getSourceManager().isWrittenInMainFile ( loc2 ) )
            {
                recordList.push_back ( rdecl );
            }
        }
    }
    else if ( d->getKind() == clang::Decl::Function )
    {
        clang::FunctionDecl *fdecl =
            clang::dyn_cast<clang::FunctionDecl > ( d );

        clang::SourceLocation loc = d->getLocation();
        if ( ast->getSourceManager().isWrittenInMainFile ( loc ) )
        {
            functionList.push_back ( fdecl );
        }
        else
        {
            clang::SourceLocation loc2 = ast->getSourceManager().getExpansionLoc ( loc );
            if ( ast->getSourceManager().isWrittenInMainFile ( loc2 ) )
            {
                functionList.push_back ( fdecl );
            }
        }
    }
    return true;
}

// declare globals to hold command line parameters
llvm::cl::opt<std::string> clOutputPath("o", llvm::cl::desc("Specify output path for code generation."), llvm::cl::value_desc("path"), llvm::cl::Required);
llvm::cl::opt<std::string> clInputFile("i", llvm::cl::desc("Specify input header with absolute or relative path."), llvm::cl::value_desc("input header"), llvm::cl::Required);
llvm::cl::opt<std::string> clFuncToSkip("s", llvm::cl::desc("[Optional] Comma separated list of fully scoped functions/methods to skip."), llvm::cl::value_desc("skip list"), llvm::cl::Optional);
llvm::cl::opt<std::string> clFuncToKeep("k", llvm::cl::desc("[Optional] Comma separated list of fully scoped functions/methods to keep."), llvm::cl::value_desc("keep list"), llvm::cl::Optional);
llvm::cl::opt<std::string> clHPrefix("p", llvm::cl::desc("[Optional] Prefix to include the original header in the mocked header."), llvm::cl::value_desc("header prefix"), llvm::cl::Optional);
llvm::cl::opt<bool> clUseQuotes("q", llvm::cl::desc("[Optional] include the original header with quotes \"\" instead of <> by default."), llvm::cl::value_desc("use quotes"), llvm::cl::Optional);
llvm::cl::opt<bool> clUseCpp("cpp", llvm::cl::desc("[Optional] Define the header as a c++ header. By default headers are parsed as C code."), llvm::cl::value_desc("parse as C++"), llvm::cl::Optional);
llvm::cl::list<std::string> clIncludes("I", llvm::cl::desc("[Optional] Include path for additional headers. May be used multiple times."), llvm::cl::value_desc("include path"), llvm::cl::ZeroOrMore, llvm::cl::Prefix);
llvm::cl::list<std::string> clMacros("D", llvm::cl::desc("[Optional] Define a pre processor macro. May be used multiple times."), llvm::cl::value_desc("define macro"), llvm::cl::ZeroOrMore, llvm::cl::Prefix);
llvm::cl::opt<std::string> clStandard("std", llvm::cl::desc("Specify language standard, for example c++98 for C++."), llvm::cl::value_desc("C or C++ standard"), llvm::cl::Optional);

int main ( int argc, char **argv )
{
    llvm::cl::ParseCommandLineOptions(argc, argv, "Opmock2 : a mocking framework for C and C++\n");

    using clang::CompilerInstance;
    using clang::TargetOptions;
    using clang::TargetInfo;
    std::vector<const char *> clangParamsList;

    std::string inputFile;
    std::string outputPath;
    std::string hprefix;
    std::string funcToSkip;
    std::string funcToKeep;
    bool useQuotes = false;
    bool useCpp = false;
    std::string langStandard;

    // parse command line options
    // options specific to opmock are:
    //
    // -cpp to specify that it's a c++ header. By default, we assume it's a C header
    // -i for the header file to parse
    // -o for the output path
    // -p to give an *optional* prefix for header inclusion when generating code
    // -q to use quotes when including the original header file. The default is to use < and >
    // -s to give a comma separated list of functions/method to skip when generating code
    // -k to give a comma separated list of functions/method to keep when generating code
    //
    inputFile = clInputFile;
    outputPath = clOutputPath;
    hprefix = clHPrefix;
    funcToSkip = clFuncToSkip;
    funcToKeep = clFuncToKeep;
    useQuotes = clUseQuotes;
    useCpp = clUseCpp;
    langStandard = clStandard;

    // build the arguments for clang, removing arguments specific to opmock
    // +1 arg because I need to put the file to be parsed first
    
    // add include path. I need to rebuild the -I in front of each option,
    // as it has been removed by arguments parsing.
    std::vector<std::string> newIncludes;
    for (unsigned i = 0; i != clIncludes.size(); ++i)
    {
        std::string newString = "-I" + clIncludes[i];
        newIncludes.push_back(newString);
    }
    
    std::vector<std::string> newMacros;
    for (unsigned i = 0; i != clMacros.size(); ++i)
    {
        std::string newString = "-D" + clMacros[i];
        newMacros.push_back(newString);
    }

    std::vector<std::string> newOptions;//miscellanous options
	newOptions.push_back(std::string("-Wno-pragma-once-outside-header"));
    if(useCpp)
    {
        newOptions.push_back(std::string("-x"));
        newOptions.push_back(std::string("c++"));
    }

     if(langStandard.length() > 0)
     {
         newOptions.push_back("-std=" + langStandard);
     }

    // first parameter is the header file to parse/compile
    clangParamsList.insert ( clangParamsList.begin(), inputFile.c_str() );

    // append the includes
    for (unsigned i = 0; i != newIncludes.size(); ++i)
    {
        clangParamsList.push_back(newIncludes[i].c_str());
    }
    
    // append the macros
    for (unsigned i = 0; i != newMacros.size(); ++i)
    {
        clangParamsList.push_back(newMacros[i].c_str());
    }

    // append other options for C++ and dialect
    for (unsigned i = 0; i != newOptions.size(); ++i)
    {
        clangParamsList.push_back(newOptions[i].c_str());
    }


    const char **argsPtr = new const char *[clangParamsList.size() + 1];
    int i = 0;
    for ( std::vector<const char *>::iterator it = clangParamsList.begin(); it != clangParamsList.end(); ++it )
    {
        argsPtr[i] = *it;
        i++;
    }
    llvm::ArrayRef<const char *> Args ( argsPtr, clangParamsList.size() );

    // AST preparation
    clang::ASTUnit *AST;

    llvm::IntrusiveRefCntPtr<clang::DiagnosticOptions> DiagOpts = new clang::DiagnosticOptions();
    clang::TextDiagnosticPrinter *DiagClient =
        new clang::TextDiagnosticPrinter ( llvm::errs(), &*DiagOpts );
    llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> DiagID ( new clang::DiagnosticIDs() );
    llvm::IntrusiveRefCntPtr<clang::DiagnosticsEngine> DiagsRef (
        new clang::DiagnosticsEngine ( DiagID, &*DiagOpts, DiagClient ) );

    clang::CompilerInvocation *CI = new clang::CompilerInvocation();
    clang::CompilerInvocation::CreateFromArgs ( *CI, Args.begin(), Args.end(), *DiagsRef );

    auto PCH = std::make_shared<clang::PCHContainerOperations>();
    AST = clang::ASTUnit::LoadFromCompilerInvocationAction ( CI, PCH, DiagsRef );

    MyRecursiveASTVisitorCpp myvis;
    myvis.ast = &AST->getASTContext();
    myvis.TraverseDecl ( AST->getASTContext().getTranslationUnitDecl() );

    // use common c/c++ code to filter out free functions
    std::vector<clang::FunctionDecl *> filteredFunctionList;

    if ( funcToSkip.size() > 0 )
    {
        std::vector<std::string> toSkip;
        tokenizeString ( funcToSkip, toSkip, "," );

        for ( std::vector<clang::FunctionDecl *>::iterator it2 = myvis.functionList.begin();
                it2 != myvis.functionList.end(); ++it2 )
        {
            clang::FunctionDecl *one_fdecl = *it2;
            bool shouldSkip = false;
            std::string fname = one_fdecl->getQualifiedNameAsString();

            for ( std::vector<std::string>::iterator it1 = toSkip.begin();
                    it1 != toSkip.end(); ++it1 )
            {
                std::string toCompare = *it1;
                if ( fname.compare ( toCompare ) == 0 )
                {
                    // note : could use an hashmap to avoid
                    // the nested loop. In case I have huge header files.
                    std::cout << "Skipping function " << fname
                              << " as it is in the exclusion list." << std::endl;
                    shouldSkip = true;
                    break;
                }
            }
            if ( shouldSkip == false )
            {
                filteredFunctionList.push_back ( one_fdecl );
            }
        }
    }
    else
    {
        filteredFunctionList = myvis.functionList;
    }

    // I can't filter class methods here because they're stored
    // in a CXXRecordDecl and I'm not sure I can modify the list
    // of operations of such a decl
    // so let's go for code generation and filter last moment,
    // when lists I control have been created

    std::vector<clang::FunctionDecl *> keepFunctionList;
    if ( funcToKeep.size() > 0 )
    {
        std::vector<std::string> toKeep;
        tokenizeString ( funcToKeep, toKeep, "," );

        for ( std::vector<clang::FunctionDecl *>::iterator it2 =
                    filteredFunctionList.begin();
                it2 != filteredFunctionList.end(); ++it2 )
        {
            clang::FunctionDecl *one_fdecl = *it2;
            bool shouldKeep = false;
            std::string fname = one_fdecl->getQualifiedNameAsString();

            for ( std::vector<std::string>::iterator it1 = toKeep.begin();
                    it1 != toKeep.end(); ++it1 )
            {
                std::string toCompare = *it1;
                if ( fname.compare ( toCompare ) == 0 )
                {
                    // note : could use an hashmap to avoid
                    // the nested loop. In case I have huge header files.
                    std::cout << "Keeping function " << fname
                              << " as it is in the keep list." << std::endl;
                    shouldKeep = true;
                    break;
                }
            }
            if ( shouldKeep == true )
            {
                keepFunctionList.push_back ( one_fdecl );
            }
        }
    }
    else
    {
        keepFunctionList = filteredFunctionList;
    }

    // now code generation
    if ( useCpp )
    {
        writeFilesForCpp ( keepFunctionList,
                           myvis.recordList,
                           myvis.declList,
                           outputPath, inputFile, hprefix, useQuotes,
                           funcToSkip, funcToKeep );
    }
    else
    {
        writeFilesForC ( keepFunctionList, outputPath,
                         inputFile, hprefix, useQuotes );
    }
    return 0;
}

struct my_toupper
{

    char operator() ( char c ) const
    {
        return std::toupper ( static_cast<unsigned char> ( c ) );
    }
};

void tokenizeString ( const std::string &str,
                      std::vector<std::string> &tokens,
                      const std::string &delimiters )
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of ( delimiters, 0 );
    // Find first "non-delimiter".
    std::string::size_type pos = str.find_first_of ( delimiters, lastPos );

    while ( std::string::npos != pos || std::string::npos != lastPos )
    {
        // Found a token, add it to the vector.
        tokens.push_back ( str.substr ( lastPos, pos - lastPos ) );
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of ( delimiters, pos );
        // Find next "non-delimiter"
        pos = str.find_first_of ( delimiters, lastPos );
    }
}

void writeFilesForC ( std::vector<clang::FunctionDecl *> functionList,
                      std::string &output, std::string &input_file,
                      std::string prefix, bool useQuotes )
{
    std::string cfile, hfile, startHeader;
    startHeaderFile ( output, input_file, prefix, useQuotes, false,
                      cfile, hfile, startHeader );
    std::ofstream hout;
    hout.open ( hfile.c_str() );
    hout << startHeader;
    hout << "#ifdef __cplusplus\n";
    hout << "extern \"C\" {\n";
    hout << "#endif\n\n";

    // generate C file with structs and functions bodies
    // in the same loop
    std::ofstream outc;
    outc.open ( cfile.c_str() );
    outc << "/* OPMOCK2 GENERATED CODE - DO NOT MODIFY */\n";
    std::string filename = SplitFilename ( input_file );
    outc << "#include \"" << removeExt ( filename ) + "_stub.h" << "\"\n";
    outc << "#include <stdio.h>\n";
    outc << "#include <string.h>\n\n";

    std::string bodies_string;
    std::string reset_all_body;
    std::string verify_all_body;
    reset_all_body = "static void opmock_reset_all_mocks_in_this_header()\n{\n";
    verify_all_body = "static void opmock_verify_all_mocks_in_this_header()\n{\n";


    // list of prototypes for expect and return
    int nb_func = 0;
    for ( std::vector<clang::FunctionDecl *>::iterator it = functionList.begin();
            it != functionList.end(); ++it )
    {
        // function name
        clang::FunctionDecl *fdecl = *it;
        std::string fname = fdecl->getNameAsString();
        if ( fdecl->isVariadic() )
        {
            std::cout << "WARNING " << fname << " is variadic, skipped\n";
        }
        else if ( fdecl->hasBody() )
        {
            std::cout << "WARNING " << fname << " is inlined, skipped\n";
        }
        else
        {
            nb_func++;
            // return value
            std::string retPrefix, retSuffix;
            std::string canonRetPrefix, canonRetSuffix;
            bool isFuncPtr = returnValueAsAString ( fdecl, retPrefix, retSuffix, false );
            /* bool isCanonFuncPtr = */ returnValueAsAString ( fdecl, canonRetPrefix, canonRetSuffix, true );
            bool isVoid = isFunctionVoid ( fdecl );

            // parameters and matchers
            std::string paramsStart;
            std::string paramsNames;
            std::string matchersStart;
            std::string paramsStruct;
            std::string matchersStruct;
            std::string matchersList;
            std::string assignList;
            std::string matchersAssignList;

            paramsStart = "(";
            unsigned nbParam = fdecl->getNumParams();
            for ( unsigned i = 0; i < nbParam; i++ )
            {
                clang::ParmVarDecl *pdecl = fdecl->getParamDecl ( i );
                std::string name = pdecl->getNameAsString();

                // cope with anonymous parameters
                if ( name.size() == 0 )
                {
                    char argbuffer[100];
                    sprintf ( argbuffer, "arg%d", i + 1 );
                    name = argbuffer;
                }

                paramsNames += name;
                if ( i < nbParam - 1 )
                {
                    paramsNames += ", ";
                }

                // update  list of matchers for mock impl
                matchersList += "        if(" + fname + "_struct_inst.calls[0].match_"
                                + name + ") {\n";
                matchersList += "            void * val1 = (void *) &" + fname
                                + "_struct_inst.calls[0]." + name + ";\n";
                matchersList += "            void * val2 = (void *) &" + name + ";\n";
                matchersList += "            int match_result = " + fname
                                + "_struct_inst.calls[0].match_" + name
                                + "(val1, val2, \"" + name + "\", get_matcher_message());\n";
                matchersList += "            if(match_result){\n";
                matchersList += "                char buffer[OP_ERROR_MESSAGE_LENGTH];\n";
                matchersList += "                snprintf(buffer, OP_ERROR_MESSAGE_LENGTH, \"WARNING : on call number %d of '" + fname + "', %s\"," + fname
                                + "_struct_inst.actualCalls, get_matcher_message());\n";
                matchersList += "                opmock_add_error_message((char *) buffer);\n";
                matchersList += "            }\n";
                matchersList += "        }\n";


                std::string parmPrefix, parmSuffix;
                std::string canonParmPrefix, canonParmSuffix;
                paramAsString ( pdecl, parmPrefix, parmSuffix, false );
                paramAsString ( pdecl, canonParmPrefix, canonParmSuffix, true );
                bool isArray = isParmArray ( pdecl );
                bool isPointer = isParmPointer ( pdecl );

                paramsStart += ( parmPrefix + " " + name );

                if ( parmSuffix.size() > 0 )
                {
                    paramsStart += ( " " + parmSuffix );
                }
                if ( i < nbParam - 1 )
                {
                    paramsStart += ", ";
                }

                // update struct parameters list
                // store the canonical type

                // however if the parameter is an array, cast it
                // to a void * as I can't have a struct attribute as a flexible array
                // if the basic type is a pointer (like a function pointer),
                // store it as well as a void *
                if ( isArray || isPointer )
                {
                    paramsStruct += "    void * " + name;
                }
                else
                {
                    paramsStruct += "    " + canonParmPrefix + " " + name;
                    if ( canonParmSuffix.size() > 0 )
                    {
                        paramsStruct += canonParmSuffix;
                    }
                }
                paramsStruct += ";\n";

                // update struct matchers list
                matchersStruct += "    OPMOCK_MATCHER match_" + name + ";\n";

                // update matcher list
                matchersStart += ", OPMOCK_MATCHER match_" + name;

                // update list of parameters assignment in a mock
                assignList += "    " + fname + "_struct_inst.calls["
                              + fname + "_struct_inst.expectedCalls]."
                              + name + " = (";
                std::string parm_no_const;
                if ( isArray || isPointer )
                {
                    parm_no_const = "void *";
                }
                else
                {
                    parm_no_const = canonParmPrefix + canonParmSuffix;
                }
                replaceAll ( parm_no_const, "const", "" );
                replaceAll ( parm_no_const, "volatile", "" );
                assignList += parm_no_const;
                assignList += ")" + name + ";\n";

                // update list of matchers assignment in a mock
                matchersAssignList += "    " + fname + "_struct_inst.calls["
                                      + fname + "_struct_inst.expectedCalls].match_"
                                      + name + " = match_" + name + ";\n";


            }

            // output the call struct
            // remove any const from the attributes
            outc << "typedef struct\n{\n";
            std::string pattern = "const";
            std::string replaceBy = "";
            replaceAll ( paramsStruct, pattern, replaceBy );
            pattern = "volatile";
            replaceAll ( paramsStruct, pattern, replaceBy );

            outc << paramsStruct;
            outc << matchersStruct;

            // return value if there's one, with *canonical* type
            if ( !isVoid )
            {
                // if the return value is const, I need to remove the "constness"
                std::string retPrefixNoConst = canonRetPrefix;
                replaceAll ( retPrefixNoConst, "const", "" );
                replaceAll ( retPrefixNoConst, "volatile", "" );

                outc << "    " << retPrefixNoConst << " to_return";
                if ( canonRetSuffix.size() > 0 )
                {
                    outc << " " << canonRetSuffix;
                }
                outc << ";\n";
            }

            outc << "    char check_params;\n";
            outc << "} " << fname << "_call;\n\n";

            // struct for the call stack
            outc << "typedef struct\n{\n";
            outc << "    int expectedCalls;\n";
            outc << "    int actualCalls;\n";
            outc << "    OPMOCK_" << fname << "_CALLBACK callback;\n";
            outc << "    " << fname << "_call calls[MAX_FUNC_CALL];\n";
            outc << "} " << fname << "_struct;\n\n";

            // static struct array for calls
            outc << "static " << fname << "_struct " << fname << "_struct_inst;\n\n";

            /*
             * functions bodies
             */

            // function to reset all mocks in this header
            reset_all_body += "    " + fname + "_MockReset();\n";

            // function to verify all mocks in this header
            verify_all_body += "    " + fname + "_VerifyMock();\n";

            // mock implementation
            std::string signature;
            signature = retPrefix + " " + fname + paramsStart + ")" + retSuffix;
            bodies_string += signature + "\n{\n";

            if ( !isVoid )
            {
                bodies_string += "    " + retPrefix + " default_res";
                if ( retSuffix.size() > 0 )
                {
                    bodies_string += " ";
                }
                bodies_string += retSuffix + " = ";
                // if the return value is const, I need to cast in const the stored
                // return value, otherwise compiler warning
                bodies_string += "(" + retPrefix + retSuffix + ")";
                bodies_string += fname + "_struct_inst.calls[0].to_return;\n";
            }

            bodies_string += "    int opmock_i;\n";
            bodies_string += "    " + fname + "_struct_inst.actualCalls++;\n\n";

            bodies_string += "    if (" + fname + "_struct_inst.callback != NULL)\n";
            bodies_string += "    {\n";
            bodies_string += "        ";

            if ( !isVoid )
            {
                bodies_string += "return ";
            }
            bodies_string += fname + "_struct_inst.callback (";
            bodies_string += paramsNames;
            if ( nbParam > 0 )
            {
                bodies_string += ", ";
            }
            bodies_string += fname + "_struct_inst.actualCalls);\n";
            if ( isVoid )
            {
                bodies_string += "        return;\n";
            }
            bodies_string += "    }\n";

            // expected calls
            bodies_string += "    if (" + fname + "_struct_inst.expectedCalls == 0)\n";
            bodies_string += "    {\n";
            bodies_string += "        opmock_add_error_message((char *) \"WARNING : unexpected call of '" + fname + "', returning random value.\");\n";
            if ( !isVoid )
            {
                bodies_string += "        return default_res;\n";
            }
            else
            {
                bodies_string += "        return;\n";
            }

            bodies_string += "    }\n\n";

            bodies_string += "    if(strcmp(opmock_get_current_call(), \"" +
                             retPrefix + " " + fname + " " + paramsStart
                             + ")" + retSuffix + "\") != 0) {\n";
            bodies_string += "        char buffer[OP_ERROR_MESSAGE_LENGTH];\n";
            bodies_string += "        snprintf(buffer, OP_ERROR_MESSAGE_LENGTH, \"WARNING : got call to '"
                             + retPrefix + " " + fname
                             + paramsStart + ")" + retSuffix
                             + "',  but was expecting call to '%s'\", opmock_get_current_call());\n";
            bodies_string += "        opmock_add_error_message(buffer);\n";
            bodies_string += "    }\n";
            bodies_string += "    opmock_pop_call();\n\n";

            bodies_string += "    if (" + fname + "_struct_inst.calls[0].check_params == 1) {\n";
            bodies_string += matchersList;
            bodies_string += "    }\n\n";

            bodies_string += "    for(opmock_i = 1; opmock_i < " + fname
                             + "_struct_inst.expectedCalls; opmock_i++) {\n";
            bodies_string += "        " + fname + "_struct_inst.calls[opmock_i - 1] = "
                             + fname + "_struct_inst.calls[opmock_i];\n";
            bodies_string += "    }\n\n";

            bodies_string += "    " + fname + "_struct_inst.expectedCalls--;\n";
            if ( !isVoid )
            {
                bodies_string += "    return default_res;\n";
            }
            bodies_string += "}\n\n";

            // mock reset implementation
            bodies_string += "void " + fname + "_MockReset()\n{\n";
            bodies_string += "    " + fname + "_struct_inst.expectedCalls = 0;\n";
            bodies_string += "    " + fname + "_struct_inst.actualCalls = 0;\n";
            bodies_string += "    " + fname + "_struct_inst.callback = NULL;\n";
            bodies_string += "}\n\n";

            // mock callback implementation
            bodies_string += "void " + fname + "_MockWithCallback(OPMOCK_" + fname +
                             "_CALLBACK callback)\n{\n";
            bodies_string += "    opmock_add_reset_callback(opmock_reset_all_mocks_in_this_header);\n";
            bodies_string += "    opmock_add_verify_callback(opmock_verify_all_mocks_in_this_header);\n";
            bodies_string += "    " + fname + "_struct_inst.callback = callback;\n";
            bodies_string += "    " + fname + "_struct_inst.expectedCalls = 0;\n";
            bodies_string += "    " + fname + "_struct_inst.actualCalls = 0;\n";
            bodies_string += "}\n\n";

            // mock verify implementation
            bodies_string += "void " + fname + "_VerifyMock()\n{\n";
            bodies_string += "    if (" + fname + "_struct_inst.expectedCalls != 0) {\n";
            bodies_string += "        char buffer[OP_ERROR_MESSAGE_LENGTH];\n";
            bodies_string += "        snprintf(buffer, OP_ERROR_MESSAGE_LENGTH, \"WARNING : Bad number of calls (%d) for '"
                             + fname + "'\"," + fname + "_struct_inst.actualCalls);\n";
            bodies_string += "        opmock_add_error_message((char *) buffer);\n";
            bodies_string += "    }\n";
            bodies_string += "}\n\n";

            // mock expect and return implementation
            bodies_string += "void " + fname + "_ExpectAndReturn " + paramsStart;
            if ( !isVoid )
            {
                if ( nbParam > 0 )
                {
                    bodies_string += ", ";
                }
                bodies_string += retPrefix + " to_return";
                if ( retSuffix.size() > 0 )
                {
                    bodies_string += " " + retSuffix;
                }
            }
            if ( nbParam > 0 )
            {
                bodies_string += matchersStart;
            }

            bodies_string += ")\n{\n";
            bodies_string += "    if(" + fname + "_struct_inst.callback != NULL)\n";
            bodies_string += "    {\n";
            bodies_string += "        " + fname + "_MockReset ();\n";
            bodies_string += "    }\n\n";

            bodies_string += "    if("
                             + fname + "_struct_inst.expectedCalls >= MAX_FUNC_CALL)\n";
            bodies_string += "    {\n";
            bodies_string += "        printf(\"WARNING : aborting "
                             + fname + "_ExpectAndReturn, call stack overload.\");\n";
            bodies_string += "        return;\n";
            bodies_string += "    }\n\n";

            bodies_string += "    opmock_add_reset_callback(opmock_reset_all_mocks_in_this_header);\n";
            bodies_string += "    opmock_add_verify_callback(opmock_verify_all_mocks_in_this_header);\n";
            bodies_string += "    opmock_add_call((char *)\""
                             + retPrefix + " " + fname + " " + paramsStart + ")" + retSuffix + "\");\n";

            // copy parameters
            bodies_string += assignList;

            // copy matcher pointers
            bodies_string += matchersAssignList;

            // return value
            if ( !isVoid )
            {
                bodies_string += "    " + fname + "_struct_inst.calls["
                                 + fname + "_struct_inst.expectedCalls].to_return = ";
                bodies_string += "(";
                std::string cast_string = canonRetPrefix + canonRetSuffix;
                replaceAll ( cast_string, "const", "" );
                replaceAll ( cast_string, "volatile", "" );
                bodies_string += cast_string;
                bodies_string += ") to_return;\n";
            }

            bodies_string += "    " + fname + "_struct_inst.calls["
                             + fname + "_struct_inst.expectedCalls].check_params = 1;\n";
            bodies_string += "    " + fname + "_struct_inst.expectedCalls++;\n";
            bodies_string += "}\n\n";


            /*
             * header output
             */

            // output expect and return function in the header
            hout << "void" << " " << fname << "_ExpectAndReturn";

            hout << paramsStart;

            // return value if there's one
            // if the return value is a function pointer there's
            // additional trickery
            if ( isFuncPtr )
            {
                if ( nbParam > 0 )
                {
                    hout << ", ";
                }
                hout << retPrefix << " to_return " << retSuffix;
            }
            else if ( retPrefix != "void" )
            {
                if ( nbParam > 0 )
                {
                    hout << ", ";
                }
                hout << retPrefix << " to_return";
            }

            // matchers
            hout << matchersStart;

            hout << ")";
            hout << ";" << std::endl;

            // output reset function
            hout << "void " << fname << "_MockReset();\n";

            // output callback typedef
            hout << "typedef " << retPrefix << " (* OPMOCK_" << fname << "_CALLBACK)" << paramsStart;
            if ( nbParam > 0 )
            {
                hout << ", ";
            }
            hout << "int calls)" << retSuffix;
            hout << ";\n";

            // output callback prototype
            hout << "void " << fname << "_MockWithCallback(OPMOCK_" << fname << "_CALLBACK callback);\n";

            // output verify function
            hout << "void " << fname << "_VerifyMock();\n";
        }
    }

    hout << "\n#ifdef __cplusplus\n";
    hout << "}\n#endif\n#endif\n";

    hout.close();

    if ( nb_func > 0 )
    {
        outc << reset_all_body << "}\n\n";
        outc << verify_all_body << "}\n\n";
    }
    outc << bodies_string;

    outc.close();

}

std::string SplitFilename ( const std::string &str )
{
    size_t found;
    found = str.find_last_of ( "/\\" );
    return str.substr ( found + 1 );
}

std::string SplitPath ( const std::string &str )
{
    size_t found;
    found = str.find_last_of ( "/\\" );
    return str.substr ( 0, found );
}

std::string removeExt ( std::string &str )
{
    size_t found;
    found = str.find_last_of ( "." );
    return str.substr ( 0, found );
}

void cleanPath ( std::string &str )
{
    //check if the path ends with a path separator
    //if not add it
    if ( str[str.length() - 1] != PATH_SEP )
    {
        str.append ( PATH_SEP_S );
    }
}

bool isParmArray ( clang::ParmVarDecl *pdecl )
{
    clang::QualType parmType = pdecl->getOriginalType();
    const clang::Type *realType = parmType.getTypePtrOrNull();

    if ( realType->isArrayType() )
    {
        return true;
    }
    return false;
}

bool isParmPointer ( clang::ParmVarDecl *pdecl )
{
    clang::QualType parmType = pdecl->getOriginalType();
    const clang::Type *realType = parmType.getTypePtrOrNull();

    if ( realType->isPointerType() )
    {
        return true;
    }
    return false;
}

void paramAsString ( clang::ParmVarDecl *pdecl, std::string &prefix, std::string &suffix,
                     bool useCanonical )
{
    clang::QualType parmType = pdecl->getOriginalType();
    std::string sparmType = parmType.getAsString();

    if ( useCanonical )
    {
        clang::QualType canonParmtype = parmType.getCanonicalType();
        sparmType = canonParmtype.getAsString();
    }
    replaceAll ( sparmType, "class ", "" );

    const clang::Type *realType = parmType.getTypePtrOrNull();

    if ( realType->isArrayType() )
    {
        size_t found;
        found = sparmType.find ( "[" );
        if ( found != std::string::npos )
        {
            prefix = sparmType.substr ( 0, found );
            suffix = sparmType.substr ( found, sparmType.size() - 1 );
        }
        else
        {
            prefix = sparmType;//meaning there's a typedef
            suffix = "";
        }
    }
    else if ( realType->isFunctionPointerType() )
    {
        size_t found;
        found = sparmType.find ( "(*)" );
        if ( found != std::string::npos )
        {
            prefix = sparmType.substr ( 0, found + 2 );
            suffix = sparmType.substr ( found + 2, sparmType.size() - 1 );
        }
        else
        {
            prefix = sparmType;
            suffix = "";
        }
    }
    else
    {
        prefix = sparmType;
        suffix = "";
    }
    //FIXME there are 2 or 3 different ways to extract parameters in this code
    // should refactor to use a single path
    replaceAll ( prefix, "_Bool", "bool" );
    replaceAll ( suffix, "_Bool", "bool" );
}

void returnValueLR ( clang::FunctionDecl *fdecl,
                     std::string &prefix,
                     std::string &suffix )
{
    clang::QualType retqualType = fdecl->getReturnType();
    clang::QualType qtype = retqualType.getCanonicalType();
    std::string canonParmType = qtype.getAsString();

    const clang::Type *realType = qtype.getTypePtrOrNull();
    if ( realType->isFunctionPointerType() )
    {
        size_t found;
        found = canonParmType.find ( "(*)" );
        prefix = canonParmType.substr ( 0, found + 2 );
        suffix = canonParmType.substr ( found + 2, canonParmType.size() - 1 );
    }
    else
    {
        prefix = canonParmType;
        suffix = "";
    }
    // make sure we don't return a _Bool type
    replaceAll ( prefix, "_Bool", "bool" );
    replaceAll ( suffix, "_Bool", "bool" );
}

bool returnValueAsAString ( clang::FunctionDecl *fdecl, std::string &retPrefix,
                            std::string &retSuffix, bool useCanonical )
{
    bool result = false;

    clang::QualType retqualType = fdecl->getReturnType();
    std::string sparmType = retqualType.getAsString();

    if ( useCanonical )
    {
        clang::QualType qtype = retqualType.getCanonicalType();
        std::string canonParmType = qtype.getAsString();
        sparmType = canonParmType;
    }

    // I don't see in clang API how to know if the return value
    // is a function pointer. TODO use the actual clang::Type to know if this is a pointer
    size_t found;
    found = sparmType.find ( "(*)" );
    if ( found != std::string::npos )
    {
        retPrefix = sparmType.substr ( 0, found + 2 );
        retSuffix = sparmType.substr ( found + 2, sparmType.size() - 1 );
        result = true;
    }
    else
    {
        retPrefix = sparmType;
        retSuffix = "";
    }
    return result;
}

void replaceAll ( std::string &str, const std::string &from, const std::string &to )
{
    if ( from.empty() )
        return;
    size_t start_pos = 0;
    while ( ( start_pos = str.find ( from, start_pos ) ) != std::string::npos )
    {
        str.replace ( start_pos, from.length(), to );
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

bool isFunctionVoid ( clang::FunctionDecl *f )
{
    clang::QualType retType = f->getReturnType();

    const clang::Type *realType = retType.getTypePtrOrNull();
    if ( realType->isVoidType() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void writeFilesForCpp ( std::vector<clang::FunctionDecl *> functionList,
                        std::vector<clang::CXXRecordDecl *> recordList,
                        std::vector<clang::NamedDecl *> declList,
                        std::string &output, std::string &input_file,
                        std::string prefix, bool useQuotes,
                        std::string &funcToSkip, std::string &funcToKeep )
{
    // split the functions to keep and the functions to skip
    std::vector<std::string> toKeep;
    std::vector<std::string> toSkip;

    std::vector<clang::FunctionDecl *> keepFunctionList;
    if ( funcToKeep.size() > 0 )
    {
        tokenizeString ( funcToKeep, toKeep, "," );
    }
    std::vector<clang::FunctionDecl *> skipFunctionList;
    if ( funcToSkip.size() > 0 )
    {
        tokenizeString ( funcToSkip, toSkip, "," );
    }

    // the key is a string. Associated to a vector of vectors of strings (the split namespaces)
    typedef std::map< std::string, NameMap * > MyMapType;
    MyMapType nsMap;

    for ( std::vector<clang::NamedDecl *>::iterator it = declList.begin();
            it != declList.end(); ++it )
    {
        clang::NamedDecl *one_decl = *it;

        // split namespaces
        std::vector<std::string> ns;
        tokenizeString ( one_decl->getQualifiedNameAsString(), ns, ":" );

        std::string nameNoScope = ns[ns.size() - 1];

        // see if I need to insert this entry in the map or if
        // it's already in
        if ( nsMap.count ( nameNoScope ) == 0 )
        {
            NameMap *nmap = new NameMap();
            nmap->nsList.push_back ( ns );
            nsMap.insert ( nsMap.begin(), MyMapType::value_type ( nameNoScope, nmap ) );

        }
        else
        {
            MyMapType::iterator itkey;
            itkey = nsMap.find ( nameNoScope );
            itkey->second->nsList.push_back ( ns );
        }
    }

    std::string cppfile, hppfile, startHeader;
    startHeaderFile ( output, input_file, prefix, useQuotes, true,
                      cppfile, hppfile, startHeader );
    std::ofstream hout;
    hout.open ( hppfile.c_str() );
    hout << startHeader;

    std::vector<OpFunction *> opFunctions;
    std::vector<OpRecord *> opRecords;
    std::map<std::string, int> overloadMap;

    //  extract functions informations
    // functions are already filtered at that point
    for ( std::vector<clang::FunctionDecl *>::iterator it = functionList.begin();
            it != functionList.end(); ++it )
    {
        OpFunction *new_func = extractFunction ( *it, overloadMap, nsMap );
        if ( new_func )
        {
            opFunctions.push_back ( new_func );
        }
    }

    // extract class informations (and their methods)
    for ( std::vector<clang::CXXRecordDecl *>::iterator it = recordList.begin();
            it != recordList.end(); ++it )
    {
        clang::CXXRecordDecl *one_rec = *it;

        // I shall create a new record only if it has at least one method
        // otherwise there's nothing to mock
        OpRecord *new_rec = new OpRecord();
        new_rec->name = one_rec->getNameAsString();
        new_rec->qualifiedName = one_rec->getQualifiedNameAsString();
        std::vector<std::string> namespaces;
        tokenizeString ( new_rec->qualifiedName, namespaces, ":" );
        namespaces.pop_back();
        new_rec->ns = namespaces;
        // is it a struct?
        if ( one_rec->isStruct() )
        {
            new_rec->isStruct = true;
        }
        //is it a template class?
        clang::ClassTemplateDecl *templateDecl = one_rec->getDescribedClassTemplate();
        if ( templateDecl )
        {
            new_rec->isTemplate = true;
        }

        // use a map to separate method overloads in the scope
        // of a class
        std::map<std::string, int> mOverloadMap;
        for ( clang::CXXRecordDecl::method_iterator it2 = one_rec->method_begin();
                it2 != one_rec->method_end(); ++it2 )
        {
            OpFunction *new_func = extractFunction ( *it2, mOverloadMap, nsMap );
            if ( new_func )
            {
                // filter variadic methods
                // TODO don't filter variadics. Instead write mock code
                // that does not store parameters and callbacks
                // meaning that we just store the return value and we don't use
                // any matchers. If matchers are assigned they will just be ignored
                // (or maybe only on fixed parameters?)
                if(new_func->isVariadic)
                {
                    std::cout << "Filtering method " << new_func->qualifiedName << " as it is variadic\n";
                    delete new_func;
                }
                else if(new_func->isInlined)
                {
                    std::cout << "Filtering method " << new_func->qualifiedName << " as it is inlined\n";
                    delete new_func;
                }

                else
                {
                    new_rec->methods.push_back ( new_func );
                }
            }
        }

        // filter methods
        if ( toSkip.size() > 0 )
        {
            for ( std::vector<std::string>::iterator it1 = toSkip.begin();
                    it1 != toSkip.end(); ++it1 )
            {
                std::string toCompare = *it1;

                for ( std::vector<OpFunction *>::iterator it2 = new_rec->methods.begin();
                        it2 != new_rec->methods.end(); ++it2 )
                {
                    std::string fname = ( *it2 )->qualifiedName;
                    if ( fname.compare ( toCompare ) == 0 )
                    {
                        std::cout << "Skipping method " << fname <<
                                  " because it is in the exclusion list." << std::endl;
                        it2 = new_rec->methods.erase ( it2 );
                    }
                }
            }
        }
        else if ( toKeep.size() > 0 )
        {
            std::vector<OpFunction *> methodsToKeep;

            for ( std::vector<std::string>::iterator it1 = toKeep.begin();
                    it1 != toKeep.end(); ++it1 )
            {
                std::string toCompare = *it1;

                for ( std::vector<OpFunction *>::iterator it2 = new_rec->methods.begin();
                        it2 != new_rec->methods.end(); ++it2 )
                {
                    std::string fname = ( *it2 )->qualifiedName;
                    if ( fname.compare ( toCompare ) == 0 )
                    {
                        std::cout << "Keeping method " << fname <<
                                  " because it is in the keep list." << std::endl;
                        methodsToKeep.push_back(*it2);
                    }
                }
            }
            if(methodsToKeep.size() > 0)
            {
                new_rec->methods.clear();
                new_rec->methods = methodsToKeep;
            }
        }


        // don't generate code for the class if it does not contain any method
        if ( new_rec->methods.size() == 0 )
        {
            delete new_rec;
        }
        else
        {
            opRecords.push_back ( new_rec );
        }
    }


    // output the header file
    // for free functions (outside of a class or struct)
    // TODO write output functions reused for both C and C++
    for ( std::vector<OpFunction *>::iterator it = opFunctions.begin();
            it != opFunctions.end(); ++it )
    {
        OpFunction *one_func = *it;
        if ( ( one_func->isTemplate == false ) && ( one_func->isOperatorOverload == false ) )
        {
            std::string ns_left;
            std::string ns_right;
            if ( one_func->ns.size() > 0 )
            {
                for ( unsigned i = 0; i < one_func->ns.size(); i++ )
                {
                    ns_left += "namespace " + one_func->ns[i] + " { ";
                    ns_right += " }";
                }
            }
            // expect and return overloads can be told appart with their parameters
            hout << ns_left << "void" << " " << one_func->name << "_ExpectAndReturn (";
            // parameters
            for ( unsigned i = 0; i < one_func->parameters.size(); i++ )
            {
                OpParameter *one_param = one_func->parameters[i];
                hout << one_param->orgTypeL << " " << one_param->name
                     << " " << one_param->orgTypeR;
                if ( i < one_func->parameters.size() - 1 )
                {
                    hout << ", ";
                }
            }

            // return value
            if ( !one_func->returnsVoid )
            {
                if ( one_func->parameters.size() > 0 )
                {
                    hout << ", ";
                }
                hout << one_func->retSignatureLeft << " to_return";
                hout << one_func->retSignatureRight;
            }

            // matchers
            if ( one_func->parameters.size() > 0 )
            {
                for ( unsigned i = 0; i < one_func->parameters.size(); i++ )
                {
                    OpParameter *one_param = one_func->parameters[i];
                    hout << ", OPMOCK_MATCHER match_" << one_param->name;
                }

            }
            hout << ");" << ns_right << std::endl;

            // function MockReset
            hout << ns_left << "void " << one_func->name;
            if ( one_func->overloads > 1 )
            {
                hout << one_func->overloads - 1;
            }
            hout << "_MockReset();" << ns_right << std::endl;

            // callback typedef
            hout << "typedef " << one_func->retSignatureLeft;
            hout << " (* OPMOCK_";
            std::string fqname = one_func->qualifiedName;
            std::replace ( fqname.begin(), fqname.end(), ':', '_' );
            hout << fqname;
            if ( one_func->overloads > 1 )
            {
                hout << one_func->overloads - 1;
            }
            hout << "_CALLBACK)(";
            // parameters for the typedef
            for ( unsigned i = 0; i < one_func->parameters.size(); i++ )
            {
                OpParameter *one_param = one_func->parameters[i];
                hout << one_param->orgTypeL << " " << one_param->name
                     << " " << one_param->orgTypeR;
                if ( i < one_func->parameters.size() - 1 )
                {
                    hout << ", ";
                }
            }
            if ( one_func->parameters.size() > 0 )
            {
                hout << ", ";
            }
            hout << "int calls)";
            hout << one_func->retSignatureRight << ";" << "\n";

            // the callback itself
            hout << ns_left << "void" << " " << one_func->name;
            hout << "_MockWithCallback(OPMOCK_";
            hout << fqname;
            if ( one_func->overloads > 1 )
            {
                hout << one_func->overloads - 1;
            }

            hout << "_CALLBACK);" << ns_right << std::endl;

            // VerifyMock functs
            hout << ns_left << "void " << one_func->name;
            if ( one_func->overloads > 1 )
            {
                hout << one_func->overloads - 1;
            }
            hout << "_VerifyMock();" << ns_right << std::endl;
        }
    }


    // output forward declarations for classes
    hout << std::endl;
    for ( std::vector<OpRecord *>::iterator it = opRecords.begin();
            it != opRecords.end(); ++it )
    {
        OpRecord *one_rec = *it;

        if ( one_rec->isTemplate == false )
        {
            std::string ns_left;
            std::string ns_right;
            if ( one_rec->ns.size() > 0 )
            {
                for ( unsigned i = 0; i < one_rec->ns.size(); i++ )
                {
                    ns_left += "namespace " + one_rec->ns[i] + " { ";
                    ns_right += " }";
                }
            }
            hout << ns_left;
            if ( one_rec->isStruct )
            {
                hout << "struct ";
            }
            else
            {
                hout << "class ";
            }
            hout << one_rec->name << "_Mock;" << ns_right << std::endl;
        }
    }

    // output callback declarations for class methods
    hout << std::endl;
    for ( std::vector<OpRecord *>::iterator it = opRecords.begin();
            it != opRecords.end(); ++it )
    {
        // compute scope for the class/struct
        OpRecord *one_rec = *it;
        if ( !one_rec->isTemplate )
        {
            std::string nsf_left;
            std::string nsf_right;
            if ( one_rec->ns.size() > 0 )
            {
                for ( unsigned i = 0; i < one_rec->ns.size(); i++ )
                {
                    nsf_left += "namespace " + one_rec->ns[i] + " { ";
                    nsf_right += " }";
                }
            }

            for ( std::vector<OpFunction *>::iterator itr = one_rec->methods.begin();
                    itr != one_rec->methods.end(); ++itr )
            {
                OpFunction *one_func = *itr;

                bool shouldGenerate = true;

                if (one_func->isOperatorOverload == true)
                    shouldGenerate = false;

                // don't generate any mock code for constructors/destructors
                // only a basic body will be generated for the base class
                // Typically mocking constructors/destructors does not have any sense,
                // as there's no return value and side effects may be mocked as well.
                if (one_func->isConstructor == true)
                {
                    shouldGenerate = false;
                }
                
                if (one_func->isDestructor == true)
                {
                    shouldGenerate = false;
                }

                if(shouldGenerate == true)
                {
                    std::string ns_left;
                    std::string ns_right;
                    if ( one_func->ns.size() > 0 )
                    {
                        for ( unsigned i = 0; i < one_func->ns.size(); i++ )
                        {
                            ns_left += "namespace " + one_func->ns[i] + " { ";
                            ns_right += " }";
                        }
                    }

                    //TODO refactor this same for function
                    //hout << nsf_left;
                    hout << "typedef " << one_func->retSignatureLeft;
                    hout << " (* OPMOCK_";
                    std::string fqname = one_func->qualifiedName;
                    std::replace ( fqname.begin(), fqname.end(), ':', '_' );
                    hout << fqname;
                    if ( one_func->overloads > 1 )
                    {
                        hout << one_func->overloads - 1;
                    }
                    hout << "_CALLBACK)(";
                    // parameters for the typedef
                    for ( unsigned i = 0; i < one_func->parameters.size(); i++ )
                    {
                        OpParameter *one_param = one_func->parameters[i];
                        hout << one_param->orgTypeL << " " << one_param->name
                             << " " << one_param->orgTypeR;
                        if ( i < one_func->parameters.size() - 1 )
                        {
                            hout << ", ";
                        }
                    }
                    if ( one_func->parameters.size() > 0 )
                    {
                        hout << ", ";
                    }
                    hout << "int calls)";
                    hout << one_func->retSignatureRight << ";" /*<< nsf_right*/ << "\n";

                    // same for version with inst but normally
                    //only if the function is not static
                    //TODO refactor as well
                    if ( !one_func->isStatic )
                    {
                        /*hout << nsf_left;*/
                        hout << "typedef " << one_func->retSignatureLeft;
                        hout << " (* OPMOCK_";
                        std::string fqname2 = one_func->qualifiedName;
                        std::replace ( fqname2.begin(), fqname2.end(), ':', '_' );
                        hout << fqname2;
                        if ( one_func->overloads > 1 )
                        {
                            hout << one_func->overloads - 1;
                        }
                        hout << "_INST_CALLBACK)(";
                        // parameters for the typedef
                        for ( unsigned i = 0; i < one_func->parameters.size(); i++ )
                        {
                            OpParameter *one_param = one_func->parameters[i];
                            hout << one_param->orgTypeL << " " << one_param->name
                                 << " " << one_param->orgTypeR;
                            if ( i < one_func->parameters.size() - 1 )
                            {
                                hout << ", ";
                            }
                        }
                        if ( one_func->parameters.size() > 0 )
                        {
                            hout << ", ";
                        }
                        hout << "int calls, ";
                        hout << one_rec->qualifiedName << " * cb_ptr)";
                        hout << one_func->retSignatureRight << ";" /*<< nsf_right*/ << "\n";
                    }
                }
            }

            // output the mock class with its list of operations
            hout << std::endl;

            std::string ns_left;
            std::string ns_right;
            if ( one_rec->ns.size() > 0 )
            {
                for ( unsigned i = 0; i < one_rec->ns.size(); i++ )
                {
                    ns_left += "namespace " + one_rec->ns[i] + " {\n";
                    ns_right += "}\n";
                }
            }
            hout << ns_left;
            if ( one_rec->isStruct )
            {
                hout << "struct ";
            }
            else
            {
                hout << "class ";
            }
            hout << one_rec->name << "_Mock\n{\n";
            hout << "    public:\n";
            hout << "    static void MockReset();\n";
            hout << "    static void VerifyMock();\n";

            for ( std::vector<OpFunction *>::iterator itm = one_rec->methods.begin();
                    itm != one_rec->methods.end(); ++itm )
            {
                OpFunction *one_func = *itm;

                if ( ( one_func->isConstructor == false ) && ( one_func->isDestructor == false )
                        && ( one_func->isOperatorOverload == false ) &&
                        ( one_func->isTemplate == false ) )
                {
                    hout << "    static void " << one_func->name;
                    if ( one_func->overloads > 1 )
                    {
                        hout << one_func->overloads - 1;
                    }
                    hout << "_MockReset();\n";

                    hout << "    static void " << one_func->name;
                    if ( one_func->overloads > 1 )
                    {
                        hout << one_func->overloads - 1;
                    }
                    hout << "_VerifyMock();\n";

                    //TODO fonction pour ecrire callback typedef, avec
                    //ou sans inst
                    hout << "    static void " << one_func->name << "_MockWithCallback(";
                    hout << "OPMOCK_";
                    std::string fqname = one_func->qualifiedName;
                    std::replace ( fqname.begin(), fqname.end(), ':', '_' );
                    hout << fqname;
                    if ( one_func->overloads > 1 )
                    {
                        hout << one_func->overloads - 1;
                    }
                    hout << "_CALLBACK callback);\n";

                    if ( !one_func->isStatic )
                    {
                        hout << "    static void " << one_func->name << "_MockWithInstanceCallback(";

                        hout << "OPMOCK_";
                        std::string fqname = one_func->qualifiedName;
                        std::replace ( fqname.begin(), fqname.end(), ':', '_' );
                        hout << fqname;
                        if ( one_func->overloads > 1 )
                        {
                            hout << one_func->overloads - 1;
                        }
                        hout << "_INST_CALLBACK callback);\n";
                    }

                    // expect and return
                    //TODO factoriser!
                    hout << "    static void " << one_func->name << "_ExpectAndReturn(";
                    // parameters
                    for ( unsigned i = 0; i < one_func->parameters.size(); i++ )
                    {
                        OpParameter *one_param = one_func->parameters[i];
                        hout << one_param->orgTypeL << " " << one_param->name
                             << " " << one_param->orgTypeR;
                        if ( i < one_func->parameters.size() - 1 )
                        {
                            hout << ", ";
                        }
                    }

                    // return value
                    if ( !one_func->returnsVoid )
                    {
                        if ( one_func->parameters.size() > 0 )
                        {
                            hout << ", ";
                        }
                        hout << one_func->retSignatureLeft << " to_return";
                        hout << one_func->retSignatureRight;
                    }

                    // matchers
                    if ( one_func->parameters.size() > 0 )
                    {
                        for ( unsigned i = 0; i < one_func->parameters.size(); i++ )
                        {
                            OpParameter *one_param = one_func->parameters[i];
                            hout << ", OPMOCK_MATCHER match_" << one_param->name;
                        }
                    }
                    hout << ");\n";
                }
            }
            hout << "};\n";
            hout << ns_right << std::endl;
        }
    }

    hout << "#endif\n";
    hout.close();

    // C++ body output
    std::ofstream outc;
    outc.open ( cppfile.c_str() );
    outc << "/* OPMOCK2 GENERATED CODE - DO NOT MODIFY */\n";
    std::string filename = SplitFilename ( input_file );
    outc << "#include \"" << removeExt ( filename ) + "_stub.hpp" << "\"\n";
    outc << "#include <stdio.h>\n";
    outc << "#include <string.h>\n\n";

    // structs for free functions
    for ( std::vector<OpFunction *>::iterator it = opFunctions.begin();
            it != opFunctions.end(); ++it )
    {
        writeFunctionStruct ( *it, NULL, outc );
    }

    // structs for C++ methods
    for ( std::vector<OpRecord *>::iterator it = opRecords.begin();
            it != opRecords.end(); ++it )
    {
        OpRecord *one_rec = *it;
        for ( std::vector<OpFunction *>::iterator it2 = one_rec->methods.begin();
                it2 != one_rec->methods.end(); ++it2 )
        {
            writeFunctionStruct ( *it2, one_rec, outc );
        }
    }
    outc << "\n";

    // function to reset all mocks
    // first count the number of functions or operations.
    // if none, I must not write this function otherwise it will generate
    // a warning at compilation time
    int nb_func = opFunctions.size();
    for ( std::vector<OpRecord *>::iterator it = opRecords.begin();
            it != opRecords.end(); ++it )
    {
        OpRecord *one_rec = *it;
        for ( std::vector<OpFunction *>::iterator it2 = one_rec->methods.begin();
                it2 != one_rec->methods.end(); ++it2 )
        {
            nb_func++;
        }
    }


    if ( nb_func > 0 )
    {
        outc << "static void opmock_reset_all_mocks_in_this_header()\n{\n";
        // first C style free functions
        for ( std::vector<OpFunction *>::iterator it = opFunctions.begin();
                it != opFunctions.end(); ++it )
        {
            OpFunction *one_func = *it;
            if ( ( one_func->isOperatorOverload == false ) && ( one_func->isTemplate == false ) )
            {
                outc << "    " << one_func->qualifiedName;
                if ( one_func->overloads > 1 )
                {
                    outc << one_func->overloads - 1;
                }
                outc << "_MockReset();\n";
            }
        }
        // then class operations
        for ( std::vector<OpRecord *>::iterator it = opRecords.begin();
                it != opRecords.end(); ++it )
        {
            OpRecord *one_rec = *it;
            if ( !one_rec->isTemplate )
            {
                std::string classPrefix = "    ";
                if ( one_rec->ns.size() > 0 )
                {
                    for ( unsigned i = 0; i < one_rec->ns.size(); i++ )
                    {
                        classPrefix += one_rec->ns[i];
                        classPrefix += "::";
                    }
                }
                classPrefix += one_rec->name;
                classPrefix += "_Mock::MockReset();\n";
                outc << classPrefix;
            }
        }
        outc << "}\n\n";

        // function to verify all mocks
        outc << "static void opmock_verify_all_mocks_in_this_header()\n{\n";
        // first C style free functions
        for ( std::vector<OpFunction *>::iterator it = opFunctions.begin();
                it != opFunctions.end(); ++it )
        {
            OpFunction *one_func = *it;
            if ( ( one_func->isOperatorOverload == false ) && ( one_func->isTemplate == false ) )
            {
                outc << "    " << one_func->qualifiedName;
                if ( one_func->overloads > 1 )
                {
                    outc << one_func->overloads - 1;
                }
                outc << "_VerifyMock();\n";
            }
        }
        // then class operations
        for ( std::vector<OpRecord *>::iterator it = opRecords.begin();
                it != opRecords.end(); ++it )
        {
            OpRecord *one_rec = *it;
            if ( !one_rec->isTemplate )
            {
                std::string classPrefix = "    ";
                if ( one_rec->ns.size() > 0 )
                {
                    for ( unsigned i = 0; i < one_rec->ns.size(); i++ )
                    {
                        classPrefix += one_rec->ns[i];
                        classPrefix += "::";
                    }
                }
                classPrefix += one_rec->name;
                classPrefix += "_Mock::VerifyMock();\n";
                outc << classPrefix;
            }
        }
        outc << "}\n\n";
    }

    // output bodies of C style functions
    for ( std::vector<OpFunction *>::iterator it = opFunctions.begin();
            it != opFunctions.end(); ++it )
    {
        OpFunction *one_func = *it;
        if ( ( one_func->isOperatorOverload == false ) &&
                ( one_func->isTemplate == false ) )
        {
            writeFunctionBody ( one_func, NULL, outc );
            writeFunctionMockResetBody ( one_func, NULL, outc );
            writeFunctionMockWithCallbackBody ( one_func, NULL, outc );
            writeFunctionVerifyMockBody ( one_func, NULL, outc );
            writeFunctionExpectAndReturnBody ( one_func, NULL, outc );
        }
    }

    // output bodies of C++ methods
    for ( std::vector<OpRecord *>::iterator it = opRecords.begin();
            it != opRecords.end(); ++it )
    {
        OpRecord *one_rec = *it;
        if ( !one_rec->isTemplate )
        {
            // class level verify
            outc << "void " << one_rec->qualifiedName << "_Mock::VerifyMock()\n{\n";
            for ( std::vector<OpFunction *>::iterator it2 = one_rec->methods.begin();
                    it2 != one_rec->methods.end(); ++it2 )
            {
                OpFunction *one_func = *it2;
                if ( ( one_func->isConstructor == false ) &&
                        ( one_func->isDestructor == false ) &&
                        ( one_func->isOperatorOverload == false ) &&
                        ( one_func->isTemplate == false ) )
                {
                    outc << "    " << one_rec->qualifiedName << "_Mock::"
                         << one_func->name;
                    if ( one_func->overloads > 1 )
                    {
                        outc << one_func->overloads - 1;
                    }
                    outc << "_VerifyMock();\n";
                }
            }
            outc << "}\n\n";

            // class level reset
            outc << "void " << one_rec->qualifiedName << "_Mock::MockReset()\n{\n";
            for ( std::vector<OpFunction *>::iterator it2 = one_rec->methods.begin();
                    it2 != one_rec->methods.end(); ++it2 )
            {
                OpFunction *one_func = *it2;
                if ( ( one_func->isConstructor == false ) &&
                        ( one_func->isDestructor == false ) &&
                        ( one_func->isOperatorOverload == false ) &&
                        ( one_func->isTemplate == false ) )
                {

                    outc << "    " << one_rec->qualifiedName << "_Mock::"
                         << one_func->name;
                    if ( one_func->overloads > 1 )
                    {
                        outc << one_func->overloads - 1;
                    }
                    outc << "_MockReset();\n";
                }
            }
            outc << "}\n\n";


            // list of class operations
            for ( std::vector<OpFunction *>::iterator it2 = one_rec->methods.begin();
                    it2 != one_rec->methods.end(); ++it2 )
            {
                OpFunction *one_func = *it2;

                if ( ( one_func->isConstructor == false ) &&
                        ( one_func->isDestructor == false ) &&
                        ( one_func->isOperatorOverload == false ) &&
                        ( one_func->isTemplate == false ) )
                {
                    writeFunctionBody ( one_func, one_rec, outc );
                    writeFunctionMockResetBody ( one_func, one_rec, outc );
                    writeFunctionMockWithCallbackBody ( one_func, one_rec, outc );
                    if ( !one_func->isStatic )
                    {
                        writeFunctionMockWithInstanceCallbackBody ( one_func, one_rec, outc );
                    }
                    writeFunctionVerifyMockBody ( one_func, one_rec, outc );
                    writeFunctionExpectAndReturnBody ( one_func, one_rec, outc );
                }
                // special case for constructors/destructor : write
                // versions with empty bodies
                // to be able to link
                if (one_func->isConstructor)
                {
                    writeConstructorBody(one_func, one_rec, outc);
                }
                else if (one_func->isDestructor)
                {
                    writeDestructorBody(one_func, one_rec, outc);
                }

            }
        }
    }
    outc.close();
}

OpFunction::OpFunction()
{
    this->overloads = 0;
    this->isConst = false;
    this->isStatic = false;
    this->isExtern = false;
    this->isVariadic = false;
    this->returnsVoid = false;
    this->isInlined = false;
    this->isConstructor = false;
    this->isDestructor = false;
    this->isOperatorOverload = false;
    this->isTemplate = false;
    this->isVirtual = false;
    this->isPureVirtual = false;
}

OpParameter::OpParameter()
{
    this->isReference = false;
}

std::string getStructReturnType ( clang::FunctionDecl *fdecl, bool &isReference )
{
    std::string result;
    isReference = false;

    clang::QualType retType = fdecl->getReturnType();
    clang::QualType qtype = retType.getCanonicalType();
    const clang::Type *realType = qtype.getTypePtrOrNull();

    if ( realType->isArrayType() )
    {
        result = "void *";
    }
    else if ( realType->isAnyPointerType() )
    {
        result = "void *";
    }
    else if ( realType->isReferenceType() )
    {
        result = "void *";
        isReference = true;
    }
    else
    {
        std::string parmString = qtype.getAsString();
        replaceAll ( parmString, "const", "" );
        replaceAll ( parmString, "volatile", "" );
	//clang replaces bool by _Bool for some reason - so let's turn it back to bool
        replaceAll ( parmString, "_Bool", "bool" );
        result = parmString;
    }
    return result;
}

OpParameter *splitParameter ( clang::ParmVarDecl *pdecl,
                              std::map< std::string, NameMap * > &nsmap,
                              int number )
{
    std::string pname = pdecl->getNameAsString();
    OpParameter *new_param = new OpParameter();

    // cope with anonymous parameters
    if ( pname.size() == 0 )
    {
        char argbuffer[100];
        sprintf ( argbuffer, "arg%d", number + 1 );
        pname = argbuffer;
    }

    new_param->name = pname;

    clang::QualType retType = pdecl->getOriginalType();
    std::string originalTypeS = retType.getAsString();

    //std::cout << pname << " type parametre original " << originalTypeS << std::endl;
    const clang::Type *orgType = retType.getTypePtrOrNull();
    const clang::TemplateSpecializationType *ttype = clang::dyn_cast< clang::TemplateSpecializationType> ( orgType );
    if ( ttype )
    {
       // std::cout << "argument " << pname << " est template specialisation\n";
    }



    clang::QualType qtype = retType.getCanonicalType();
    const clang::Type *realType = qtype.getTypePtrOrNull();



    const clang::TemplateSpecializationType *ttype2 = clang::dyn_cast< clang::TemplateSpecializationType> ( qtype );
    if ( ttype2 )
    {
        std::cout << "argument " << pname << " est template specialisation\n";
    }


    std::string parmString2 = qtype.getAsString();
    replaceAll ( parmString2, "class ", "" );
    replaceAll ( parmString2, "const", "" );
    replaceAll ( parmString2, "volatile", "" );
    replaceAll ( parmString2, "_Bool", "bool" );

    //std::cout << "type parametre " << parmString2 << std::endl;

    // if the parameter is a function pointer type
    // then I may need to split it in left and right part
    if ( realType->isArrayType() )
    {
        new_param->castTypeL = "void *";
    }
    else if ( realType->isAnyPointerType() )
    {
        new_param->castTypeL = "void *";
    }
    else if ( realType->isReferenceType() )
    {
        new_param->castTypeL = "void *";
        new_param->isReference = true;
    }
    else
    {
        new_param->castTypeL = parmString2;
    }

    // get original type, possibly split in 2 if function pointer
    // I use the canonical type as otherwise I can't get the fully scoped type
    // of a parameter.
    std::string prefix, suffix;
    paramAsString ( pdecl, prefix, suffix, true );
    new_param->orgTypeL = prefix;
    new_param->orgTypeR = suffix;

    return new_param;
}

OpRecord::OpRecord()
{
    this->isStruct = false;
    this->isTemplate = false;
}

OpFunction *extractFunction ( clang::FunctionDecl *fdecl,
                              std::map<std::string, int> &overloadMap,
                              std::map< std::string, NameMap * > &nsMap )
{
    OpFunction *new_func = NULL;

    // isUserProvided on constructor/destructor introduced automatically
    // by clang, but only for methods
    clang::CXXMethodDecl *mdecl = clang::dyn_cast<clang::CXXMethodDecl > ( fdecl );
    if ( mdecl )
    {
        if ( !mdecl->isUserProvided() )
            return NULL;
    }

    new_func = new OpFunction();
    new_func->name = fdecl->getNameAsString();
    new_func->qualifiedName = fdecl->getQualifiedNameAsString();

    // extract namespaces if the function has them
    std::vector<std::string> namespaces;
    tokenizeString ( new_func->qualifiedName, namespaces, ":" );
    namespaces.pop_back();
    new_func->ns = namespaces;

    // handle method overloads
    ++overloadMap[new_func->name];
    new_func->overloads = overloadMap[new_func->name];

    if ( fdecl->isVariadic() )
    {
        std::cout << "WARNING " << new_func->qualifiedName << " is variadic\n";
        new_func->isVariadic = true;
    }
    if ( fdecl->hasBody() )
    {
        std::cout << "WARNING " << new_func->qualifiedName << " is inlined\n";
        new_func->isInlined = true;
    }

    clang::CXXConstructorDecl *cdecl =
        clang::dyn_cast<clang::CXXConstructorDecl > ( fdecl );
    if ( cdecl )
    {
        new_func->isConstructor = true;
    }

    clang::CXXDestructorDecl *ddecl =
        clang::dyn_cast<clang::CXXDestructorDecl > ( fdecl );
    if ( ddecl )
    {
        new_func->isDestructor = true;
    }

    if ( fdecl->getTemplatedKind() != clang::FunctionDecl::TK_NonTemplate )
    {
        new_func->isTemplate = true;
    }

    if ( mdecl )
    {
        if ( mdecl->isOverloadedOperator() )
        {
            new_func->isOperatorOverload = true;
        }
        if ( mdecl->isStatic() )
        {
            new_func->isStatic = true;
        }
        if ( mdecl->isConst() )
        {
            new_func->isConst = true;
        }
    }

    // return value
    bool isReference;
    new_func->retStructType = getStructReturnType ( fdecl, isReference );
    std::string lval, rval;
    returnValueLR ( fdecl, lval, rval );

    new_func->retSignatureLeft = lval;
    new_func->retSignatureRight = rval;
    new_func->retIsReference = isReference;

    new_func->returnsVoid = isFunctionVoid ( fdecl );



    //std::cout << "parametres fonction " << new_func->name << std::endl;


    unsigned nbParam = fdecl->getNumParams();
    for ( unsigned i = 0; i < nbParam; i++ )
    {
        new_func->parameters.push_back ( splitParameter ( fdecl->getParamDecl ( i ), nsMap, i ) );
    }
    //TODO default value for parameters, and other nasty constructs
    return new_func;
}

void writeFunctionStruct ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out )
{
    if ( one_func->isConstructor || one_func->isDestructor || one_func->isOperatorOverload
            || one_func->isTemplate )
        return;
    if ( ( one_rec != NULL ) && ( one_rec->isTemplate ) )
        return;

    std::string overload = "";
    if ( one_func->overloads > 1 )
    {
        char buffer[100];
        sprintf ( buffer, "%d", one_func->overloads - 1 );
        overload += buffer;
    }

    out << "typedef struct\n{\n";

    // struct attributes
    for ( unsigned i = 0; i < one_func->parameters.size(); i++ )
    {
        OpParameter *one_param = one_func->parameters[i];
        out << "    " << one_param->castTypeL << " " << one_param->name
            << " " << one_param->castTypeR << ";\n";
    }
    //matchers
    for ( unsigned i = 0; i < one_func->parameters.size(); i++ )
    {
        OpParameter *one_param = one_func->parameters[i];
        out << "    OPMOCK_MATCHER match_" << one_param->name << ";\n";
    }
    //optional return value
    if ( !one_func->returnsVoid )
    {
        out << "    " << one_func->retStructType << " to_return;\n";
    }

    out << "    char check_params;\n";

    std::string fqname = one_func->qualifiedName;
    std::replace ( fqname.begin(), fqname.end(), ':', '_' );
    out << "} " << fqname << overload << "_call;\n\n";

    out << "typedef struct\n{\n";
    out << "    int expectedCalls;\n";
    out << "    int actualCalls;\n";

    out << "    " << "OPMOCK_" << fqname << overload <<
        "_CALLBACK callback;" << std::endl;
    if ( one_rec && ( !one_func->isStatic ) )
    {
        out << "    " << "OPMOCK_" << fqname << overload <<
            "_INST_CALLBACK callbackInst;" << std::endl;
    }
    out << "    " << fqname << overload << "_call calls[MAX_FUNC_CALL];\n";
    out << "} " << fqname << overload << "_struct;\n\n";

    out << "static " << fqname << overload << "_struct "
        << fqname << overload << "_struct_inst;\n\n";
}

void writeFunctionBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out )
{
    std::string struct_inst = one_func->getfixedScopedOverloadedName() + "_struct_inst";
    out << one_func->buildSignature ( one_rec );
    out << "\n{\n";

    std::string signLeft;
    if ( !one_func->returnsVoid )
    {
        // if the return value is a reference, transform it into a pointer
        signLeft = one_func->retSignatureLeft;
        if ( one_func->retIsReference )
        {
            replaceAll ( signLeft, "&", "*" );
        }

        out << "    " << signLeft << " default_res";
        if ( one_func->retSignatureRight.size() > 0 )
        {
            out << " " << one_func->retSignatureRight;
        }
        out << " = (" << signLeft << one_func->retSignatureRight << ") ";
        out << struct_inst << ".calls[0].to_return";
        out << ";\n";
    }
    out << "    int opmock_i;\n";
    out << "    " << struct_inst << ".actualCalls++;\n";

    out << "    if (" << struct_inst << ".callback != NULL)\n    {\n";
    out << "        ";
    if ( !one_func->returnsVoid )
    {
        out << "return ";
    }
    out << struct_inst << ".callback (";
    if ( one_func->parameters.size() > 0 )
    {

        /*std::cout << "taille des parametres " << one_func->parameters.size() << " pour la fonction "
                << one_func->qualifiedName << std::endl;*/

        out << one_func->buildParameterNames() << ", ";
    }
    out << struct_inst << ".actualCalls);\n";
    out << "    }\n";

    out << "    if (" << struct_inst << ".expectedCalls == 0)\n    {\n";
    out << "        opmock_add_error_message((char *) \"WARNING : unexpected call of '"
        << one_func->buildSignature ( one_rec ) << "', returning random value.\");\n";
    if ( !one_func->returnsVoid )
    {
        out << "        return ";
        if ( one_func->retIsReference )
        {
            out << "*";
        }
        out << "default_res;\n";
    }
    out << "    }\n\n";

    out << "    if(strcmp(opmock_get_current_call(), \"";
    out << one_func->buildSignature ( one_rec ) << "\") != 0) {\n";
    out << "        char buffer[OP_ERROR_MESSAGE_LENGTH];\n";
    out << "        snprintf(buffer, OP_ERROR_MESSAGE_LENGTH, \"WARNING : got call to '";
    out << one_func->buildSignature ( one_rec ) << "',  but was expecting call to '%s'\", opmock_get_current_call());\n";
    out << "        opmock_add_error_message(buffer);\n";
    out << "    }\n";
    out << "    opmock_pop_call();\n\n";

    // parameters check and the rest
    if ( one_func->parameters.size() > 0 )
    {
        out << "    if (" << struct_inst << ".calls[0].check_params == 1) {\n";
        for ( unsigned i = 0; i < one_func->parameters.size(); i++ )
        {
            OpParameter *one_param = one_func->parameters[i];
            out << "        if (" << struct_inst << ".calls[0].match_"
                << one_param->name << ") {\n";
            out << "            void * val1 = (void *) &"
                << struct_inst << ".calls[0]." << one_param->name << ";\n";
            out << "            void * val2 = (void *) &"
                << one_param->name << ";\n";
            out << "            int match_result = "
                << struct_inst << ".calls[0].match_" <<
                one_param->name << "(val1, val2, \"" <<
                one_param->name << "\", get_matcher_message());\n";
            out << "            if(match_result) {\n";
            out << "                char buffer[OP_ERROR_MESSAGE_LENGTH];\n";
            out << "                snprintf(buffer, OP_ERROR_MESSAGE_LENGTH, \"WARNING : on call number %d of '";
            out << one_func->buildSignature ( one_rec ) << "', %s\",";
            out << struct_inst << ".actualCalls, get_matcher_message());\n";
            out << "                opmock_add_error_message((char *) buffer);\n";
            out << "            }\n";
            out << "        }\n";

        }
        out << "    }\n\n";
    }

    out << "    for(opmock_i = 1; opmock_i < " << struct_inst << ".expectedCalls; opmock_i++) {\n";
    out << "        " << struct_inst << ".calls[opmock_i - 1] = "
        << struct_inst << ".calls[opmock_i];\n";
    out << "    }\n\n";
    out << "    " << struct_inst << ".expectedCalls--;\n";
    if ( !one_func->returnsVoid )
    {
        out << "    return ";
        if ( one_func->retIsReference )
        {
            out << "*";
        }
        out << "default_res;\n";
    }

    out << "}\n\n";
}

void writeFunctionMockResetBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out )
{
    std::string ovl = "";

    if ( one_func->overloads > 1 )
    {
        char buffer[10];
        sprintf ( buffer, "%d", one_func->overloads - 1 );
        ovl = buffer;
    }
    std::string structName = "    ";
    out << "void ";

    if ( one_rec )
    {
        out << one_rec->qualifiedName << "_Mock::" << one_func->name << ovl;
    }
    else
    {
        out << one_func->qualifiedName << ovl;
    }
    out << "_MockReset()\n{\n";


    if ( one_func->ns.size() > 0 )
    {
        for ( unsigned i = 0; i < one_func->ns.size(); i++ )
        {
            structName += one_func->ns[i] + "__";
        }
    }
    structName += one_func->name + ovl + "_struct_inst";

    out << structName << ".expectedCalls = 0;\n";
    out << structName << ".actualCalls = 0;\n";
    out << structName << ".callback = NULL;\n";
    if ( one_rec && ( !one_func->isStatic ) )
    {
        out << structName << ".callbackInst = NULL;\n";
    }
    out << "}\n\n";
}

void writeFunctionMockWithCallbackBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out )
{
    std::string ovl = "";

    if ( one_func->overloads > 1 )
    {
        char buffer[10];
        sprintf ( buffer, "%d", one_func->overloads - 1 );
        ovl = buffer;
    }
    std::string structName;
    out << "void ";

    if ( one_rec )
    {
        out << one_rec->qualifiedName << "_Mock::" << one_func->name;
    }
    else
    {
        out << one_func->qualifiedName;
    }

    out << "_MockWithCallback(OPMOCK_";
    std::string qname = one_func->qualifiedName;
    std::replace ( qname.begin(), qname.end(), ':', '_' );
    out << qname << ovl << "_CALLBACK callback)\n{\n";

    if ( one_func->ns.size() > 0 )
    {
        for ( unsigned i = 0; i < one_func->ns.size(); i++ )
        {
            structName += one_func->ns[i] + "__";
        }
    }
    structName += one_func->name + ovl + "_struct_inst";

    out << "    opmock_add_reset_callback(opmock_reset_all_mocks_in_this_header);\n";
    out << "    opmock_add_verify_callback(opmock_verify_all_mocks_in_this_header);\n";
    out << "    " << structName << ".callback = callback;\n";
    if ( one_rec && ( !one_func->isStatic ) )
    {
        out << "    " << structName << ".callbackInst = NULL;\n";
    }

    out << "    " << structName << ".expectedCalls = 0;\n";
    out << "    " << structName << ".actualCalls = 0;\n";
    out << "}\n\n";
}

void writeFunctionMockWithInstanceCallbackBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out )
{
    std::string ovl = "";

    if ( one_func->overloads > 1 )
    {
        char buffer[10];
        sprintf ( buffer, "%d", one_func->overloads - 1 );
        ovl = buffer;
    }
    std::string structName;
    out << "void ";

    if ( one_rec )
    {
        out << one_rec->qualifiedName << "_Mock::" << one_func->name;
    }
    else
    {
        out << one_func->qualifiedName;
    }
    out << "_MockWithInstanceCallback(OPMOCK_";
    std::string qname = one_func->qualifiedName;
    std::replace ( qname.begin(), qname.end(), ':', '_' );
    out << qname << ovl << "_INST_CALLBACK callback)\n{\n";

    if ( one_func->ns.size() > 0 )
    {
        for ( unsigned i = 0; i < one_func->ns.size(); i++ )
        {
            structName += one_func->ns[i] + "__";
        }
    }
    structName += one_func->name + ovl + "_struct_inst";

    out << "    opmock_add_reset_callback(opmock_reset_all_mocks_in_this_header);\n";
    out << "    opmock_add_verify_callback(opmock_verify_all_mocks_in_this_header);\n";
    out << "    " << structName << ".callbackInst = callback;\n";
    out << "    " << structName << ".callback = NULL;\n";
    out << "    " << structName << ".expectedCalls = 0;\n";
    out << "    " << structName << ".actualCalls = 0;\n";
    out << "}\n\n";
}

void writeFunctionVerifyMockBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out )
{
    std::string ovl = "";

    if ( one_func->overloads > 1 )
    {
        char buffer[10];
        sprintf ( buffer, "%d", one_func->overloads - 1 );
        ovl = buffer;
    }
    std::string structName;
    out << "void ";

    if ( one_rec )
    {
        out << one_rec->qualifiedName << "_Mock::" << one_func->name << ovl;
    }
    else
    {
        out << one_func->qualifiedName << ovl;
    }
    out << "_VerifyMock()\n{\n";


    if ( one_func->ns.size() > 0 )
    {
        for ( unsigned i = 0; i < one_func->ns.size(); i++ )
        {
            structName += one_func->ns[i] + "__";
        }
    }
    structName += one_func->name + ovl + "_struct_inst";

    out << "    if (" << structName << ".expectedCalls != 0) {\n";
    out << "        char buffer[OP_ERROR_MESSAGE_LENGTH];\n";
    out << "        snprintf(buffer, OP_ERROR_MESSAGE_LENGTH, \"WARNING : Bad number of calls (%d) for '";
    out << one_func->qualifiedName;
    out << "'\", " << structName << ".actualCalls);\n";
    out << "        opmock_add_error_message((char *) buffer);\n";
    out << "    }\n}\n\n";
}

void writeFunctionExpectAndReturnBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out )
{
    std::string structi = one_func->getfixedScopedOverloadedName() + "_struct_inst";

    // write the prototype of the expect and return function/method
    out << "void ";
    if ( one_rec )
    {
        out << one_rec->qualifiedName << "_Mock::" << one_func->name;
    }
    else
    {
        out << one_func->qualifiedName;
    }
    out << "_ExpectAndReturn (";
    if ( one_func->parameters.size() > 0 )
    {
        out << one_func->buildParameters();
    }
    if ( !one_func->returnsVoid )
    {
        if ( one_func->parameters.size() > 0 )
        {
            out << ", ";
        }

        out << one_func->retSignatureLeft << " to_return";
        if ( one_func->retSignatureRight.size() > 0 )
        {
            out << " " << one_func->retSignatureRight;
        }
    }
    if ( one_func->parameters.size() > 0 )
    {
        //TODO factoriser cette fonction
        for ( unsigned i = 0; i < one_func->parameters.size(); i++ )
        {
            OpParameter *one_param = one_func->parameters[i];
            out << ", OPMOCK_MATCHER match_" << one_param->name;

        }
    }
    out << ")\n{\n";


    std::string mreset;
    if ( one_rec )
    {
        mreset = one_rec->qualifiedName;
        mreset += "_Mock::";
        mreset += one_func->name;
        if ( one_func->overloads > 1 )
        {
            char buffer[10];
            sprintf ( buffer, "%d", one_func->overloads - 1 );
            mreset += buffer;
        }
        mreset += "_MockReset()";

    }

    else
    {
        mreset = one_func->qualifiedName;
        if ( one_func->overloads > 1 )
        {
            char buffer[10];
            sprintf ( buffer, "%d", one_func->overloads - 1 );
            mreset += buffer;
        }
        mreset += "_MockReset()";
    }

    out << "    if(" << structi << ".callback != NULL)\n";
    out << "    {\n";
    out << "        " << mreset << ";\n";
    out << "    }\n\n";

    if ( one_rec && ( !one_func->isStatic ) )
    {
        out << "    if(" << structi << ".callbackInst != NULL)\n";
        out << "    {\n";
        out << "        " << mreset << ";\n";
        out << "    }\n\n";

    }

    out << "    if (" << structi << ".expectedCalls >= MAX_FUNC_CALL )\n";
    out << "    {\n";
    out << "        printf (\"WARNING : aborting " << one_func->qualifiedName
        << "_ExpectAndReturn, call stack overload.\");\n";
    out << "        return;\n";
    out << "    }\n\n";

    out << "    opmock_add_reset_callback ( opmock_reset_all_mocks_in_this_header );\n";
    out << "    opmock_add_verify_callback ( opmock_verify_all_mocks_in_this_header );\n";
    out << "    opmock_add_call ( ( char * ) \""
        << one_func->buildSignature ( one_rec ) << "\" );\n";

    // record parameters
    for ( unsigned i = 0; i < one_func->parameters.size(); i++ )
    {
        OpParameter *one_param = one_func->parameters[i];
        out << "    " << structi << ".calls["
            << structi << ".expectedCalls]." << one_param->name << " = ";
        out << "(" << one_param->castTypeL << one_param->castTypeR << ")";
        if ( one_param->isReference )
        {
            out << "&";
        }
        out << one_param->name << ";\n";
        out << "    " << structi << ".calls["
            << structi << ".expectedCalls].match_" << one_param->name
            << " = match_" << one_param->name << ";\n";
    }

    // return value
    if ( !one_func->returnsVoid )
    {
        out << "    " << structi << ".calls[" << structi
            << ".expectedCalls].to_return = ";
        //out << "(" << one_param->castTypeL << one_param->castTypeR << ")";
        out << "(" << one_func->retStructType << ")";
        if ( one_func->retIsReference )
        {
            out << "&";
        }
        out << "to_return;\n";
    }
    out << "    " << structi << ".calls[" << structi
        << ".expectedCalls].check_params = 1;\n";
    out << "    " << structi << ".expectedCalls++;\n";
    out << "}\n\n";
}

std::string OpFunction::getfixedScopedOverloadedName()
{
    //FIXME si c'est une methode de classe alors il faudrait
    //couper apres la classe pour ajouter _Mock
    //par exemple un parametre supplementaire pour la classe (pointeur null ou pas)
    //si pas null alors il faut l'introduire avant le nom de la fonction
    std::string fixedName;
    if ( ns.size() > 0 )
    {
        for ( unsigned i = 0; i < ns.size(); i++ )
        {
            fixedName += ns[i] + "__";
        }
    }
    fixedName += name;

    if ( overloads > 1 )
    {
        char buffer[10];
        sprintf ( buffer, "%d", overloads - 1 );
        fixedName += buffer;
    }
    return fixedName;
}

std::string OpFunction::buildParameters()
{
    std::string result = "";
    for ( unsigned i = 0; i < parameters.size(); i++ )
    {
        OpParameter *one_param = parameters[i];
        result += one_param->orgTypeL + " " + one_param->name;
        if ( one_param->orgTypeR.size() > 0 )
        {
            result += " " + one_param->orgTypeR;
        }
        if ( i < parameters.size() - 1 )
        {
            result += ", ";
        }
    }
    return result;
}

std::string OpFunction::buildParameterNames()
{
    std::string result;
    for ( unsigned i = 0; i < parameters.size(); i++ )
    {
        OpParameter *one_param = parameters[i];
        result += one_param->name;
        if ( i < parameters.size() - 1 )
        {
            result += ", ";
        }
    }
    return result;
}

std::string OpFunction::buildSignature ( OpRecord *one_rec )
{
    std::string result;

    // if the function is either a constructor or a destructor,
    // no return value
    if((this->isConstructor == false) && (this->isDestructor == false))
    {
        result += retSignatureLeft + " ";
    }
    if ( one_rec )
    {
        result += one_rec->qualifiedName + "::" + name;
    }
    else
    {
        result += qualifiedName;
    }

    result += "(";
    result += buildParameters();
    result += ")";
    if ( this->isConst )
    {
        result += " const";
    }
    result += retSignatureRight;
    return result;
}

void startHeaderFile ( std::string &output, std::string &input_file,
                       std::string &prefix, bool useQuotes, bool useCpp,
                       std::string &coutput, std::string &houtput,
                       std::string &result )
{
    std::string filename = SplitFilename ( input_file );

    std::string cppfile = removeExt ( filename );
    if ( useCpp )
    {
        cppfile.append ( "_stub.cpp" );
    }
    else
    {
        cppfile.append ( "_stub.c" );
    }

    std::string hfile = removeExt ( filename );
    if ( useCpp )
    {
        hfile.append ( "_stub.hpp" );
    }
    else
    {
        hfile.append ( "_stub.h" );
    }

    std::string header_guard = removeExt ( filename );
    std::replace ( header_guard.begin(), header_guard.end(), '.', '_' );
    std::replace ( header_guard.begin(), header_guard.end(), '-', '_' );
    header_guard += "_STUB_H";
    if ( useCpp )
    {
        header_guard += "PP";
    }
    header_guard.insert ( 0, "_" );
    std::transform ( header_guard.begin(), header_guard.end(),
                     header_guard.begin(), my_toupper() );


    cleanPath ( output );
    cppfile.insert ( 0, output );
    hfile.insert ( 0, output );

    houtput = hfile;
    coutput = cppfile;

    result += "/* OPMOCK2 GENERATED CODE - DO NOT MODIFY */\n";
    result += "#ifndef " + header_guard + "\n";
    result += "#define " + header_guard + "\n\n";

    result += "#include ";
    if ( useQuotes )
    {
        result += "\"";
    }
    else
    {
        result += "<";
    }
    if ( prefix.size() > 0 )
    {
        result += prefix + PATH_SEP_S;
    }

    result += filename;

    if ( useQuotes )
    {
        result += "\"";
    }
    else
    {
        result += ">";
    }
    result += "\n";

    result += "#include \"opmock.h\"\n\n";

}

void writeConstructorBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out )
{
    // basic, empty destructor to make sure we link
    // as constructor/destructors don't return values and should not have side
    // effects beside the current class instance, no need to mock them?
    out << one_func->buildSignature ( one_rec );
    out << "\n{\n";
    out << "}" << std::endl;
}

void writeDestructorBody ( OpFunction *one_func, OpRecord *one_rec, std::ofstream &out )
{
    // same for destructor
    out << one_func->buildSignature ( one_rec );
    out << "\n{\n";
    out << "}" << std::endl;
}

