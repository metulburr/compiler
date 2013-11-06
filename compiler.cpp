#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

class String{
    public:
        std::string str;
        std::vector<std::string> tokens;
        char delim;
    
        String(std::string string, char delimiter='\n'){
            str = string;
            delim = delimiter;
            tokens = split();
        }
        
        std::string 
        operator*(int num){
            std::string s;
            for (int i=0; i<num; i++){
                s += this->str;
            }
            return s;
        }
        
        bool 
        startswith(std::string search){
            if ( this->str.compare(0, search.length(), search) == 0)
                return true;
            else
                return false;
        }
        bool 
        endswith(std::string search){
            if (search.length() > str.length())
                return false;
            int len = str.length();
            int start = str.length() - search.length();
            if ( this->str.compare(start, len, search) == 0)
                return true;
            else
                return false;
        }
        
        //split self.str into vector
        std::vector<std::string> 
        split(){
            std::vector<std::string> v;
            std::stringstream ss(this->str);
            std::string temp;
            while( getline(ss, temp, this->delim)){
                v.push_back(temp);
            }
            return v;
        }
        
        //join vector of elements to one string by sep
        template <class T> std::string 
        join(const std::vector<T> &v, std::string sep="\n"){
            std::string s;
            for (auto i:v){
                s += i;
                s += sep;
            }
            return s;
        }
        
        std::string 
        upper(){
            std::string s = this->str;
            std::transform(s.begin(), s.end(), s.begin(), toupper);
            return s;
        }

        std::string 
        lower(){
            std::string s = this->str;
            std::transform(s.begin(), s.end(), s.begin(), tolower);
            return s;
        }

        std::string 
        replace(const std::string& find, const std::string& replacement) {
            std::string s = this->str;
            size_t pos = 0;
            while ((pos = s.find(find, pos)) != std::string::npos) {
                s.replace(pos, find.length(), replacement);
                pos += replacement.length();
            }
            return s;
        }
        
        std::string 
        strip(const std::string &whitespace = " \t\n"){
            std::string s = this->str;
            const auto start = s.find_first_not_of(whitespace);
            const auto end = s.find_last_not_of(whitespace);
            const auto range = end - start + 1;
            
            if (start == std::string::npos)
                return ""; // no content
            else
                return s.substr(start, range);
        }
        
        //if constructor arg is only a number, return true if between start and end, else false
        template <class T, class U> bool 
        between(T start, U end){
            double number;
            std::stringstream ss(this->str);
            ss >> number;
            
            if (number > start && number < end)
                return true;
            else
                return false;
        }
        
        
        
};



std::string 
splice(std::string s, int front=0, int back=0){
    std::string s2 = s.substr(front);
    std::string s3 = std::string(s2.rbegin(), s2.rend()).substr(back);
    return std::string(s3.rbegin(), s3.rend());
}

bool 
startswith(std::string str, std::string search){
    if ( str.compare(0, search.length(), search) == 0)
        return true;
    else
        return false;
}

std::string 
cha2str(char ch){
    std::stringstream ss;
    std::string s;
    ss << ch;
    ss >> s;
    return s;
}

bool 
is_op(char c){
    char ops[4] = {'+', '-', '*', '/'};
    for (auto op:ops){
        if (c == op){
            return true;
        }
    }
    return false;
}

std::string
translate(char c, bool type_only=false){
    if (isdigit(c))
        if (type_only)
            return "DIGIT";
        else
            return "DIGIT" + cha2str(c);
    else if (c == '.')
        return "PERIOD";
    else if (is_op(c))
        if (type_only)
            return "OP";
        else
            return "OP" + cha2str(c);
    else if (c == '=')
        return "ASSIGN";
    else if (c == '!')
        return "EXCLAM";
    else if (isalpha(c) || c == '_')
        if (type_only)
            return "CHAR";
        else
            return "CHAR" + cha2str(c);
    else if (c == '(')
        return "POPEN";
    else if (c == ')')
        return "PCLOSE";
    else if (c == '{')
        return "BOPEN";
    else if (c == '}')
        return "BCLOSE";
    else if (isspace(c))
        return "SPACE";
    else
        return "OTHER";
}



int main(){
    const char *input =
        "var_var = 1+7*31/1001\n";
    
    String filer(input);
    std::vector<std::string> lines = filer.split(), translated_line, tokens;
    std::vector< std::vector<std::string> > file;

    unsigned int line_number = 1;
    for (auto line:lines){
        int index = 0;
        std::string token_str;
        for (auto ch:line){
            std::cout << translate(ch) << std::endl;
            
            if (translate(ch, true) == translate(line[index-1], true)){
                //char is following previously same type
                token_str += ch;
                if (index+1 == line.length())
                    //push str to tokens on last char of line
                    tokens.push_back(token_str);
            }
            else{
                //char is starting a new type
                tokens.push_back(token_str);
                token_str = ch;
            }
            index++;
        }
        file.push_back(tokens);
        line_number++;
    }
    
    //print test
    for (auto i:file[0])
        std::cout << i << std::endl;
}
