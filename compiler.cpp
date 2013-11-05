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
translate(char c){
    if (isdigit(c))
        return "DIGIT" + cha2str(c);
    else if (c == '.')
        return "PERIOD";
    else if (is_op(c))
        return "OP" + cha2str(c);
    else if (c == '=')
        return "ASSIGN";
    else if (isalpha(c) || c == '_')
        return "CHAR" + cha2str(c);
    else if (c == '(')
        return "OPENPAREN";
    else if (c == ')')
        return "CLOSEPAREN";
    else if (c == '{')
        return "OPENBRACKET";
    else if (c == '}')
        return "CLOSEBRACKET";
    else
        return "NONE";
}

int main(){
    const char *input =
        "var_var = (1.1+7)*3/44\n";
    
    String filer(input);
    std::vector<std::string> lines = filer.split(), translated_line;
    std::vector< std::vector<std::string> > file;

    unsigned int line_number = 1;
    for (auto line:lines){
        for (auto ch:line){
            //std::cout << "LINE: " << line_number << std::endl;
            std::string def = translate(ch);
            std::cout << def << std::endl;
            translated_line.push_back(def);
        }
        file.push_back(translated_line);
        line_number++;
    }
}
