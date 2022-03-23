#include <vector>
#include<iostream>
#include "Page.hpp"


using std::vector;
using namespace ariel;

void Page::newLines(int num){

    for(int i = 0 ; i < num ; i ++){
        vector<char> v (100,'_');
        rows.push_back(v);
    }
}

void Page::writeRange(int row,int col,Direction dir, int len, std::string data){
    
    //check if we have enough rows
    int currLen = rows.size();
    if(currLen == 0){
        currLen--; //in case where the page is empty
    }

    int linesToAdd;
    
    if(dir == Direction::Vertical){
        
        //Add new rows if needed
        linesToAdd =(len - (currLen - row));
        if(linesToAdd > 0){
            newLines(linesToAdd);
        } 
        //make sure that we are writing to empty cells
        for(size_t i = static_cast<size_t>(row); i < len + row; i++){
            
            if(rows.at(i).at(static_cast<size_t>(col)) != '_'){
                return;
            }
        }
        //write the actual data
        for(char c: data){
            rows.at(static_cast<size_t>(row)).at(static_cast<size_t>(col)) = c;
            row++;
        }
    }

    else{

        //throw an exception if we are out of the row
        if(len + col > 100){
            throw "Out of row error";
        }
        //Add new rows if needed
        int neededRows = (col + len -1) / 100;
        linesToAdd =(neededRows - (currLen - row));
        if(linesToAdd > 0){
            newLines(linesToAdd);
        } 
        int rowTemp = row;
        //make sure that we are writing to empty cells
        for(int i = col; i < col + len;i++){
            
            if(rows.at(static_cast<size_t>(rowTemp)).at(static_cast<size_t>(i % 100)) != '_'){
                return;
            }
            rowTemp = row + i /100;
        }
        rowTemp = row;
        //write the actual data
        
        for(char c: data){

            rows.at(static_cast<size_t>(row)).at(static_cast<size_t>(col)) = c;
            ++col;

            if(col == 100){
                col = 0;
                ++row;
            }
        }

    }


}

std::string Page::readPage(){
    std::string s = "";
    
    for(size_t i = 0 ; i < rows.size(); i++){

        s += std::to_string(i) + ": ";
        s += std::string(rows.at(i).data()) +"\n";

    }
    return s;
}

void Page::eraseData(int row,int col,Direction dir, int len){

    
    //check if we have enough rows
    int currLen = rows.size();
    if(currLen == 0){
        currLen--; //in case where the page is empty
    }
    int linesToAdd;

    if(dir == Direction::Vertical){
        
        //Add new rows if needed
        linesToAdd =(len - (currLen - row));
        if(linesToAdd > 0){
            newLines(linesToAdd);
        } 
        //make sure that we are writing to empty cells
        for(int i = row; i < len + row; i++){
            
            rows.at(static_cast<size_t>(i)).at(static_cast<size_t>(col)) = '~';
            
        }
    }

    else{
        if(len + col > 100){
            throw "Out of row error";
        }
        //Add new rows if needed
        int neededRows = (col + len -1) / 100;
        linesToAdd =(neededRows - (currLen - row));
        if(linesToAdd > 0){
            newLines(linesToAdd);
        } 
        int rowTemp = row;
        //make sure that we are writing to empty cells
        for(int i = col; i < col + len;i++){
            
            rows.at(static_cast<size_t>(rowTemp)).at(static_cast<size_t>(i % 100)) = '~';

            rowTemp = row + i /100;
        }



    }


}

std::string Page::readRange(int row, int col, Direction dir, int len){

    //fill the result string with '_' in case we want to read more then length of the notebook
    std::string res(static_cast<size_t>(len), '_'); 
    int index = 0;
    if(dir == Direction::Vertical){


        for(int i = row; i < rows.size() && index < len; i++){
            res.replace(static_cast<size_t>(index),1,1,rows.at(static_cast<size_t>(i)).at(static_cast<size_t>(col)));
            index++;
        }

    }


    else{
        if(len + col > 100){
            throw "Out of row error";
        }
    
        while(row != rows.size() && index < len){

            res.replace(static_cast<size_t>(index),1,1,rows.at(static_cast<size_t>(row)).at(static_cast<size_t>(col)));
            col++;
            index++;
            if(col == 100){//go the next row if we reached the end of the current one
                col = 0;
                ++row;
            }
        }
    }


    return res;
}




// int main(){

//     Page p1;
//     std::string s(101,'@');
//     p1.writeRange(0,0,Direction::Horizontal,101,s);
//     p1.writeRange(1,0,Direction::Vertical,7,"2345678");
//     p1.writeRange(1,0,Direction::Vertical,7,"aaaaaaa");
//     p1.writeRange(1,3,Direction::Vertical,7,"aaaaaaa");
//     p1.writeRange(0,21,Direction::Vertical,7,"asdfghjk");
//     p1.eraseData(0,0,Direction::Horizontal,8);
//     p1.eraseData(0,21,Direction::Vertical,15);
//     std::cout<<p1.readPage();
//     std::cout<<p1.readRange(0,0,Direction::Horizontal,13)<<std::endl;
//     std::cout<<p1.readRange(1,3,Direction::Vertical,7)<<std::endl;
//     std::cout<<p1.readRange(0,21,Direction::Vertical,15)<<std::endl;
//     std::cout<<p1.readRange(3,0,Direction::Horizontal,101)<<std::endl;
    

//     return 0 ;
// }