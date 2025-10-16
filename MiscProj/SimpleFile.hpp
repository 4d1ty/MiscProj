#ifndef SIMPLEFILE_HPP
#define SIMPLEFILE_HPP
#include <fstream>
#include <iostream>
#include <variant>
#include <optional>
#include <vector>
#include <string>



/// <summary>
/// Defines an alias for the file open mode type used in file stream operations.
/// </summary>
using file_mode_t = std::ios_base::openmode;

//CONSTANTS

/// <summary>
/// Open for reading
/// </summary>
constexpr file_mode_t FILE_READ = std::ios::in;
/// <summary>
/// Open for writing
/// </summary>
constexpr file_mode_t FILE_WRITE = std::ios::out;
/// <summary>
/// Append to the end of the file
/// </summary>
constexpr file_mode_t FILE_APPEND = std::ios::out | std::ios::app;
/// <summary>
/// Erase contents before writing
/// </summary>
constexpr file_mode_t FILE_TRUNC = std::ios::out | std::ios::trunc;
/// <summary>
/// Open and seek to the end (can still read/write anywhere)
/// </summary>
constexpr file_mode_t FILE_ATE = std::ios::ate;
/// <summary>
/// Open in binary mode (no newline conversions)	
/// </summary>
constexpr file_mode_t FILE_BIN = std::ios::binary;

/// <summary>
/// The default mode in which the file should be opened
/// </summary>
constexpr file_mode_t DEFAULT_MODE = FILE_READ | FILE_WRITE | FILE_APPEND;

/// <summary>
/// Represents a simple file handler for reading from and writing to files.
/// Its provieds simple api for handling files, don't expect robustness.
/// </summary>
class SimpleFile {
public:
	SimpleFile() = default;
	/// <summary>
	/// Constructs a SimpleFile object and opens the specified file with the given mode.
	/// </summary>
	/// <param name="path">The path to the file to open.</param>
	/// <param name="mode">The mode in which to open the file. Defaults to DEFAULT_MODE if not specified.</param>
	SimpleFile(const std::string&, file_mode_t = DEFAULT_MODE);

	/// <summary>
	/// Destroys the SimpleFile object and closes the associated file.
	/// </summary>
	~SimpleFile();

	/// <summary>
	/// Opens the file
	/// </summary>
	/// <param name="path"></param>
	/// <param name=""></param>
	/// <returns></returns>
	bool open(const std::string& path, file_mode_t = DEFAULT_MODE);

	/// <summary>
	/// Closes the file stream
	/// </summary>
	void close();

	/// <summary>
	/// Checks whether the resource is currently open.
	/// </summary>
	/// <returns>true if the resource is open; otherwise, false.</returns>
	bool isOpen();

	/// <summary>
	/// Flushes any buffered output to the file.
	/// </summary>
	void flush();

	/// <summary>
	/// Reads lines from the file and outputs them to the standard output.
	/// </summary>
	void echo();

	/// <summary>
	/// Appends the given text to the file, followed by a newline.
	/// </summary>
	/// <param name="text">The text to append to the file.</param>
	void append(const std::string&);

	/// <summary>
	/// Reads the contents of the file into the provided buffer.
	/// </summary>
	/// <param name="buffer">A reference to a string where the file contents will be stored.</param>
	void read(std::string&);

	/// <summary>
	/// Returns the size of a file in bytes.
	/// </summary>
	/// <returns>The size of the file in bytes, or a negative value if an error occurs.</returns>
	int size();

	/// <summary>
	/// Clears the contents of the file.
	/// </summary>
	void clear();

	/// <summary>
	/// Writes the specified string to the file.
	/// </summary>
	/// <param name="">The string to write.</param>
	void write(const std::string&);

	/// <summary>
	/// Writes a string followed by a newline character to the file.
	/// </summary>
	/// <param name="">The string to write</param>
	void writeln(const std::string&);

	/// <summary>
	/// Reads and returns the entire contents as a string.
	/// </summary>
	/// <returns>A string containing all the data that was read.</returns>
	std::optional<std::string> readAll();

	/// <summary>
	/// Reads and returns the entire contents as a vector<string>
	/// </summary>
	/// <returns></returns>
	std::optional<std::vector<std::string>> readLines();

	/// <summary>
	/// Get the file mode
	/// </summary>
	/// <returns></returns>
	file_mode_t getFileMode();

	/// <summary>
	/// Get the current file path
	/// </summary>
	/// <returns></returns>
	std::string getFilePath();

	/// <summary>
	/// Writes the elements of a list of strings.
	/// </summary>
	/// <param name="">A constant reference to a vector containing the strings to write.</param>
	void writeList(const std::vector<std::string>&);


	/// <summary>
	/// Seek to the end of the file
	/// </summary>
	void seekToEnd();

	/// <summary>
	/// Seek to the start of the file
	/// </summary>
	void seekToStart();


private:
	/// <summary>
	/// Path to the file
	/// </summary>
	std::string filePath;
	/// <summary>
	/// The Actual file stream
	/// </summary>
	std::fstream file;
	/// <summary>
	/// Mode in which the file is opened
	/// </summary>
	file_mode_t fileMode = DEFAULT_MODE;
};
#endif // !SIMPLEFILE_HPP