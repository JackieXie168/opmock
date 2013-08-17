#!/bin/bash

main_file="main.c"
# start creating main file (main.c)
echo "#include \"opmock.h\"" > $main_file
header_array=()
functions_array=()

# analyze command line. I want all c and cpp files
# c files must end with .c or .C
# cpp files must end with .cpp or .cc or .CC or .c++
for f in "$@"
do
	echo "looking file : $f"

	# test if this is a C or C++ file
	filetype=""
	header_file=""

	suffix=${f: -2}

	if [ "$suffix" == ".c" ]
	then
		filetype="C"
		header_file=${f%.c}.h
	elif [ "$suffix" == ".C" ]
	then
		filetype="C"
		header_file=${f%.C}.h
	fi

	suffix=${f: -4}
	if [ "$suffix" == ".cpp" ]
	then
		filetype="CPP"
		header_file=${f%.cpp}.hpp
	elif [ "$suffix" == ".cc" ]
	then
		filetype="CPP"
		header_file=${f%.cc}.hpp
	elif [ "$suffix" == ".CC" ]
	then
		filetype="CPP"
		header_file=${f%.CC}.hpp
	elif [ "$suffix" == ".c++" ]
	then
		filetype="CPP"
		header_file=${f%.c++}.hpp
	fi

	TESTS=`cat $f|grep '^[ \t ]*void[\t ]test_[a-z,A-Z,_,0-9]*([\t ]*)'`

	# the array contains void, function_name( ), ( )
	# I have to ignore the void, and remove the () from the lines that contain it
	# then remove empty lines

	if [ "$filetype" != "" ]
	then
		#start creating header file
		#and main file as well
		header="#ifndef "
		macro=${header_file//./_}_
        # The following notation does not work with bash 3
        # so let's stick with an old, compatible one.
		#macro=${macro^^}
        macro=`echo ${macro} | tr '[:lower:]' '[:upper:]'` 
		header=$header$macro
		echo $header > $header_file

		header="#define "
		header=$header$macro
		echo $header >> $header_file
		echo "" >> $header_file

		header_array+=($header_file)

		# output all tests in the files (both header file and main file		
		for test in $TESTS
		do
			one_func=`echo $test|sed 's/([\t ]*)//'|sed 's/^void[\t ]*//'`
			if [ "$one_func" != "" ]
			then
				echo "void $one_func ();" >> $header_file
				functions_array+=($one_func)
			fi
		done

		# end header file
		echo "" >> $header_file
		echo "#endif" >> $header_file
		
	fi
done

# output the end of the main file
for one_header in ${header_array[@]}
do
	echo "#include \"$one_header\"" >> $main_file
done

echo "" >> $main_file
echo "int main(int argc, char *argv[])" >> $main_file
echo "{" >> $main_file
echo "  opmock_test_suite_reset();" >> $main_file

for one_test in ${functions_array[@]}
do
	echo "  opmock_register_test($one_test, \"$one_test\");" >>  $main_file
done

# end of main file
echo "  opmock_test_suite_run();" >> $main_file
echo "" >> $main_file
echo "  return 0;" >> $main_file
echo "}" >> $main_file
