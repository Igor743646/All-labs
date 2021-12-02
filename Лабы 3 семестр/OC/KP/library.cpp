#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <filesystem>

#define LIBDLL extern "C"

LIBDLL char* get_file (const char* path) {
	try {
		std::ifstream file;
		file.open(path, std::fstream::in);
		if (!file) {
			return (char *)"Can't open or not available\n";
		} else {
			std::string result;
			char a;
			while (file.get(a)) {
				result += a;
			}

			file.close();
			return (char*) result.c_str();
		}
	} catch (const std::exception &e) {
		std::cout << e.what() << "\n";
	} catch (...) {
		std::cout << "Everything is bad :(\n";
	}
	return (char*)"No such file(";
}

LIBDLL char* get_files (const char* path) {
	try {
		namespace fs = std::filesystem;
		std::string result = "";
	    for (auto & p : fs::directory_iterator(path)) {
	    	
	        result += p.path().string() + "\n";
	    }
	    std::cout << result;
	    return (char*)result.c_str();
	} catch (const std::exception &e) {
		std::cout << e.what() << "\n";
	} catch (...) {
		std::cout << "Everything is bad :(\n";
	}
	return (char*)"No such directory(";
}

LIBDLL void sdf (const char* path) {
	printf("%s\n", path);
	return;
}


LIBDLL int delete_file (const char* path) {
	try {
		return remove(path);
	} catch (const std::exception &e) {
		std::cout << e.what() << "\n";
	} catch (...) {
		std::cout << "Everything is bad :(\n";
	}
	return 0;
}

LIBDLL long long get_file_size (const char* path) {
	try {
		std::ifstream file;
		file.open(path, std::ifstream::ate);
		if (!file) {
			return -1;
		} else {
			return file.tellg();
		}
	} catch (const std::exception &e) {
		std::cout << e.what() << "\n";
	} catch (...) {
		std::cout << "Everything is bad :(\n";
	}
	return -1;
}

