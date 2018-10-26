#include "Helberg_Functions.h"

using namespace std;

bool Sort_Vector_Int(vector<int> i, vector<int> j){         //Sorts the temp vector
    return (i.size() < j.size());
}    

length_t Power(int n, int m){                     //Returns the power of one to the other as an int
    if (m == 0) return 1;
    else if (m == 1) return n;
    length_t product = n;
    for (int i = 1; i < m; i++){
        product *= n;
    }
    return product;
}

length_t Moment(int code, int n, int q, int d){        //Calculates the moment
                            //bits vs modding vs array of ints
    length_t sum = 0;
    for (int i = 1; i <= n; i++){
        if (weights[i][d]){
            sum += weights[i][d] * ((code & (3 * Power(4, i - 1))) >> ((i - 1) * 2));
        }
        else{
            sum += Weight(i, q, d) * ((code & (3 * Power(4, i - 1))) >> ((i - 1) * 2));
        }
    }
    return sum;
}
/*{
    first_group = (digit & 0xC0) >> 6; //192
    second_group = (digit & 0x30) >> 4;   //48
    third_group = (digit & 0x0C) >> 2;   //12
    fourth_group = (digit & 0x03);      //3
}*/
length_t Weight(int i, int q, int d){            //Calculates the weight
    if (weights[i][d])
        return weights[i][d];
    else if (i <= 0)
        return 0;
    else if (i == 1)
        return 1;
    int j;  length_t sum = 0;
    for (j = 1; j <= d; j++){
        sum += Weight((i - j), q, d);
    }
    sum = 1 + ((q - 1) * sum);
    weights[i][d] = sum;
    return sum;
}
