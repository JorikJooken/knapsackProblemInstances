.PHONY: test example clean

CXX := g++
CXX_FLAGS := -std=c++11 -O2 -Werror -Wall -Wextra -pedantic-errors -fmax-errors=1

GENERATOR_SOURCE := generator.cpp
GENERATOR_EXECUTABLE := generatorExecutable

EXAMPLE_INPUT := testInputForGenerator.txt
EXAMPLE_OUTPUT := toyProblemInstance.txt

TEST_DIR := test
TEST_LOG := ${TEST_DIR}/test.log
TEST_OUTPUT_FILE := ${TEST_DIR}/test_output.log

all: ${GENERATOR_EXECUTABLE}

${GENERATOR_EXECUTABLE}: ${GENERATOR_SOURCE}
	@$(CXX) $(CXX_FLAGS) -o ${GENERATOR_EXECUTABLE} ${GENERATOR_SOURCE}

example: ${GENERATOR_EXECUTABLE}
	@./${GENERATOR_EXECUTABLE} < ${EXAMPLE_INPUT} > ${EXAMPLE_OUTPUT} 2>/dev/null

test: ${GENERATOR_EXECUTABLE}
	@# success
	@for N in 1 2 3 ; do \
		./${GENERATOR_EXECUTABLE} < ${TEST_DIR}/input_$$N.txt > ${TEST_OUTPUT_FILE} 2>${TEST_LOG} ; \
		diff ${TEST_DIR}/output_$$N.txt ${TEST_OUTPUT_FILE} > /dev/null; \
		if test $$? -eq 0; then \
			echo -e "Test $$N \033[32mpassed\033[0;39m"; \
		else \
			echo -e "Test $$N \033[31mfailed\033[0;39m"; \
		fi; \
	done
	@# failure
	@for N in 4 ; do \
		./${GENERATOR_EXECUTABLE} < ${TEST_DIR}/input_$$N.txt > ${TEST_OUTPUT_FILE} 2>${TEST_LOG} ; \
		if test $$? -ne 0; then \
			echo -e "Test $$N \033[32mpassed\033[0;39m"; \
		else \
			echo -e "Test $$N \033[31mfailed\033[0;39m"; \
		fi; \
	done

clean:
	rm -f ${GENERATOR_EXECUTABLE} ${EXAMPLE_OUTPUT} ${TEST_OUTPUT_FILE} ${TEST_LOG}
