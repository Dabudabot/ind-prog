﻿#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <shellapi.h>

#ifdef FIND_NUMBER & FIZZ_BUZZ
#error Both configs defined
#endif

// in order not to collide with main from student solution and current main
#pragma comment(linker, "/subsystem:windows")
#pragma comment(lib, "shell32.lib")

// declare the main of the student solution
int main();

int read_assert(std::fstream &file, const int variable)
{
	while (true)
	{
		const auto symbol = file.get();

		if (symbol == EOF)
		{
			return 1;
		}

		if (isdigit(symbol))
		{
			file.putback(symbol);
			int var = 0;
			file >> var;

			if (var != variable)
			{
				return 1;
			}

			return 0;
		}
	}
}

int endAssert(std::fstream &file)
{
	char c;
	while ((c = file.get()) != EOF)
	{
		if (isdigit(c))
		{
			return 1;
		}
	}
	return 0;
}

int check(int result, const char *filename)
{
	//
	//	open test case
	//
	std::fstream source;
	source.open(filename, std::ios::in);

	//	open student`s solution result
	std::fstream target;
	target.open("result.txt", std::ios::in);

	//
	// solve test case by ourselves
	//
	#ifdef FIND_NUMBER
	#pragma message("Building find number")
	size_t m, n;
	std::unordered_map<size_t, size_t> array;
	source >> m >> n;
	for (size_t i = 0; i < n; ++i)
	{
		int x;
		source >> x;

		if (source.fail() || x < 0)
		{
			if (result != 0)
			{
				return 0;
			}

			return 1;
		}

		++array[x];
	}

	for (size_t i = 0; i < m; ++i)
	{
		if (array.find(i) == array.end())
		{
			if (read_assert(target, i))
			{
				source.close();
				target.close();
				return 1;
			}
		}
	}
	#else
	#ifdef FIZZ_BUZZ
	#pragma message("Building fizz buzz")
	#error "NOT READY"
	#else
	#error "FIND_NUMBER or FIZZ_BUZZ must be defined"
	#endif
	#endif

	auto status = endAssert(target);
	source.close();
	target.close();
	return status;
}

int test_runner(int (*solution)(), const char *filename)
{
	//
	// open file with current test case
	//
	std::fstream case_file;
	case_file.open(filename, std::ios::in);

	//
	// to this file we will write the results
	//
	std::fstream result_file;
	result_file.open("result.txt", std::ios::out);

	//
	//	get streams to the file
	//
	std::streambuf *stream_buffer_case_file = case_file.rdbuf();
	std::streambuf *stream_buffer_result_file = result_file.rdbuf();

	//
	//	save current cin and cout streams
	//
	const auto stream_buffer_cout = std::cout.rdbuf();
	const auto stream_buffer_cin = std::cin.rdbuf();

	//
	//	set streams to files
	//
	std::cin.rdbuf(stream_buffer_case_file);
	std::cout.rdbuf(stream_buffer_result_file);

	//
	//	run student`s solution,
	//  it must return 0 if solution is solvable and 1 otherwise
	//
	int result = solution();

	//
	// test done
	//
	case_file.close();
	result_file.close();

	//
	// restore original streams
	//
	std::cin.rdbuf(stream_buffer_cin);
	std::cout.rdbuf(stream_buffer_cout);

	// 
	// checking the answer depending on task
	//
	auto status = check(result, filename);
	
	//
	// if solution of the students is right resut 0, otherwise 1
	//
	return status;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, int nCmdShow)
{
	//
	// Prepare command line arguments
	//
	int argc;
	const auto lp_argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	const auto argv = static_cast<char **>(malloc(argc * sizeof(char *)));
	auto i = 0;
	for (; i < argc; ++i)
	{
		const int size = wcslen(lp_argv[i]) + 1;
		argv[i] = static_cast<char *>(malloc(size));
		wcstombs(argv[i], lp_argv[i], size);
	}
	LocalFree(lp_argv);

	// 
	// start test, main in this case is main from student`s solution
	//
	const auto result = test_runner(main, argv[1]);

	//
	// cleanup command line args
	//
	i = 0;
	for (; i < argc; ++i)
	{
		free(argv[i]);
	}

	free(argv);

	//
	// if solution of the students is right resut 0, otherwise 1
	//
	return result;
}