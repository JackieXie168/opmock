package org.opmock;

import java.util.Iterator;
import java.util.List;

/**
 * Used to write useful structs both for C and C++ generated code
 * 
 * @author pascal
 * 
 */
public class StructWriter {

	/**
	 * write a list of structs useful for mocks
	 * 
	 * @param functions
	 *            list of functions (free functions or class members)
	 * @param className
	 *            name of the class. if "" then it's a free C++ function or a C
	 *            function
	 * @param isImpl
	 *            true if we also want to call the original implementation,
	 *            either a function or through inheritance.
	 * @return
	 */
	public static String writeStructs(List<CFunction> functions,
			String className) {

		String res = "";

		// get the class name but without the ::
		String myClassName = "";
		String classPrefix = "";
		if (className.length() > 0) {
			myClassName = className.replace(':', '_');
			classPrefix = myClassName + "_";
		}

		// declare one set of structs per member function
		for (CFunction oneFunc : functions) {

			String fname = oneFunc.functionName;
			if (oneFunc.nameSpace.length() > 0) {
				fname = oneFunc.functionName.replace(':', '_');
			}

			// typedef to record a function call
			res += "typedef struct\n{\n";

			Iterator<CParameter> itr = oneFunc.params.iterator();
			while (itr.hasNext()) {
				CParameter oneParam = itr.next();
				String s = oneParam.value;

				// if the parameter is an array (one dimension or more)
				// I can't declare it in the struct. Instead, cast it to
				// a void * and use the parameter name.
				if (s.indexOf("[") != -1) {
					res += "    void * " + oneParam.name + ";\n";
				} else {
					// if the parameter is const, remove the const
					// as I can not give a value to this const when creating
					// the struct
					String toPointer = oneParam.value;
					if (oneParam.value.indexOf("const") != -1) {
						toPointer = toPointer.replaceAll("const[ \t]+", "");
					}

					// if the parameter is a reference to something, store
					// a pointer instead, as a reference can't be
					// uninitialized
					if (oneParam.value.indexOf("&") != -1) {
						toPointer = toPointer.replace('&', '*');
					}

					res += "    " + toPointer;
					if (oneParam.hasName == false) {
						res += " " + oneParam.name;
					}
					res += ";\n";
				}
			}

			// additional fields to store matcher pointers
			itr = oneFunc.params.iterator();
			while (itr.hasNext()) {
				CParameter oneParam = itr.next();
				res += "    OPMOCK_MATCHER match_" + oneParam.name + ";\n";
			}

			// add the return value storage if it's not void
			if (oneFunc.returnValue.compareTo("void") != 0) {
				
				// and if the return value is const we need to remove this const as well
				String returnValue = new String(oneFunc.returnValue);
				if (returnValue.indexOf("const") != -1) {
					returnValue = returnValue.replaceAll("const[ \t]+", "");
				}
				
				// if the return value is a reference, store a pointer
				// instead
				if (returnValue.indexOf("&") != -1) {
					String toPointer = returnValue.replace('&', '*');
					res += "    " + toPointer + " return_value;\n";
				} else {
					res += "    " + returnValue + " return_value;\n";
				}
			}
			res += "    char check_params;\n";
			res += "} ";
			res += classPrefix + fname + oneFunc.uid;

			if (oneFunc.overload > 0) {
				res += Integer.toString(oneFunc.overload);
			}

			res += "_call;\n\n";

			// typedef for the struct dedicated to the function
			res += "typedef struct\n{\n";
			res += "    int expectedCalls;\n";
			res += "    int actualCalls;\n";
			
			res += "    OPMOCK_" + classPrefix + fname + oneFunc.uid;

			if (oneFunc.overload > 0) {
				res += Integer.toString(oneFunc.overload);
			}

			res += "_CALLBACK callback;\n";

			// I store instance callback only if this is a c++ class!
			if (className.length() > 0) {
				res += "    OPMOCK_" + classPrefix + fname + oneFunc.uid;
				if (oneFunc.overload > 0) {
					res += Integer.toString(oneFunc.overload);
				}
				res += "_INST_CALLBACK callbackInst;\n";
			}

			res += "    " + classPrefix + fname + oneFunc.uid;
			if (oneFunc.overload > 0) {
				res += Integer.toString(oneFunc.overload);
			}
			res += "_call calls[MAX_FUNC_CALL];\n";

			res += "} " + classPrefix + fname + oneFunc.uid;
			if (oneFunc.overload > 0) {
				res += Integer.toString(oneFunc.overload);
			}
			res += "_struct;\n\n";

			res += "static " + classPrefix + fname + oneFunc.uid;
			if (oneFunc.overload > 0) {
				res += Integer.toString(oneFunc.overload);
			}
			res += "_struct " + classPrefix + fname + oneFunc.uid;
			if (oneFunc.overload > 0) {
				res += Integer.toString(oneFunc.overload);
			}//TODO remove duplicate code. Use a string either empty or with a number in it
			res += "_struct_inst;\n\n";
		}

		return res;
	}
}
