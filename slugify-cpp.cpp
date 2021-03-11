/* 
    http://www.17study.com.cn
    andrewWang@sina.com
*/

#include "slugify-cpp.hpp"

using namespace std;

#define POINTERLENGTH 389253
string MAPPING;
unsigned char BUF[POINTERLENGTH];

std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> CVT;

struct Ptr {
    uint16_t offset;
    uint8_t len;
} __attribute__((packed));

struct Ptr *charPtr = (struct Ptr *)BUF;
/*
template<typename tStringType, typename tTraits = typename tStringType::traits_type>
void print_code_unit_sequence(tStringType str)
{
    using char_type = typename tTraits::char_type;
    static_assert(std::is_same<char_type, char>::value || std::is_same<char_type, char16_t>::value || std::is_same<char_type, char32_t>::value, "error");
    using unsigned_char_type = typename std::make_unsigned<char_type>::type;
    using unsigned_int_type = typename std::make_unsigned<typename tTraits::int_type>::type;
    int w = std::is_same<char, char_type>::value ? 2 : std::is_same<char16_t, char_type>::value ? 4 : 8;
    for(auto c : str) {
        auto value = static_cast<unsigned_int_type>(static_cast<unsigned_char_type>(c));
        std::cout << "0x" << std::hex << std::uppercase << std::setw(w) << std::setfill('0') << value << ' ';
    }
}
*/
string readMapping(){
    std::ifstream t("mapping.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    return str;
}
void readPointer(unsigned char *p){
    std::ifstream infile("pointers.bin");
    infile.read((char *)p, POINTERLENGTH);
}
int LE2BE(int c){
    return ((c&0xff) << 8) + ((c&0xff00)>>8);
}

void dumpPointer(){
    int len=POINTERLENGTH/3;
    for(int i=0;i<0x300;i++){
        cout << hex << charPtr[i].offset << " : " << hex << (int)charPtr[i].len << endl;
    };
}

string slugify(string sin){
    auto s=CVT.from_bytes(sin);
    string rs=u8"";
    for(auto c:s){
        if ((uint16_t)c < 0xff){
            rs += ((char)c);
            continue;
        }
        int c1=(uint16_t)c;
        if (c1 >= POINTERLENGTH/3){
            continue;
        }
        int offset=(int)charPtr[c1].offset;
        int len=(int)charPtr[c1].len;
        if(offset > MAPPING.length()-len){
            continue;
        }
        for(auto cs:MAPPING.substr(offset,len)){
            rs += cs;
        }
    };

	std::regex e1("[^\\w\\s$*_+~.()\'\"-]");
	rs = std::regex_replace(rs, e1, "");

	std::regex e2("^\\s+|\\s+$");
	rs = std::regex_replace(rs, e2, "");

	std::regex e3("[-\\s]+");
	rs = std::regex_replace(rs, e3, "-");

	std::regex e4("#-$");
	rs = std::regex_replace(rs, e4, "");

    return rs;
};

void slugify_init(){
    MAPPING = readMapping();
    readPointer(BUF);
}

