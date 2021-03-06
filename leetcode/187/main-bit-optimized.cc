int add_char(int current, char c){
    if(c == 'A'){
        current |= 0;
    }else if(c == 'C'){
        current |= 1;
    }else if(c == 'G'){
        current |= 2;
    }else if(c == 'T'){
        current |= 3;
    }else assert(false);
    return current;
}

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        // Two 2^20-1 size table to store whether that pattern has occurred
        bitset<(1<<20)-1> occur_once;
        bitset<(1<<20)-1> occur_twice;
        // encode a 10-letter string as a 20 bits integer
        // i.e. A == 00, C == 01, G == 10, T == 11
        // i.e. a 10-letter string will appear like this:
        // ACCGT == 00,01,01,10,11
        int mask = (1 << 20) - 1; // a 20 bits mask
        vector<string> answers;
        int bound = s.length()-9;
        int current = 0;
        for(int i = 0; i < bound; i++){
            // Update current
            if(i != 0){
                // Remove the leftest two bits
                current = (current << 2) & mask;
                // Add the new character
                current = add_char(current, s[i+9]);
            }else{
                for(int j = i; j < i + 10; j++){
                    // left shift by 2
                    current <<= 2;
                    // Add the new char
                    current = add_char(current, s[j]);
                }
            }
            if(occur_twice[current]) continue;
            // If it has already occur once
            if(occur_once[current]){
                answers.push_back(string(s.begin()+i, s.begin()+i+10));
                occur_twice.set(current);
            }else{
                occur_once.set(current);
            }
        }
        return answers;
    }
};

