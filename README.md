# C++ File Indexer

A command-line file indexing tool built in C++20. The program recursively scans a directory, collects file metadata, and provides options for searching and analysing the indexed files.

This project was built to practise modern C++ concepts including `std::filesystem`, structs, vectors, maps, error handling, modular program structure, and automated testing with GoogleTest.

## Features

* Recursively indexes files within a directory
* Records file path, filename, extension, and size
* Skips recursion into `.git` and `build` directories
* Search files by extension
* Search files by filename
* Search files by minimum file size
* Case-insensitive filename and extension searches
* Displays index statistics including:

  * Total number of files
  * Total size
  * Average file size
  * Largest file
  * Smallest file
  * File counts by extension
* Handles invalid directories and filesystem errors
* Automated unit tests using GoogleTest and CTest

## Technologies

* C++20
* CMake
* GoogleTest
* CTest
* `std::filesystem`

## Project Structure

```text
cpp-file-indexer/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── include/
│   └── file_indexer.h
├── src/
│   ├── file_indexer.cpp
│   └── main.cpp
└── tests/
    └── file_indexer_tests.cpp
```

## Building

From the project directory, configure the CMake build:

```cmd
cmake -S . -B build
```

Build the Release version:

```cmd
cmake --build build --config Release
```

The executable will be created at:

```text
build\Release\fileindex.exe
```

## Running

Provide a directory path as a command-line argument.

Example:

```cmd
build\Release\fileindex.exe "C:\Users\YourName\Documents"
```

The program will recursively scan the directory and display the files it finds before presenting the search and statistics menu.

## Testing

The project uses GoogleTest for automated unit testing.

After building, run:

```cmd
cd build
ctest -C Release
```

The tests cover functionality including:

* Converting text to lowercase
* Searching by file extension
* Searching by filename
* Searching by minimum file size
* Case-insensitive searches
* Empty search results
* Calculating file statistics
* Handling an empty file list

## Example

A typical session starts by providing a directory:

```text
File Indexer starting...
Argument 0: build\Release\fileindex.exe
Argument 1: C:\Users\YourName\Documents

Directory found.
```

The indexer then scans the directory and reports the files and their metadata.

After indexing, a menu allows the user to search the results or display statistics.

## Design

The project separates the command-line interface from the indexing functionality.

`main.cpp` is responsible for handling command-line arguments and interacting with the user, while `file_indexer.cpp` contains the reusable indexing, searching, and statistics functionality.

The `FileInfo` structure is used to represent metadata for each indexed file, while the `Statistics` structure stores calculated information about the complete index.

Filesystem operations use `std::error_code` where appropriate so that individual filesystem errors can be handled without immediately terminating the program.

## Future Improvements

Possible future improvements include:

* Sorting search results
* Additional search filters
* Exporting the index to CSV or JSON
* Persisting an index between program runs
* Improved command-line argument handling
* Performance improvements for very large directory trees

## Author

Conor Briggs

This project is part of my C++ development portfolio and was created to demonstrate practical programming, software structure, testing, and problem-solving skills.
