/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Main.java
 * Copyright (C) Pascal Ognibene 2010-2012 <pognibene@gmail.com>
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

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Main {
	static boolean useCpp = false;

	public static void main(String[] args) {
		String input = null, outputPath = null;
		String headerPrefix = "";
		String header = null;
		String skipFunct = "";
		String keepOnly = "";
		boolean noMock = false;

		if (args.length < 6) {
			System.out
					.println("Required arguments : --input-file path_to_input --output-path output_path --header header_filename");
			System.out.println("Optional argument : --use-impl yes");
			System.out
					.println("\tWill generate specific code to call the 'original' renamed implementation of a function");
			System.out.println("Optional argument : --use-cpp yes");
			System.out
					.println("\tParse the header as a C++ header, looking for classes rather than functions.");
			System.out
					.println("Optional argument : --header-prefix path_to_prepend");
			System.out
					.println("\tprepend this path to include statements in generated code.");
			System.out.println("Optional argument : --no-mock yes/no");
			System.out
					.println("\tIf set to yes, skip the mock generation and just keep the stub/callback code.");
			System.out
					.println("Optional argument : --skip-funct val1,val2,val3,...,valn");
			System.out
					.println("\tWhen generating C, skip functions names that are in the specified comma separated list.");
			System.out
					.println("Optional argument : --keep-only val1,val2,val3,...,valn");
			System.out
					.println("\tWith C or C++, generate code only the fully scoped operations in the specified comma separated list.");
			System.exit(1);
		}

		int i = 0;
		while (i < args.length - 1) {

			if (args[i].compareTo("--input-file") == 0) {
				input = args[i + 1];
				i += 2;
			} else if (args[i].compareTo("--output-path") == 0) {

				outputPath = args[i + 1];
				i += 2;
			} else if (args[i].compareTo("--header-prefix") == 0) {
				headerPrefix = args[i + 1];
				i += 2;
			} else if (args[i].compareTo("--header") == 0) {
				header = args[i + 1];
				i += 2;
			} else if (args[i].compareTo("--use-cpp") == 0) {
				String useIt = args[i + 1];
				if (useIt.compareTo("yes") == 0) {
					useCpp = true;
				}
				i += 2;
			} else if (args[i].compareTo("--skip-funct") == 0) {
				skipFunct = args[i + 1];
				i += 2;
			} else if (args[i].compareTo("--no-mock") == 0) {
				String useIt = args[i + 1];
				if (useIt.compareTo("yes") == 0) {
					noMock = true;
				}
				i += 2;
			} else if (args[i].compareTo("--keep-only") == 0) {
				keepOnly = args[i + 1];
				i += 2;
			} else {
				// default case : unknown option, try to skip it
				i++;
			}
		}

		if (input == null) {
			System.out
					.println("ERROR : bad or missing --input-file parameter, exiting.");
			System.exit(1);
		}
		if (outputPath == null) {
			System.out
					.println("ERROR : bad or missing --output-path parameter, exiting.");
			System.exit(1);
		}
		
		// print opmock version
		System.out.println("Opmock 0.9.2 running...");

		String[] toExclude = skipFunct.split(",");

		// remove prepended qualifiers :: if necessary
		for (int j = 0; j < toExclude.length; j++) {
			if (toExclude[j].startsWith("::")) {
				toExclude[j] = toExclude[j].substring(2);
			}
		}
		
		String[] toKeep = keepOnly.split(",");
		if (toKeep.length == 1 && toKeep[0].length() == 0) {
			toKeep = null;
		} else {
			for (int j = 0; j < toKeep.length; j++) {
				if (toKeep[j].startsWith("::")) {
					toKeep[j] = toKeep[j].substring(2);
				}
			}
		}

		// process the input to extract paths and names
		File f = new File(input);
		String filename = f.getName();

		// cut the .xml extension
		filename = filename.substring(0, filename.length() - 4);

		if (!outputPath.endsWith(File.separator)) {
			outputPath += File.separator;
		}

		if (headerPrefix.length() > 0) {
			if (!headerPrefix.endsWith(File.separator)) {
				headerPrefix += File.separator;
			}
		}

		String outputHeader = null;
		String output = null;
		if (useCpp == false) {
			output = outputPath + filename + "_stub.c";
			outputHeader = outputPath + filename + "_stub.h";
		} else {
			output = outputPath + filename + "_stub.cpp";
			outputHeader = outputPath + filename + "_stub.hpp";
		}

		XmlLoader loader = new XmlLoader();

		// This is a C header
		if (useCpp == false) {
			List<CFunction> functions = loader.processFileForC(input);

			// check that there are no functions defined more than one time
			// can happen with some faulty headers
			List<CFunction> funcToRemove = new ArrayList<CFunction>();
			HashMap<String, CFunction> map = new HashMap<String, CFunction>();

			for (CFunction oneFunc : functions) {
				boolean fromMap = map.containsKey(oneFunc.functionName);
				if (fromMap == true) {
					funcToRemove.add(oneFunc);
				} else {
					map.put(oneFunc.functionName, oneFunc);
				}
			}

			for (CFunction removeOne : funcToRemove) {
				System.out.println("WARNING : removed function "
						+ removeOne.functionName
						+ " because it's already defined.");
				functions.remove(removeOne);
			}

			// check if I have to remove some more functions with an exclude
			// list
			funcToRemove = new ArrayList<CFunction>();
			for (int j = 0; j < toExclude.length; j++) {
				for (CFunction oneFunc : functions) {
					if (toExclude[j].compareTo(oneFunc.functionName) == 0) {
						funcToRemove.add(oneFunc);
					}
				}
			}

			// now just keep functions in the keepOnly list
			if (toKeep != null) {
				for (CFunction oneFunc : functions) {
					boolean foundFunction = false;
					for (int j = 0; j < toKeep.length; j++) {
						if (toKeep[j].compareTo(oneFunc.functionName) == 0) {
							foundFunction = true;
						}
					}
					if (foundFunction == false) {
						funcToRemove.add(oneFunc);
					}
				}
			}

			for (CFunction removeOne : funcToRemove) {
				System.out
						.println("INFO : removed function "
								+ removeOne.functionName
								+ " because it's in the exclusion list or not in the keep list.");
				functions.remove(removeOne);
			}

			// write header file with mock function prototypes
			writeMockHeader(functions, outputHeader, header, noMock,
					headerPrefix);

			// I have the list of C functions/prototypes
			// now produce the mocked implementation of the functions
			// and the utility functions/macros

			try {
				PrintWriter out = new PrintWriter(new BufferedWriter(
						new FileWriter(output)));

				out.println("/* OPMOCK GENERATED CODE - DO NOT MODIFY */\n");

				out.println("#include \"" + headerPrefix + filename + "_stub.h"
						+ "\"\n");
				out.println("#include <stdio.h>\n");
				out.println("#include <string.h>\n");

				String supportStructs = StructWriter
						.writeStructs(functions, "");
				out.println(supportStructs);

				if (!noMock) {
					out.print(getResetAllBody(filename, functions, null));
					out.print(getVerifyAllBody(filename, functions, null));
				}

				for (CFunction oneFunc : functions) {
					out.print(oneFunc.getMockBody(""));
					out.print(oneFunc.getResetBody(""));
					out.print(oneFunc.getCallbackBody("", false, noMock));
					out.print(oneFunc.getVerifyBody(""));
					out.print(oneFunc.getExpectAndReturnBody(noMock));
				}

				out.close();

			} catch (IOException e) {
				e.printStackTrace();
				System.exit(1);
			}
		}
		// This is a C++ header
		else {
			List<CppClass> classes = new ArrayList<CppClass>();
			List<CFunction> functionTemplates = new ArrayList<CFunction>();
			List<CFunction> functions = new ArrayList<CFunction>();
			List<CppClass> classTemplates = new ArrayList<CppClass>();

			loader.processFileForCpp(input, functions, classes,
					functionTemplates, classTemplates);

			// remove specified functions from classes, functions, templates,
			// class templates
			for (CppClass oneClass : classes) {
				List<CFunction> funcToRemove = new ArrayList<CFunction>();
				for (int j = 0; j < toExclude.length; j++) {
					for (CFunction oneFunc : oneClass.functions) {
						// build the function fully scoped name
						String scopedName = oneClass.className + "::"
								+ oneFunc.functionName;
						if (toExclude[j].compareTo(scopedName) == 0) {
							funcToRemove.add(oneFunc);
						}
					}
				}
				
				// same thing for constructors
				List<CFunction> constructorToRemove = new ArrayList<CFunction>();
				for (int j = 0; j < toExclude.length; j++) {
					for (CFunction oneFunc : oneClass.constructors) {
						// build the function fully scoped name
						String scopedName = oneClass.className + "::"
								+ oneFunc.functionName;
						if (toExclude[j].compareTo(scopedName) == 0) {
							constructorToRemove.add(oneFunc);
						}
					}
				}
				
				// same thing for destructors
				List<CFunction> destructorToRemove = new ArrayList<CFunction>();
				for (int j = 0; j < toExclude.length; j++) {
					for (CFunction oneFunc : oneClass.destructors) {
						// build the function fully scoped name
						String scopedName = oneClass.className + "::"
								+ oneFunc.functionName;
						if (toExclude[j].compareTo(scopedName) == 0) {
							destructorToRemove.add(oneFunc);
						}
					}
				}

				// now just keep functions in the keepOnly list
				if (toKeep != null) {
					for (CFunction oneFunc : oneClass.functions) {
						String scopedName = oneClass.className + "::"
								+ oneFunc.functionName;
						boolean foundFunction = false;
						for (int j = 0; j < toKeep.length; j++) {
							if (toKeep[j].compareTo(scopedName) == 0) {
								foundFunction = true;
								break;
							}
						}
						if (foundFunction == false) {
							funcToRemove.add(oneFunc);
						}
					}
				}

				// now remove the specified fully scoped functions
				for (CFunction oneFunc : funcToRemove) {
					oneClass.functions.remove(oneFunc);
					System.out
							.println("Removed operation "
									+ oneClass.className
									+ "::"
									+ oneFunc.functionName
									+ " because it is in the exclusion list or not in the keep list.");
				}
				
				for (CFunction oneFunc : constructorToRemove) {
					oneClass.constructors.remove(oneFunc);
					System.out
							.println("Removed constructor "
									+ oneClass.className
									+ "::"
									+ oneFunc.functionName
									+ " because it is in the exclusion list or not in the keep list.");
				}
				
				for (CFunction oneFunc : destructorToRemove) {
					oneClass.destructors.remove(oneFunc);
					System.out
							.println("Removed destructor "
									+ oneClass.className
									+ "::"
									+ oneFunc.functionName
									+ " because it is in the exclusion list or not in the keep list.");
				}
			}

			// if a class has no operations to generate (either because
			// they are filtered out, or because there were no operations
			// from the beginning, then I shall not generate any code
			// for this class. So remove the class from the class list.
			List<CppClass> classesToRemove = new ArrayList<CppClass>();

			for (CppClass oneClass : classes) {
				if((oneClass.functions.size() == 0) &&
					(oneClass.constructors.size() == 0) &&
					(oneClass.destructors.size() == 0))
				{
					classesToRemove.add(oneClass);
				} 
			}

			for(CppClass oneClass : classesToRemove)
			{
				classes.remove(oneClass);
			}

			
			System.out.println("found " + classes.size() + " classes in file");

			writeMockHeaderCpp(functions, classes, functionTemplates,
					classTemplates, outputHeader, header, headerPrefix, noMock);
			writeMockBodyCpp(functions, classes, output, header, filename,
					headerPrefix, noMock);
		}
	}

	private static String getVerifyAllBody(String filename,
			List<CFunction> functions, List<CppClass> classes) {
		String res = "static void opmock_verify_all_mocks_in_this_header()\n{\n";

		if (functions != null) {
			for (CFunction oneFunc : functions) {
				res += "    " + oneFunc.functionName;
				if (oneFunc.overload > 0) {
					res += Integer.toString(oneFunc.overload);
				}
				res += "_VerifyMock ();\n";
			}
		}

		if (classes != null) {
			for (CppClass oneClass : classes) {
				res += "    " + oneClass.className + "_Mock"
						+ "::VerifyMock ();\n";
			}
		}

		res += "}\n\n";

		return res;
	}

	private static void writeMockBodyCpp(List<CFunction> functions,
			List<CppClass> classes, String output, String header,
			String filename, String headerPrefix, boolean noMock) {
		try {
			PrintWriter out = new PrintWriter(new BufferedWriter(
					new FileWriter(output)));

			out.println("/* OPMOCK GENERATED C++ CODE - DO NOT MODIFY */\n");

			out.println("#include <stdio.h>\n");
			out.println("#include <string.h>\n");

			out.println("#include \"" + headerPrefix + filename + "_stub.hpp"
					+ "\"\n");

			// write structs used by classes
			for (CppClass oneClass : classes) {
				out.print(StructWriter.writeStructs(oneClass.functions,
						oneClass.className));
			}

			// write structs used by free C++ functions
			String supportStructs = StructWriter.writeStructs(functions, "");
			out.println(supportStructs);

			if (!noMock) {
				out.print(getResetAllBody(filename, functions, classes));
				out.print(getVerifyAllBody(filename, functions, classes));
			}

			for (CFunction oneFunc : functions) {
				out.print(oneFunc.getMockBody(""));
				out.print(oneFunc.getResetBody(""));
				out.print(oneFunc.getCallbackBody("", false, noMock));
				out.print(oneFunc.getVerifyBody(""));
				out.print(oneFunc.getExpectAndReturnBody(noMock));

			}

			for (CppClass oneClass : classes) {
				out.print(oneClass.getConstructorBodies());
				out.print(oneClass.getDestructorBody());
				out.print(oneClass.getMockBodies(noMock));
				if (!noMock) {
					out.print(oneClass.getResetBodies());
					out.print(oneClass.getClassResetBody());
				}
				out.print(oneClass.getCallbackBodies(noMock));
				if (!noMock) {
					out.print(oneClass.getVerifyBodies());
					out.print(oneClass.getClassVerifyBody());
					out.print(oneClass.getExpectAndReturnBodies(noMock));
				}
			}

			out.close();

		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	private static void writeMockHeaderCpp(List<CFunction> functions,
			List<CppClass> classes, List<CFunction> functionTemplates,
			List<CppClass> classTemplates, String output, String header,
			String headerPrefix, boolean noMock) {

		// generate the header guard from the file name
		String guard = (new File(output)).getName();
		guard = guard.replace('.', '_') + "_";
		guard = guard.replace('-', '_');
		guard = guard.toUpperCase();

		try {
			PrintWriter out = new PrintWriter(new BufferedWriter(
					new FileWriter(output)));

			out.println("/* OPMOCK GENERATED C++ CODE - DO NOT MODIFY */\n");

			// mock definitions
			out.print("#ifndef " + guard + "\n");
			out.print("#define " + guard + "\n\n");

			out.print("#include \"" + headerPrefix + header + "\"\n\n");
			out.print("#include \"opmock.h\"\n");

			// expect and return functions
			for (CFunction oneFunc : functions) {
				String mockStart = oneFunc.getExpectAndReturnPrototype("");
				out.println(mockStart);
			}
			out.println();

			// mock reset functions
			// one reset function per mocked function
			for (CFunction oneFunc : functions) {
				out.println(oneFunc.getMockReset());
			}
			out.println();

			// mock with callback functions for complex cases
			for (CFunction oneFunc : functions) {
				out.println(oneFunc.getMockWithCallback());
			}
			out.println();

			for (CFunction oneFunc : functions) {
				out.println(oneFunc.getMockVerify());
			}
			out.println();

			// write forward declaration of the classes, because they are used
			// by the callbacks..
			for (CppClass oneClass : classes) {
				out.print(oneClass.getForwardDeclaration());
			}
			out.println();

			// write callback definitions
			for (CppClass oneClass : classes) {
				out.print(oneClass.buildClassTypedefs());
			}

			for (CppClass oneClass : classes) {
				out.print(oneClass.getDefinition(noMock));
			}
			out.println();

			// write function templates
			// TODO autres fonctions associees callbacks, reset, etc
			// for (CFunction oneFunc : functionTemplates) {
			// out.print(oneFunc.getTemplateBody(useImpl));
			// }

			out.println("#endif\n");
			out.close();

		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}

	}

	private static void writeMockHeader(List<CFunction> functions,
			String output, String header, boolean noMock, String headerPrefix) {

		// generate the header guard from the file name
		String guard = (new File(output)).getName();
		guard = "_" + guard.replace('.', '_');
		guard = guard.replace('-', '_');
		guard = guard.toUpperCase();

		try {
			PrintWriter out = new PrintWriter(new BufferedWriter(
					new FileWriter(output)));

			out.println("/* OPMOCK GENERATED CODE - DO NOT MODIFY */\n");

			// mock definitions
			out.print("#ifndef " + guard + "\n");
			out.print("#define " + guard + "\n\n");

			out.print("#include \"" + headerPrefix + header + "\"\n\n");
			out.print("#include \"opmock.h\"\n");

			out.println("#ifdef __cplusplus");
			out.println("extern \"C\" {");
			out.println("#endif\n");

			if (!noMock) {
				// expect and return functions
				for (CFunction oneFunc : functions) {
					String mockStart = oneFunc
							.getExpectAndReturnPrototypeStart("", false);
					out.print(mockStart);
					out.println(";");
				}
				out.println();

				// mock reset functions
				// one reset function per mocked function
				for (CFunction oneFunc : functions) {
					out.println(oneFunc.getMockReset());
				}
				out.println();
			}

			// mock with callback functions for complex cases
			for (CFunction oneFunc : functions) {
				out.println(oneFunc.getMockWithCallback());
			}
			out.println();

			if (!noMock) {
				// verify for the functions
				// one verify per function as each of them has a dedicated
				// struct
				for (CFunction oneFunc : functions) {
					out.println(oneFunc.getMockVerify());
				}
				out.println();
			}

			out.println("#ifdef __cplusplus");
			out.println("}");
			out.println("#endif");

			out.println("#endif\n");
			out.close();

		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	private static String getResetAllBody(String filename,
			List<CFunction> functions, List<CppClass> classes) {
		String res = "static void opmock_reset_all_mocks_in_this_header()\n{\n";

		for (CFunction oneFunc : functions) {
			res += "    " + oneFunc.functionName;
			if (oneFunc.overload > 0) {
				res += Integer.toString(oneFunc.overload);
			}
			res += "_MockReset ();\n";
		}

		if (classes != null) {
			for (CppClass oneClass : classes) {
				res += "    " + oneClass.className + "_Mock"
						+ "::MockReset ();\n";
			}
		}

		res += "}\n\n";

		return res;
	}
}
