#include <vector>
#include <cmath>
#include <utility>
#include <cstdint>
#include <string>
#include <unordered_map>

using namespace std;

class Solution { 
public:
    vector<string> invalidTransactions(vector<string>& transactions) {

        //A transaction is invalid if:
        //
        //1. Amount > 1000
        //
        //2. There is another transaction with the same name and different city
        //And it occurs within 60 minutes of the other transaction
        
        //String indices: 1. Transaction name
        //                2. Time
        //                3. Amount of money
        //                4. City name

        //In the hashmap I will store the transaction name and indeces
        
        unordered_map<string, vector<int>> map;

        string current_string{};
        uint8_t current_field{};
        vector<tuple<int, int, string>> fields;

        uint16_t time{};
        uint16_t amount{};
        string city{};

        vector<string> return_vec;

        vector<int> invalid_indeces;

        for(auto i{0uz}; i < transactions.size(); ++i)
        {
            invalid_indeces.push_back(0);
            current_field = 0;
            current_string.clear();
            city.clear();
            amount = 0;
            time = 0;
            for(auto j{0uz}; j < transactions[i].size(); ++j)
            {
                if(transactions[i][j] == ',')
                {
                    if(current_field == 0)
                    {
                        map[current_string].push_back(i);
                        current_string.clear();
                    }
                    else if(current_field == 1)
                    {
                        time = stoi(current_string);
                        current_string.clear();
                    }
                    else if(current_field == 2)
                    {
                        amount = stoi(current_string);
                        if(amount > 1000)
                        {
                            invalid_indeces[i] = 1;
                            current_string.clear();
                            return_vec.push_back(transactions[i]);
                        }
                        current_string.clear();
                    }
                    ++current_field;
                }
                else if(j + 1 == transactions[i].size())
                {
                    current_string.push_back(transactions[i][j]);
                    city = current_string;
                    fields.push_back( {time, amount, city} );
                    city.clear();
                    current_string.clear();
                }
                else
                {
                    current_string.push_back(transactions[i][j]);
                }
            }
        }
        for(auto i{0uz}; i < transactions.size(); ++i)
        {
            current_string.clear();
            uint16_t j{};
            while(transactions[i][j] != ',')
            {
                current_string.push_back(transactions[i][j]);
                ++j;
            }
            for(auto d{0uz}; d < map[current_string].size(); ++d)
            {
                if(map[current_string][d] != i)
                {
                    if( abs(get<0>(fields[i]) 
                        -get<0>(fields[map[current_string][d]])) <= 60 &&
                        ( get<2>(fields[i]) != get<2>(fields[map[current_string][d]]) ))
                    {
                        if(invalid_indeces[i] == 0)
                        {
                            invalid_indeces[i] = 1;
                            return_vec.push_back(transactions[i]);
                        }
                        if(invalid_indeces[map[current_string][d]] == 0)
                        {
                            invalid_indeces[map[current_string][d]] = 1;
                            return_vec.push_back(transactions[map[current_string][d]]);
                        }
                    }
                }
            }
        }
        return return_vec;
        
    }
};
