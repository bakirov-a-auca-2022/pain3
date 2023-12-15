#include <bits/stdc++.h>

std::map<std::string, char>  read_codes(const std::string& path){
    std::ifstream file(path);
    std::string line;
    std::map<std::string, char> codes;
    while(std::getline(file, line)){
        if (line.empty()){
            continue;
        }
        //format of the line <code>:<symbol>
        std::string code = line.substr(0, line.find(':'));
        std::string symbol_str = line.substr(line.find(':') + 1);
        char symbol;
        if (symbol_str.empty()) {
            symbol = '\n';
        } else {
            symbol = symbol_str[0];
        }

        codes[code] = symbol;
    }

    return codes;
}

std::string read_bin(const std::string& path) {
    std::string binStr;
    std::ifstream file(path, std::ios::binary);
    char byte;
    while (file.get(byte)) {
        for (int i = 7; i >= 0; i--) {
            char bit = ((byte >> i) & 1) + '0';
            binStr += bit;
        }
    }

    return binStr;
}

std::string decode (std::map<std::string, char>& codes, const std::string& path){
    std::string res;
    std::string bin = read_bin(path);
    std::string currentCode;

    for (char c : bin) {
        currentCode += c;
        if (codes.count(currentCode)) {
            res += codes[currentCode];
            currentCode.clear();
        }
    }

    return res;
}

std::string read_file(const std::string& path){
    std::ifstream file(path);
    std::string line;
    std::string file_content;
    while(std::getline(file, line)){
        file_content += line + "\n";
    }
    return file_content;
}


int main(){
    auto codes =  read_codes("../encoded_pairs.txt");
    std::string res = decode(codes, "../encoded_text.bin");
    //std::string example = read_file("../ex_text.txt");
    std::ofstream out_file("../decoded_text.txt");
    out_file << res;
}