#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <shellapi.h>
#include <string>

#define RESULT_FILE_CPP "result_cpp.txt"
#define RESULT_FILE_C "result_c.txt"
#define FIND_NUMBER
#if defined(FIND_NUMBER) && defined(FIZZ_BUZZ)
#error Both configs defined
#endif

// in order not to collide with main from student solution and current main
#pragma comment(linker, "/subsystem:windows")
#pragma comment(lib, "shell32.lib")

// declare the main of the student solution
int main();

int read_assert(std::fstream &file, const char* variable)
{
	while (true)
	{
		std::string str;
		file >> str;

		if (file.fail()) return 1;
		if (!_stricmp(str.c_str(), variable)) return 0;
	}
}

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

bool is_empty(std::fstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
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
	target.open(RESULT_FILE_CPP, std::ios::in);

	if (is_empty(target))
	{
		target.close();
		target.open(RESULT_FILE_C, std::ios::in);
	}

	//
	// solve test case by ourselves
	//
	#if defined(FIND_NUMBER)
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
	#elif defined(FIZZ_BUZZ)
	#pragma message("Building fizz buzz")
	size_t n;
	source >> n;
	for (size_t i = 0; i < n; ++i)
	{
		long long x;
		source >> x;

		if (source.fail())
		{
			if (result != 0)
			{
				return 0;
			}
			
			return 1;
		}

		if (x % 3 == 0 && x % 5 == 0)
		{
			if (read_assert(target, "fizzbuzz")) return 1;
		}
		else if(x % 3 == 0)
		{
			if (read_assert(target, "fizz")) return 1;
		}
		else if (x % 5 == 0)
		{
			if (read_assert(target, "buzz")) return 1;
		}
		else
		{
			if (read_assert(target, x)) return 1;
		}
	}
	#else
	#error "FIND_NUMBER or FIZZ_BUZZ must be defined"
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
	FILE* fp;
	FILE* rfp;
	std::fstream case_file;
	case_file.open(filename, std::ios::in);
	errno_t err = freopen_s(&fp, filename, "r", stdin);

	if (err != 0 || !case_file.is_open())
	{
		return 1;
	}

	//
	// to this file we will write the results
	//
	std::fstream result_file;
	result_file.open(RESULT_FILE_CPP, std::ios::out);
	err = freopen_s(&rfp, RESULT_FILE_C, "w", stdout);

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
	fclose(rfp);
	fclose(fp);

	//
	// restore original streams
	//
	std::cin.rdbuf(stream_buffer_cin);
	std::cout.rdbuf(stream_buffer_cout);

	// 
	// checking the answer depending on task
	//
	auto status = check(result, filename);

	remove(RESULT_FILE_CPP);
	remove(RESULT_FILE_C);
	
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