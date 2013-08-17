#!/bin/bash

#set -x
# main script to run opmock code generators
# this will first run SWIG to get an XML AST for a header file,
# then the opmock jar file to generate the actual mocks.
# ./opmock.sh --input-file /home/pascal/dev/essai_mycmock/chantier1/deps.h 
# --output-path $HOME/dev/essai_mycmock/chantier1/ --use-cpp no

START_DATE=`date +%s`

SCRIPT_DIR=$(dirname $0)
SWIG=$SCRIPT_DIR/swig/bin/swig
OPMOCK_JAR=$SCRIPT_DIR/opmock.jar

INPUT_FILE=""
OUTPUT_PATH=""
HEADER_PREFIX=""
HEADER=""
USE_CPP="no"
USE_RECURSE="no"
NO_MOCK="no"
SKIP_FUNCT=""
KEEP_ONLY=""
USE_IMPL="no"

# analyze parameters
NB_PARAMS=$#
MAX_PARAMS=$(($NB_PARAMS - 1))

for (( i = 0 ; i < $MAX_PARAMS ; i++ ))
do
    oneParam=$1
    if [ "$oneParam" = "--input-file" ]; then
	shift
	INPUT_FILE=$1
	shift
    elif [ "$oneParam" = "--output-path" ]; then
	shift
	OUTPUT_PATH=$1
	shift
    elif [ "$oneParam" = "--header-prefix" ]; then
	shift
	HEADER_PREFIX="--header-prefix ${1}"
	shift
    elif [ "$oneParam" = "--use-cpp" ]; then
	shift
	USE_CPP=$1
	shift
    elif [ "$oneParam" = "--no-mock" ]; then
	shift
	NO_MOCK=$1
	shift
    elif [ "$oneParam" = "--skip-funct" ]; then
	shift
	SKIP_FUNCT="--skip-funct ${1}"
	shift
    elif [ "$oneParam" = "--keep-only" ]; then
	shift
	KEEP_ONLY="--keep-only ${1}"
	shift
    elif [ "$oneParam" = "--use-impl" ]; then
	shift
	USE_IMPL=$1
	shift
    fi
done

# check mandatory parameters
if [ "$INPUT_FILE" = "" ]; then
    echo "ERROR : bad or missing --input-file. Please check your options."
    exit 1
fi

if [ "$OUTPUT_PATH" = "" ]; then
    echo "ERROR : bad or missing --output-path. Please check your options."
    exit 1
fi

HEADER=$(basename $INPUT_FILE)

if [ "$USE_CPP" = "yes" ]; then
    SWIG_CPP="-c++"
fi

if [ "$USE_RECURSE" = "yes" ]; then
    SWIG_RECURSE="-c++"
fi

# use the input filename as the output file name for swig
# cut the extension
swigfile=$(basename $INPUT_FILE)
swigfile=${swigfile%.*}


# call SWIG to the xml AST
echo "Calling SWIG to generate AST..."
SWIG_FEATURES="$SWIG_FEATURES -DOPMOCK_ACCESS"
export SWIG_FEATURES

$SWIG -includeall -ignoremissing -module module $SWIG_CPP -xmlout $HOME/${swigfile}.xml $INPUT_FILE
echo "Done."

# now call opmock to generate the headers and c/cpp files
echo "Calling Opmock to generate the mocks..."
java -jar $OPMOCK_JAR --input-file $HOME/${swigfile}.xml --output-path $OUTPUT_PATH \
    --header $HEADER --use-cpp $USE_CPP $HEADER_PREFIX --no-mock $NO_MOCK $SKIP_FUNCT $KEEP_ONLY --use-impl $USE_IMPL
echo "Done."

END_DATE=`date +%s`
DELTA_TIME="$(expr $END_DATE - $START_DATE)"

echo "Time to generate the mocks : $DELTA_TIME second(s)."

