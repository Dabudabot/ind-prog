#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <shellapi.h>

#pragma comment(linker, "/subsystem:windows")
#pragma comment(lib, "shell32.lib")

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
	std::fstream source;
	source.open(filename, std::ios::in);
	std::fstream target;
	target.open("result.txt", std::ios::in);

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

	auto status = endAssert(target);
	source.close();
	target.close();
	return status;
}

int test_runner(int (*solution)(), const char *filename)
{
	std::fstream case_file;
	case_file.open(filename, std::ios::in);

	std::fstream result_file;
	result_file.open("result.txt", std::ios::out);

	std::streambuf *stream_buffer_case_file = case_file.rdbuf();
	std::streambuf *stream_buffer_result_file = result_file.rdbuf();

	const auto stream_buffer_cout = std::cout.rdbuf();
	const auto stream_buffer_cin = std::cin.rdbuf();

	std::cin.rdbuf(stream_buffer_case_file);
	std::cout.rdbuf(stream_buffer_result_file);

	int result = solution();

	case_file.close();
	result_file.close();

	std::cin.rdbuf(stream_buffer_cin);
	std::cout.rdbuf(stream_buffer_cout);

	auto status = check(result, filename);
	
	return status;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, int nCmdShow)
{
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

	std::cout << "Running test: " << argv[1] << " ";

	const auto result = test_runner(main, argv[1]);

	i = 0;
	for (; i < argc; ++i)
	{
		free(argv[i]);
	}

	free(argv);

	std::cout << result << std::endl;
	return result;
}