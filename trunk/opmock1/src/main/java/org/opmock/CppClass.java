/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CppClass.java
 * Copyright (C) Pascal Ognibene 2010 <pognibene@gmail.com>
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

package org.opmock;

//TODO supporter overload des operateurs << >> (pour les flux)

//TODO enlever actualCalls++ inutile ds le code
//et faire un early exit

//TODO gérer les surcharges d'opérateurs
// de façon a pouvoir les surcharger aussi si je dérive de la classe
//ou pas... (pb est que si dans le code existant j'utilise les surcharges de
//la classe, ça pose pb. En mock pur pas pb, en mock hérité ??)

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class CppClass {
	public String namespace;
	public String className;
	public List<String> inheritance = new ArrayList<String>();
	public List<CFunction> functions = new ArrayList<CFunction>();
	public List<CppAttribute> attributes = new ArrayList<CppAttribute>();
	public List<CFunction> constructors = new ArrayList<CFunction>();
	public List<CFunction> destructors = new ArrayList<CFunction>();

	/**
	 * Get the class definition, to be included in the header This is the same
	 * name than the original class, appended with Mock
	 * 
	 * @return
	 */
	public String getDefinition(boolean noMock) {
		String res = "";
		int nDepth = 0;

		// find out if this class is inside nested namespaces
		String[] tab = className.split("::");

		if (tab.length != 1) {
			for (int i = 0; i < tab.length - 1; i++) {
				res += "namespace " + tab[i] + "\n{\n";
				nDepth++;
			}
		}

		// class definition
		res += "class " + tab[tab.length - 1] + "_Mock";

		res += "\n";
		res += "{\n";
		res += "  public:\n";

		// FIXME dois-je implementer les constructeurs propres à la classe?
		// TODO pas de constructeurs, supposés hérités
		// constructors
		// for (CFunction oneFunction : constructors) {
		// res += "    " + oneFunction.getPrototype() + "\n";
		// }
		// if (constructors.size() > 0)
		// res += "\n";

		// // destructors
		// for (CFunction oneFunction : destructors) {
		// res += "    " + oneFunction.getPrototype() + "\n";
		// }
		// if (destructors.size() > 0)
		// res += "\n";

		// // now all business operations definitions
		// for (CFunction oneFunction : functions) {
		// res += "    " + oneFunction.getPrototype() + "\n";
		// }
		// if (functions.size() > 0)
		// res += "\n";

		if (!noMock) {
			// now specific opmock operations
			// reset operations
			for (CFunction oneFunction : functions) {
				res += "    static " + oneFunction.getResetPrototype();
			}
			if (functions.size() > 0)
				res += "\n";

			// class reset operation
			// to reset all operations of a class in one go!
			res += "    static void MockReset ();\n";
			res += "    static void VerifyMock ();\n\n";
		}

		// callback operations
		String myClassName = className.replace(':', '_');
		myClassName += "_";
		for (CFunction oneFunction : functions) {
			res += "    static "
					+ oneFunction.getCppCallbackPrototype(myClassName, false);
		}
		if (functions.size() > 0)
			res += "\n";

		// instance callback operations
		for (CFunction oneFunction : functions) {
			res += "    static "
					+ oneFunction.getCppCallbackPrototype(myClassName, true);
		}
		if (functions.size() > 0)
			res += "\n";

		if (!noMock) {
			// verify operations
			for (CFunction oneFunction : functions) {
				res += "    static " + oneFunction.getCppVerifyPrototype()
						+ "\n";
			}
			if (functions.size() > 0)
				res += "\n";

			// expect and return operations
			for (CFunction oneFunction : functions) {
				res += "    static "
						+ oneFunction.getCppExpectAndReturnPrototype();
			}
			if (functions.size() > 0)
				res += "\n";
		}

		res += "};\n";

		// class conclusion
		// if there are namespace close them
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

	public String buildClassTypedefs() {
		String res = "";

		for (CFunction oneFunc : functions) {
			// callback for class callback
			res += getOperationCallback(oneFunc, false);

			// and callback for instance callback (if I
			// have a pointer on the class)
			res += getOperationCallback(oneFunc, true);
		}
		res += "\n";

		return res;
	}

	public String getOperationCallback(CFunction oneFunc, boolean isInstance) {
		// TODO a mettre en commun avec code C
		String myClassName = className.replace(':', '_');

		String res = "typedef ";
		res += oneFunc.returnValue;
		res += " (* OPMOCK_";
		res += myClassName + "_";
		res += oneFunc.functionName + oneFunc.uid;
		if (isInstance) {
			res += "_INST";
		}
		res += "_CALLBACK)(";

		Iterator<CParameter> itr = oneFunc.params.iterator();
		while (itr.hasNext()) {
			String s = itr.next().value;
			res += s;
			if (itr.hasNext()) {
				res += ", ";
			}
		}
		if (oneFunc.params.size() > 0) {
			res += ", ";
		}

		res += "int calls";
		if (isInstance) {
			res += ", ";
			if (oneFunc.isConst) {
				res += "const ";
			}
			res += className;
			res += " * cb_ptr";
		}
		res += ");\n";

		return res;
	}

	public String getMockBodies(boolean noMock) {
		String res = "";
		for (CFunction oneFunc : functions) {
			res += oneFunc.getMockBody(className);
		}
		return res;
	}

	/**
	 * Given a name like foo::boo:yoo::MyClass return foo::boo:yoo
	 * 
	 * @param className2
	 * @return
	 */
	private String getNamespace(String className2) {
		int index = className2.lastIndexOf(':');
		if (index == -1) {
			return "";
		} else {
			return className2.substring(0, index - 1);
		}
	}

	public String getResetBodies() {
		String res = "";
		for (CFunction oneFunc : functions) {
			res += oneFunc.getResetBody(className);
		}
		return res;
	}

	public String getCallbackBodies(boolean noMock) {
		String res = "";

		res += getCallbackBody(className, false, noMock);
		res += getCallbackBody(className, true, noMock);
		return res;
	}

	private String getCallbackBody(String className, boolean isInstance,
			boolean noMock) {
		String res = "";
		for (CFunction oneFunc : functions) {
			res += oneFunc.getCallbackBody(className, isInstance, noMock);
		}
		return res;
	}

	public String getVerifyBodies() {
		String res = "";
		for (CFunction oneFunc : functions) {
			res += oneFunc.getVerifyBody(className);
		}
		return res;
	}

	public String getExpectAndReturnBodies(boolean noMock) {

		// TODO a mettre en commun avec code C
		// doit faire partie de la fonction, pas de la classe
		// a part le nom de classe (ou de namespace) a mettre en parametre
		// supplementaire, c'est tout pareil que le C

		String myClassName = className.replace(':', '_');
		String res = "";

		for (CFunction oneFunc : functions) {
			String structName = myClassName + "_" + oneFunc.functionName
					+ oneFunc.uid + "_struct_inst";

			res += oneFunc.getExpectAndReturnPrototypeStart(className
					+ "_Mock::", false)
					+ "\n{\n";

			// check if we need to reset the mock
			// in case it was configured before as a callback
			res += "    if(" + structName + ".callback != NULL)\n    {\n";
			res += "        " + className + "_Mock::" + oneFunc.functionName
					+ oneFunc.uid + "_MockReset ();\n";
			res += "    }\n\n";

			res += "    if(" + structName + ".callbackInst != NULL)\n    {\n";
			res += "        " + className + "_Mock::" + oneFunc.functionName
					+ oneFunc.uid + "_MockReset ();\n";
			res += "    }\n\n";

			// check that we're not going outside the call stack
			res += "    if(" + structName
					+ ".expectedCalls >= MAX_FUNC_CALL)\n    {\n";
			res += "        printf(\"WARNING : aborting ";
			res += className + "::" + oneFunc.functionName + oneFunc.uid;
			res += "_ExpectAndReturn, call stack overload.\\n\");\n";
			res += "        return;\n";
			res += "    }\n\n";

			if (!noMock) {
				res += "    opmock_add_reset_callback(opmock_reset_all_mocks_in_this_header);\n";
				res += "    opmock_add_verify_callback(opmock_verify_all_mocks_in_this_header);\n";
			}

			// store the function name in the global call stack
			res += "    opmock_add_call((char *)\""
					+ oneFunc.getCppBodyStart(className, "") + "\");\n";

			// store parameters in the call stack
			Iterator<CParameter> itr = oneFunc.params.iterator();
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

				// if the parameter is a reference, get its address instead
				// because I can't store an uninitialized reference
				if (hasArray) {
					res += "(void *) ";
				}
				if (oneParam.value.indexOf('&') != -1) {
					res += "&";
				}

				// if the parameter is const, I need to brute force it to non
				// const for assignment
				String constPrepend = "";
				if ((oneParam.value.indexOf("const") != -1)
						&& (hasArray == false)) {

					// remove the const and the parameter name
					constPrepend = oneParam.value.replaceAll("const[ \t]+", "");

					// find the last space or tab in the line, just before the
					// parameter name
					// and cut before that to get the type
					int startParamName = constPrepend
							.lastIndexOf(oneParam.name) - 1;
					constPrepend = constPrepend.substring(0, startParamName);

					constPrepend = "(" + constPrepend + ") ";
				}

				res += constPrepend + oneParam.name + ";\n";
			}

			// for each parameter, store as well the pointer to a matcher
			// the pointer can be NULL, in which case no parameter matching is
			// done
			itr = oneFunc.params.iterator();
			while (itr.hasNext()) {
				CParameter oneParam = itr.next();
				res += "    " + structName + ".calls[";
				res += structName + ".expectedCalls].match_";
				res += oneParam.name + " = match_" + oneParam.name + ";\n";
			}

			// store return value in the call stack
			if (oneFunc.returnValue.compareTo("void") != 0) {
				res += "    " + structName + ".calls[";
				res += structName + ".expectedCalls].return_value = ";

				String toCast = "";
				if (oneFunc.returnValue.indexOf("const") != -1) {
					toCast = oneFunc.returnValue.replaceAll("const[ \t]+", "");
					toCast = "(" + toCast + ")";
					res += toCast;
				}

				if (oneFunc.returnValue.indexOf("&") != -1) {
					res += "&to_return;\n";
				} else {
					res += "to_return;\n";
				}
			}

			res += "    " + structName + ".calls[";
			res += structName + ".expectedCalls].check_params = 1;\n";

			res += "    " + structName + ".expectedCalls++;\n";
			res += "}\n\n";
		}
		return res;
	}

	/*
	 * Get forward declaration for a mock class. This is the same name than the
	 * original class + Mock (everything mock related is delegated in this
	 * class)
	 */
	public String getForwardDeclaration() {
		String res = "";

		// split the class to get the namespaces if there are any
		String[] tab = className.split("::");
		if (tab.length > 1) {
			for (int index = 0; index < tab.length - 1; index++) {
				res += "namespace " + tab[index] + " { ";
			}
			res += "class " + tab[tab.length - 1] + "_Mock;";
			for (int index = 0; index < tab.length - 1; index++) {
				res += " }";
			}
			res += "\n";
		} else {
			res = "class " + className + "_Mock;\n";
		}
		return res;
	}

	public String getUseImplBodies() {
		String res = "";
		for (CFunction oneFunc : functions) {
			res += oneFunc.getUseImplBody(className);
		}
		return res;
	}

	public String getClassResetBody() {
		String res = "void " + className + "_Mock::MockReset ()\n{\n";

		for (CFunction oneFunc : functions) {
			res += "    " + className + "_Mock::" + oneFunc.functionName
					+ oneFunc.uid;
			res += "_MockReset ();\n";
		}
		res += "}\n\n";
		return res;
	}

	// preliminary support for constructors
	// currently they do nothing
	public String getConstructorBodies() {
		String res = "";
		for (CFunction oneFunc : constructors) {
			res += getConstructorBody(oneFunc);
		}
		return res;
	}

	private String getConstructorBody(CFunction oneFunc) {
		String res = oneFunc.getCppBodyStart(className, "") + "\n{\n";
		// empty constructor.
		res += "}\n\n";
		return res;
	}

	public String getDestructorBody() {
		String res = "";
		for (CFunction oneFunc : destructors) {
			// there's already a ~ in front of the method name
			// so I can reuse the constructor body logic
			res += getConstructorBody(oneFunc);
		}
		return res;
	}

	public String getClassVerifyBody() {
		String res = "void " + className + "_Mock::VerifyMock ()\n{\n";

		for (CFunction oneFunc : functions) {
			res += "    " + className + "_Mock::" + oneFunc.functionName
					+ oneFunc.uid;
			res += "_VerifyMock ();\n";
		}
		res += "}\n\n";
		return res;
	}
}
