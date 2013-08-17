/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CFunction.java
 * Copyright (C) Pascal Ognibene 2010 <pognibene@gmail.com>
 * 
 *  is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 *  is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

package org.opmock;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class CFunction {
	public List<CParameter> params = new ArrayList<CParameter>();
	public String returnValue = "";
	public String functionName = "";
	public String storage = "";
	boolean isMember = false;
	String access = "";
	public boolean isVariadic;
	public String nameSpace = "";
	public int overload = 0;

	// used to differentiate overloads of the same operation
	// ie functions with the same name but different parameters
	public String uid = "";
	public int nbDefaultParam = 0;
	public boolean isConst = false;

	public String getPrototype() {
		// if the function has a non empty namespace, that's a scoped C++
		// function so write the namespaces!
		// the function name is fully scoped, so I have to retain only the
		// function name
		int nDepth = 0;
		String head = "";
		String[] tab = functionName.split("::");

		if (tab.length != 1) {
			for (int i = 0; i < tab.length - 1; i++) {
				head += "namespace " + tab[i] + " { ";
				nDepth++;
			}
		}

		String res = head + getBodyStart();
		res += ";";

		if (nDepth > 0) {
			for (int i = 0; i < nDepth; i++) {
				res += " }";
			}
		}

		return res;
	}

	public String getBodyStart() {
		String res = "";
		// for a parameter, storage can be const
		if (storage.length() > 0) {
			res = storage + " ";
		}
		if (returnValue.length() > 0) {
			res += returnValue + " ";
		}
	
		res += functionName;
		res += " (";
		res += getParameters();
		res += ")";
		return res;
	}

	public String getDefaultReturn() {

		String toReturn = null;

		// case of void function
		if (returnValue.compareTo("void") == 0) {
			return null;
		}

		int index = returnValue.indexOf("*");
		if (index != -1) {
			toReturn = "    return NULL;";
		} else {
			toReturn = "    " + returnValue + " res;\n";
			toReturn += "    return res;";
		}

		return toReturn;
	}

	// note : it's not possible to mock variadic functions so far
	// or ONLY using callbacks and no management of call counts
	public String getExpectAndReturnPrototypeStart(String functionPrefix,
			boolean useNamespace) {
		String res = "void ";
		String fname = null;

		fname = functionName;
		if (!useNamespace) {
			if (nameSpace.length() > 0) {
				String[] tab = functionName.split("::");
				fname = tab[tab.length - 1];
			}
		}

		res += functionPrefix + fname + "_ExpectAndReturn (";
		res += getParameters();

		// if the function has a return value, add it
		if (returnValue.compareTo("void") != 0) {
			if (params.size() > 0) {
				res += ", ";
			}
			res += returnValue;
			res += " to_return";
		}
		// if I have parameters, I have matchers also
		if (params.size() > 0) {
			res += ", ";
		}
		res += getMatcherParameters();
		res += ")";

		return res;
	}

	private String getMatcherParameters() {
		String res = "";
		Iterator<CParameter> itr = params.iterator();
		while (itr.hasNext()) {
			String s = "OPMOCK_MATCHER match_" + itr.next().name;
			res += s;
			if (itr.hasNext()) {
				res += ", ";
			}
		}
		return res;
	}

	public String getMockReset() {
		String fname = null;
		String head = "";
		int nDepth = 0;
		String[] tab = functionName.split("::");

		if (nameSpace.length() > 0) {
			fname = tab[tab.length - 1];
		} else {
			fname = functionName;
		}

		if (tab.length != 1) {
			for (int i = 0; i < tab.length - 1; i++) {
				head += "namespace " + tab[i] + " { ";
				nDepth++;
			}
		}

		String res = head + "void ";
		res += fname;
		// overload number to differentiate functions
		if (this.overload > 0) {
			res += Integer.toString(this.overload);
		}
		res += "_MockReset();";

		if (nDepth > 0) {
			for (int i = 0; i < nDepth; i++) {
				res += " }";
			}
		}

		return res;
	}

	public String getMockWithCallback() {

		String fname = null;
		String shortName = functionName;

		if (nameSpace.length() > 0) {
			fname = functionName.replace(":", "_");
		} else {
			fname = functionName;
		}
		// first line : typedef for the function pointer
		String res = "typedef ";
		res += returnValue;
		res += " (* OPMOCK_";
		res += fname;

		// if the function is overloaded, make the callback typedef unique
		if (this.overload > 0) {
			res += Integer.toString(this.overload);
		}

		res += "_CALLBACK)(";

		res += getParameters();

		if (params.size() > 0) {
			res += ", ";
		}
		res += "int calls);\n";

		// 2nd line : stub with callback
		// deal with C++ and namespaces
		int nDepth = 0;
		String head = "";
		String[] tab = functionName.split("::");

		if (tab.length != 1) {
			shortName = tab[tab.length - 1];
			for (int i = 0; i < tab.length - 1; i++) {
				head += "namespace " + tab[i] + " { ";
				nDepth++;
			}
		}

		res += head + "void ";
		res += shortName;
		res += "_MockWithCallback(OPMOCK_" + fname;

		if (this.overload > 0) {
			res += Integer.toString(this.overload);
		}

		res += "_CALLBACK callback);";

		if (nDepth > 0) {
			for (int i = 0; i < nDepth; i++) {
				res += " }";
			}
		}

		return res;
	}

	private String getParameters() {
		String res = "";
		Iterator<CParameter> itr = params.iterator();
		while (itr.hasNext()) {
			CParameter param = itr.next();
			String s = param.value;
			if (param.hasName == false) {
				s += " " + param.name;
			}
			res += s;
			if (itr.hasNext()) {
				res += ", ";
			}
		}
		return res;
	}

	public String getMockVerify() {

		int nDepth = 0;
		String head = "";
		String[] tab = functionName.split("::");
		String fname = functionName;

		if (tab.length != 1) {
			fname = tab[tab.length - 1];
			for (int i = 0; i < tab.length - 1; i++) {
				head += "namespace " + tab[i] + " { ";
				nDepth++;
			}
		}

		String res = head + "void ";
		res += fname + uid;

		// uniquify name of verify function for free C style functions
		if (this.overload > 0) {
			res += Integer.toString(this.overload);
		}
		res += "_VerifyMock();";

		if (nDepth > 0) {
			for (int i = 0; i < nDepth; i++) {
				res += " }";
			}
		}

		return res;
	}

	public String getExpectAndReturnBody(boolean noMock) {
		// TODO FIXME fusion with code for c++

		String fname = functionName;
		boolean useNamespace = false;
		if (nameSpace.length() > 0) {
			fname = functionName.replace(':', '_');
			useNamespace = true;
		}

		String structName = fname;
		if (this.overload > 0) {
			structName += Integer.toString(this.overload);
		}
		structName += "_struct_inst";
		String res = getExpectAndReturnPrototypeStart("", useNamespace)
				+ "\n{\n";

		// check if we need to reset the mock
		// in case it was configured before as a callback
		res += "    if(" + structName + ".callback != NULL)\n    {\n";
		res += "        " + functionName;
		if (this.overload > 0) {
			res += Integer.toString(this.overload);
		}
		res += "_MockReset ();\n";
		res += "    }\n\n";

		// check that we're not going outside the call stack
		res += "    if(" + structName
				+ ".expectedCalls >= MAX_FUNC_CALL)\n    {\n";
		res += "        printf(\"WARNING : aborting ";
		res += functionName + "_ExpectAndReturn, call stack overload.\\n\");\n";
		res += "        return;\n";
		res += "    }\n\n";

		if (!noMock) {
			res += "    opmock_add_reset_callback(opmock_reset_all_mocks_in_this_header);\n";
			res += "    opmock_add_verify_callback(opmock_verify_all_mocks_in_this_header);\n";
		}

		// store the function name in the global call stack
		res += "    opmock_add_call((char *)\"" + getBodyStart() + "\");\n";

		// store parameters in the call stack
		Iterator<CParameter> itr = params.iterator();
		while (itr.hasNext()) {
			CParameter oneParam = itr.next();
			String s = oneParam.value;

			// check if this is an array.
			// In this case I need to cast it to void *
			boolean hasArray = false;
			if (s.indexOf("[") != -1) {
				hasArray = true;
			}

			res += "    " + structName + ".calls[";
			res += structName + ".expectedCalls].";
			res += oneParam.name + " = ";
			if (hasArray) {
				res += "(void *) ";
			}
			if (oneParam.value.indexOf('&') != -1) {
				res += "&";
			}

			// if the parameter is const, I need to brute force it to non const
			// for assignment
			String constPrepend = "";
			if ((oneParam.value.indexOf("const") != -1) && (hasArray == false)) {
				// remove the const and the parameter name
				constPrepend = oneParam.value.replaceAll("const[ \t]+", "");
                                
                                // the parameter may have no name (anonymous parameter)
                                // in this case, just append the synthetized name
				int startParamName = constPrepend.lastIndexOf(oneParam.name) - 1;
                                if(startParamName > 0)
                                {
                                    constPrepend = constPrepend.substring(0, startParamName);
                                }
                                /*else
                                {
                                    constPrepend = constPrepend + oneParam.name;
                                }*/

				constPrepend = "(" + constPrepend + ") ";
			}

			res += constPrepend + oneParam.name + ";\n";
		}

		// for each parameter, store as well the pointer to a matcher
		// the pointer can be NULL, in which case no parameter matching is done
		itr = params.iterator();
		while (itr.hasNext()) {
			CParameter oneParam = itr.next();
			res += "    " + structName + ".calls[";
			res += structName + ".expectedCalls].match_";
			res += oneParam.name + " = match_" + oneParam.name + ";\n";
		}

		// store return value in the call stack
		// the return value can be const as well, in which case
		// i brute force it to non const
		if (returnValue.compareTo("void") != 0) {
			res += "    " + structName + ".calls[";
			res += structName + ".expectedCalls].return_value = ";

			String toCast = "";
			if (returnValue.indexOf("const") != -1) {
				toCast = returnValue.replaceAll("const[ \t]+", "");
				toCast = "(" + toCast + ")";
				res += toCast;
			}

			if (returnValue.indexOf("&") != -1) {
				res += "&to_return;\n";
			} else {
				res += "to_return;\n";
			}
		}

		// specify that we do want to test the parameters when the function is
		// called
		res += "    " + structName + ".calls[";
		res += structName + ".expectedCalls].check_params = 1;\n";

		res += "    " + structName + ".expectedCalls++;\n";
		res += "}\n\n";

		return res;
	}

	public String getParameterName(String s) {
		String[] array = s.split(" ");
		return array[array.length - 1];
	}

	public String getMockBody(String className) {

		String res = "";
		String myClassName = "";
		String classPrefix = "";
		if (className.length() > 0) {
			myClassName = className.replace(':', '_');
			classPrefix = myClassName + "_";
		}

		String fname = functionName;
		if (nameSpace.length() > 0) {
			fname = functionName.replace(':', '_');
		}
		String structName = classPrefix + fname + uid;
		if (this.overload > 0) {
			structName += Integer.toString(this.overload);
		}
		structName += "_struct_inst";

		// TODO refactor getCppBodyStart and getBodyStart
		// to get a single function for C and C++
		if (className.length() == 0) {
			res = getBodyStart() + "\n{\n";
		} else {
			res = getCppBodyStart(className, "") + "\n{\n";
		}

		// declare variables at the top of the file
		boolean isVoid = false;
		if (returnValue.compareTo("void") == 0) {
			isVoid = true;
		}

		// return value if function not void
		if (isVoid == false) {
			String returnType = "";
			if (returnValue.indexOf("&") != -1) {
				returnType = returnValue.replace('&', '*');
			} else {
				returnType = returnValue;
			}
			// if the return type contains a const, remove it
			if (returnType.indexOf("const") != -1) {
				returnType = returnType.replace("const", "");
			}
			res += "    " + returnType;

			res += " default_res;\n";
		}

		res += "    int opmock_i;\n";
		res += "    " + structName + ".actualCalls++;\n\n";

		if (!isVoid) {
			res += "    default_res = " + structName
					+ ".calls[0].return_value;\n\n";
		}

		// call callback function if in callback mode
		res += getOperationCallbackBody(structName, isVoid, false);
		if (className.length() > 0) {
			if (storage.indexOf("static") == -1) {
				res += "    else\n";
				res += getOperationCallbackBody(structName, isVoid, true);
			}
		}

		// check if we are expecting calls (behavior programmed)
		res += "    if (" + structName + ".expectedCalls == 0)\n";
		res += "    {\n";
		String msg = "WARNING : unexpected call of '";
		if (className.length() > 0) {
			msg += className + "::";
		}
		msg += functionName + "', returning random value.";
		res += "        opmock_add_error_message((char *) \"" + msg + "\");\n";

		if (isVoid == false) {
			if (returnValue.indexOf("&") != -1) {
				res += "        return *default_res;\n";
			} else {
				res += "        return default_res;\n";
			}
		} else {
			res += "        return;\n";
		}
		res += "    }\n\n";

		// check if this is the call we expect
		// if it's not stop the call here and return default value

		res += "    if(strcmp(opmock_get_current_call(), \"";
		String operation;
		if (className.length() == 0) {
			operation = getBodyStart();
		} else {
			operation = getCppBodyStart(className, "");
		}
		res += operation;
		res += "\") != 0) {\n";
		res += "        char buffer[OP_ERROR_MESSAGE_LENGTH];\n";
		res += "        snprintf(buffer, OP_ERROR_MESSAGE_LENGTH, \"WARNING : got call to '";
		res += operation
				+ "',  but was expecting call to '%s\", opmock_get_current_call());\n";
		res += "        opmock_add_error_message(buffer);\n";
		res += "    }\n";
		res += "    opmock_pop_call();\n\n";

		// /
		res += "    " + "if (" + structName
				+ ".calls[0].check_params == 1) {\n";

		// check parameters if there are some
		Iterator<CParameter> itr = params.iterator();
		while (itr.hasNext()) {
			CParameter oneParam = itr.next();
			res += "        if (" + structName + ".calls[0].match_"
					+ oneParam.name + ") {\n";

			// is this a reference parameter?
			// in this case cast the reference address to a void *
			if (oneParam.value.indexOf("&") != -1) {
				res += "            void * val1 = (void *) " + structName
						+ ".calls[0]." + oneParam.name + ";\n";
				res += "            void * val2 = (void *) &" + oneParam.name
						+ ";\n";
			}

			// is it a function pointer ? TODO

			// is this an array parameter?
			// in this case cast the array to void *
			else if (oneParam.value.indexOf("[") != -1) {
				res += "            void * val1 = (void *) " + structName
						+ ".calls[0]." + oneParam.name + ";\n";
				res += "            void * val2 = (void *) " + oneParam.name
						+ ";\n";
			}

			// default case : it's either a primitive type,
			// or a typedef, or a struct passed by value
			// in this case get a void * on both param and stored param
			else {
				res += "            void * val1 = (void *) &" + structName
						+ ".calls[0]." + oneParam.name + ";\n";
				res += "            void * val2 = (void *) &" + oneParam.name
						+ ";\n";
			}

			// call the matcher function
			res += "            int match_result = " + structName
					+ ".calls[0].match_" + oneParam.name + "(val1, val2, \""
					+ oneParam.name + "\", get_matcher_message());\n";

			// if problem yell
			res += "            if(match_result) {\n";

			String funcName = "";
			if (className.length() > 0) {
				funcName += className + "::";
			}
			funcName += functionName;

			res += "                char buffer[OP_ERROR_MESSAGE_LENGTH];\n";
			res += "                snprintf(buffer, OP_ERROR_MESSAGE_LENGTH, \"WARNING : on call number %d of '";
			res += funcName + "', %s\"," + structName + ".actualCalls"
					+ ", get_matcher_message());\n";
			res += "                opmock_add_error_message((char *) buffer);\n";
			res += "            }\n";
			res += "        }\n";
		}
		res += "    }\n\n";

		// shift on the left the calls array
		res += "    for(opmock_i = 1; opmock_i < " + structName
				+ ".expectedCalls; opmock_i++) {\n";
		res += "        " + structName + ".calls[opmock_i - 1] = " + structName
				+ ".calls[opmock_i];\n";
		res += "    }\n\n";

		res += "    " + structName + ".expectedCalls--;\n";

		if (isVoid == false) {
			if (returnValue.indexOf("&") != -1) {
				res += "    return *default_res;\n";
			} else {
				res += "    return default_res;\n";
			}
		}

		res += "}\n\n";

		return res;
	}

	private String getBasename(String name) {
		int index = name.lastIndexOf(':');
		if (index == -1) {
			return name;
		} else {
			return name.substring(index + 1);
		}
	}

	private String getNamespace(String name) {
		int index = name.lastIndexOf(':');
		if (index == -1) {
			return "";
		} else {
			return name.substring(0, index - 1);
		}
	}

	private String getOperationCallbackBody(String structName, boolean isVoid,
			boolean isInstance) {
		String res = "";
		res += "    if (" + structName;
		if (isInstance) {
			res += ".callbackInst != NULL)\n";
		} else {
			res += ".callback != NULL)\n";
		}
		res += "    {\n";
		res += "        ";
		if (isVoid == false) {
			res += "return ";
		}
		if (isInstance) {
			res += structName + ".callbackInst (";
		} else {
			res += structName + ".callback (";
		}

		// parameters for the function
		Iterator<CParameter> itr = params.iterator();
		while (itr.hasNext()) {
			CParameter oneParam = itr.next();
			res += oneParam.name;
			if (itr.hasNext()) {
				res += ", ";
			}
		}
		if (params.size() > 0) {
			res += ", ";
		}

		// number of calls
		res += structName;
		if (isInstance) {
			res += ".actualCalls, this);\n";
		} else {
			res += ".actualCalls);\n";
		}
		if (isVoid == true) {
			res += "        return;\n";
		}
		res += "    }\n";
		return res;
	}

	public String getCallbackBody(String className, boolean isInstance,
			boolean noMock) {

		String fname = functionName;
		if (nameSpace.length() > 0) {
			fname = functionName.replace(':', '_');
		}

		String myClassName = "";
		String classPrefix = "";
		if (className.length() > 0) {
			myClassName = className.replace(':', '_') + "_";
			classPrefix = className + "_Mock::";
		}

		String mystruct = myClassName + fname + uid;
		if (this.overload > 0) {
			mystruct += Integer.toString(this.overload);
		}
		mystruct += "_struct_inst";

		String res = "void ";
		if (!isInstance) {
			res += classPrefix + functionName + "_MockWithCallback(OPMOCK_"
					+ myClassName + fname + uid;
			if (this.overload > 0) {
				res += Integer.toString(this.overload);
			}
			res += "_CALLBACK callback)\n{\n";
		} else {
			res += classPrefix + functionName
					+ "_MockWithInstanceCallback(OPMOCK_" + myClassName + fname
					+ uid;
			if (this.overload > 0) {
				res += Integer.toString(this.overload);
			}
			res += "_INST_CALLBACK callback)\n{\n";
		}

		if (!noMock) {
			// FIXME pas sur d'avoir besoin de ce code ici
			// genere en trop?
			res += "    opmock_add_reset_callback(opmock_reset_all_mocks_in_this_header);\n";
			res += "    opmock_add_verify_callback(opmock_verify_all_mocks_in_this_header);\n";
		}

		if (isInstance) {
			res += "    " + mystruct + ".callbackInst = callback;\n";
			res += "    " + mystruct + ".callback = NULL;\n";
		} else {
			res += "    " + mystruct + ".callback = callback;\n";
			if (className.length() > 0) {
				res += "    " + mystruct + ".callbackInst = NULL;\n";
			}
		}
		res += "    " + mystruct + ".expectedCalls = 0;\n";
		res += "    " + mystruct + ".actualCalls = 0;\n";

		res += "}\n\n";

		return res;
	}

	public String getPrototypeUseImpl() {
		int nDepth = 0;
		String head = "";
		String[] tab = functionName.split("::");
		String fname = functionName;

		if (tab.length != 1) {
			fname = tab[tab.length - 1];
			for (int i = 0; i < tab.length - 1; i++) {
				head += "namespace " + tab[i] + " { ";
				nDepth++;
			}
		}

		String res = head + "void " + fname + uid + "_UseImpl ();";

		if (nDepth > 0) {
			for (int i = 0; i < nDepth; i++) {
				res += " }";
			}
		}

		return res;
	}

	public String getUseImplBody(String className) {
		String fname = functionName;
		if (nameSpace.length() > 0) {
			fname = functionName.replace(':', '_');
		}
		String myClassName = "";
		String classPrefix = "";
		if (className.length() > 0) {
			myClassName = className.replace(':', '_') + "_";
			classPrefix = className + "::";
		}
		String structName = myClassName + fname + uid + "_struct_inst";

		String res = "void " + classPrefix + functionName + uid
				+ "_UseImpl ()\n";
		res += "{\n";
		res += "    " + structName + ".callback = NULL;\n";
		if (className.length() > 0) {
			res += "    " + structName + ".callbackInst = NULL;\n";
		}
		res += "    " + structName + ".expectedCalls = 0;\n";
		res += "    " + structName + ".actualCalls = 0;\n";
		res += "    " + structName + ".useRealImpl = 1;\n";
		res += "}\n\n";

		return res;
	}

	public String getResetBody(String className) {

		String fname = functionName;
		if (nameSpace.length() > 0) {
			fname = functionName.replace(':', '_');
		}
		String myClassName = "";
		String classPrefix = "";
		if (className.length() > 0) {
			myClassName = className.replace(':', '_') + "_";
			classPrefix = className + "_Mock::";
		}
		String structName = myClassName + fname + uid;

		if (this.overload > 0) {
			structName += Integer.toString(this.overload);
		}
		structName += "_struct_inst";

		String res = "void ";
		res += classPrefix + functionName + uid;
		if (this.overload > 0) {
			res += Integer.toString(this.overload);
		}
		res += "_MockReset()\n{\n";
		res += "    " + structName + ".expectedCalls = 0;\n";
		res += "    " + structName + ".actualCalls = 0;\n";
		res += "    " + structName + ".callback = NULL;\n";

		if (className.length() > 0) {
			res += "    " + structName + ".callbackInst = NULL;\n";
		}

		res += "}\n\n";
		return res;
	}

	public String getVerifyBody(String className) {

		String fname = functionName;
		if (nameSpace.length() > 0) {
			fname = functionName.replace(':', '_');
		}

		String myClassName = "";
		String classPrefix = "";
		if (className.length() > 0) {
			myClassName = className.replace(':', '_') + "_";
			classPrefix = className + "_Mock::";
		}

		String structName = myClassName + fname + uid;
		if (this.overload > 0) {
			structName += Integer.toString(this.overload);
		}
		structName += "_struct_inst";

		String res = "void ";
		res += classPrefix + functionName + uid;
		if (this.overload > 0) {
			res += Integer.toString(this.overload);
		}
		res += "_VerifyMock()\n{\n";
		res += "    if (" + structName + ".expectedCalls != 0) {\n";
		res += "        char buffer[OP_ERROR_MESSAGE_LENGTH];\n";

		String funcName = "";
		if (className.length() > 0) {
			funcName += className + "::";
		}
		funcName += functionName;

		res += "        snprintf(buffer, OP_ERROR_MESSAGE_LENGTH, \"WARNING : Bad number of calls (%d) for '";
		res += funcName + "'\"," + structName + ".actualCalls);\n";

		res += "        opmock_add_error_message((char *) buffer);\n";
		res += "    }\n";
		res += "}\n\n";

		return res;
	}

	public String getResetPrototype() {
		String res = "void " + functionName + uid + "_MockReset();\n";
		return res;
	}

	public String getCppCallbackPrototype(String prefix, boolean isInstance) {
		String res = "void ";

		res += functionName;
		if (isInstance) {
			res += "_MockWithInstanceCallback(OPMOCK_" + prefix + functionName
					+ uid + "_INST_CALLBACK callback);\n";
		} else {
			res += "_MockWithCallback(OPMOCK_" + prefix + functionName + uid
					+ "_CALLBACK callback);\n";
		}
		return res;
	}

	public String getCppVerifyPrototype() {
		return getMockVerify();
	}

	public String getCppCallOriginalPrototype(String className) {
		return getPrototypeUseImpl();
	}

	public String getCppBodyStart(String className, String classSuffix) {
		String res = "";
		if (returnValue.length() > 0) {
			res = returnValue + " ";
		}
		res += className + classSuffix + "::" + functionName + classSuffix
				+ " (";
		res += getParameters();
		res += ")";
		if (this.isConst) {
			res += " const";
		}
		return res;
	}

	public String getCppExpectAndReturnPrototype() {
		String res = getExpectAndReturnPrototypeStart("", false) + ";\n";
		return res;
	}

	public String getTemplateBody(boolean useImpl) {
		String res = "";
		String[] tab = nameSpace.split("::");

		int nDepth = 0;
		if (tab.length != 1) {
			for (int i = 0; i < tab.length; i++) {
				res += "namespace " + tab[i] + "\n{\n";
				nDepth++;
			}
		}

		String structName = functionName + "_struct_inst";
		res += "template </* FIXME write parameters here */>\n";
		res += getBodyStart() + "\n{\n";

		// TODO write template body
		// should at least return a default value if there's one
		// namespace ok, maintenant il faut ecrire le body
		// et trouver un moyen de recuperer les parametres

		res += "}\n";

		// close namespaces
		if (nDepth > 0) {
			for (int i = 0; i < nDepth; i++) {
				res += "}\n";
			}
			res += "\n";
		} else {
			res += "\n";
		}

		return res;
	}

	public String getExpectAndReturnPrototype(String functionPrefix) {
		int nDepth = 0;
		String head = "";
		String[] tab = functionName.split("::");

		if (tab.length != 1) {
			for (int i = 0; i < tab.length - 1; i++) {
				head += "namespace " + tab[i] + " { ";
				nDepth++;
			}
		}
		String res = head
				+ getExpectAndReturnPrototypeStart(functionPrefix, false) + ";";
		if (nDepth > 0) {
			for (int i = 0; i < nDepth; i++) {
				res += " }";
			}
		}
		return res;
	}
}
