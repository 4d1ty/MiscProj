#include "SimpleFile.hpp"

SimpleFile::SimpleFile(const std::string& path, file_mode_t mode)
{
	this->open(path, mode);
}

SimpleFile::~SimpleFile() {
	file.close();
}

bool SimpleFile::open(const std::string& path, file_mode_t mode) {
	this->filePath = path;
	this->fileMode = mode;
	this->file.open(path, mode);
	return this->isOpen();
}

bool SimpleFile::isOpen() {
	return this->file.is_open();
}

void SimpleFile::close() {
	if (this->isOpen())
		this->file.close();
}

void SimpleFile::flush() {
	if (this->isOpen())
		this->file.flush();
}

void SimpleFile::echo() {
	std::string line;
	while (std::getline(this->file, line)) {
		std::cout << line << "\n";
	}
}

void SimpleFile::write(const std::string& text) {


	if (!this->isOpen()) {
		std::cerr << "Error: No File opened to write\n";
		return;
	}
	if ((this->fileMode & FILE_WRITE) || (this->fileMode & FILE_APPEND)) {
		if (this->fileMode & FILE_APPEND) {
			this->file.seekp(0, std::ios::end);
		}
		this->file << text;
	}
	else {
		std::cerr << "Error: Write failed, file not opened in write or append mode\n";
		return;
	}
}

void SimpleFile::writeln(const std::string& text) {
	this->write(text + "\n");
}


void SimpleFile::append(const std::string& text) {
	if (!this->isOpen()) {
		std::cerr << "Error: No File opened to append\n";
		return;
	}
	if (this->fileMode & FILE_APPEND) {
		this->file.seekp(0, std::ios::end);
		this->file << text;
	}
	else {
		std::cerr << "Error: Write Failed, File not opened in append mode\n";
		return;
	}
}


void SimpleFile::read(std::string& buffer) {
	if (!this->isOpen()) {
		std::cerr << "Error: No File opened to append\n";
		return;
	}
	if (this->fileMode & FILE_READ) {
		this->seekToStart();
		std::string line;
		while (std::getline(this->file, line))
		{
			buffer.append(line + "\n");
		}
	}
	else {
		std::cerr << "Error: Read Failed, File not opened in read mode\n";
		return;
	}
}

int SimpleFile::size() {
	if (!this->isOpen()) {
		std::cerr << "Error: No File opened to append\n";
		return -1;
	}
	auto currentPos = this->file.tellg();
	this->file.seekg(0, std::ios::end);
	int size = static_cast<int>(this->file.tellg());
	this->file.seekg(currentPos);
	return size;
}

void SimpleFile::clear() {
	if (!this->isOpen()) {
		std::cerr << "Error: No File opened to clear\n";
		return;
	}

	if ((this->fileMode & FILE_WRITE) || (this->fileMode & FILE_APPEND)) {
		this->close();
		auto reopenMode = (this->fileMode & FILE_BIN) | std::ios::out | std::ios::trunc;
		this->open(this->filePath, reopenMode);
		this->fileMode = reopenMode;

	}
	else {
		std::cerr << "Error: Clear Failed, File not opened in write or append mode\n";
		return;
	}
}

std::optional<std::string> SimpleFile::readAll() {
	if (!this->isOpen()) {
		std::cerr << "Error: No File opened to read\n";
		return std::nullopt;
	}
	if (this->fileMode & FILE_READ) {
		std::string buffer;
		this->read(buffer);
		return buffer;
	}
	std::cerr << "Error: Read Failed, File not opened in read mode\n";
	return std::nullopt;
}

std::optional<std::vector<std::string>> SimpleFile::readLines() {
	if (!this->isOpen()) {
		std::cerr << "Error: No File opened to read\n";
		return std::nullopt;
	}
	if (this->fileMode & FILE_READ) {
		this->seekToStart();
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(this->file, line))
		{
			lines.push_back(line);
		}
		return lines;
	}
	std::cerr << "Error: Read Failed, File not opened in read mode\n";
	return std::nullopt;
}

file_mode_t SimpleFile::getFileMode() {
	return this->fileMode;
}

std::string SimpleFile::getFilePath() {
	return this->filePath;
}


void SimpleFile::writeList(const std::vector<std::string>& list) {
	for (auto& element : list) {
		this->writeln(element);
	}
}


void SimpleFile::seekToEnd() {
	this->file.clear();
	this->file.seekg(0, std::ios::end);
}

void SimpleFile::seekToStart() {
	this->file.clear();
	this->file.seekg(0, std::ios::beg);
}