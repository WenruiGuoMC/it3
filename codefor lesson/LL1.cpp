#include<bits/stdc++.h>  // 万能头 
using namespace std ; 

// 先完成初始化 //
// 在主函数定义变量时不使用栈内空间 使用堆的空间 栈小堆大 可以防止递推数据过大爆栈
// 同时此时定义的变量 以及初始化为空或者0 很方便
char s ; 
int n , num , len , cnt , flag ; 
string str , post ; 
map<char,int> wa , wb ;     //标记输入顺序 wa是非终结符 wb是终结符
map<int,char> aw , bw ; 
string data[10][3] ;                    //用来记录输入的生成式
bool first[20][10] , follow[20][10] ; 
bool st[10] ; 

int made_first(char i); 
int made_follow(char i) ; 

signed main(){


    cin >> n ; 
    cnt = 1 ; 
    wb['@'] = 0 , bw[0] = '@' ; 


    while(n --){
        cin >> str ; 

        // 分割生成式
        data[num][0] = str.substr(0,1) ; 
        post = str.substr(3) ; 
        data[num][1] =  post; 


        // 完成wa wb建立
        wa[str[0]] = num ; 
        aw[num] = str[0] ; 

        
        len = post.length() ; 
        for(int i = 0 ; i < len ; i ++){
            if(wb.count(post[i]) == 0 && post[i] >= 'a' && post[i] <= 'z'){
                wb.insert(pair<char,int>(post[i],cnt)) ; 
                bw.insert(pair<int,char>(cnt,post[i])) ; 
                cnt ++ ; 
            }
        }


        num ++ ; 
    }
    wb['#'] = cnt , bw[cnt] = '#' ; 



    //生成first and follow集
    for(auto it : wa) made_first(it.first) ; 
    follow[wa['S']][cnt] = 1 ;
    for(auto it : wa) made_follow(it.first) , cout << endl ; 
    

    // 输出
    for(int i = 0 ; i < num ; i ++){
        cout << "first[" << aw[i] << "] =" ;
        for(int j = 0 ; j <= cnt ; j ++){
            if(first[wa[aw[i]]][j]){
                cout<< " " << bw[j] ; 
            }
        }
        cout << endl; 
    }

    for(int i = 0 ; i < num ; i ++){
        cout << "follow[" << aw[i] << "] =" ;
        for(int j = 0 ; j <= cnt ; j ++){
            if(follow[i][j]){
                cout<< " " << bw[j] ; 
            }
        }
        cout << endl; 
    }
}


int made_first(char i){
// cout <<'*'<< i ; 
    if(isupper(i)){
        string t = data[wa[i]][1] ;
// cout << t << endl;  
        if(isupper(t[0])){
            int ans = made_first(t[0]) ; 
            for(int j = 0 ; j <= cnt ; j ++){
                first[wa[i]][j] = first[ans][j] ; 
            }
        }
        else{
            int where = wb[t[0]] ; 
            first[wa[i]][where] = 1 ; 
// cout << wa[i] << ' '<< where << ' '  << t[0] << ' ' << endl; 
        }
    }
    return wa[i] ; 
}

bool notstop(int x , string t){
    if((t[x] >= 'a' && t[x] <= 'z') || t[x] == '@') return true ;
    else return false ; 
}

int made_follow(char x){

    int s = wa[x] ; 
    // cout << x << endl; 
    if(st[s]) return s ; 

    for(int i = 0 ; i < num ; i ++){
        if(s == i) continue; 

        string t = data[i][1] ; 
        int len = t.length() ;

        for(int ii = 0 ; ii < len ; ii ++)
        {
            if(t[ii] != x) continue; 

            // cout << t << endl; 
            for(int j = 0 ; j < len ; ){
                if(t[j] != x) j ++ ; 

                if(j < len - 1 && notstop(j+1 ,t)){
                    // cout << 1 << endl; 
                    int ss = wb[t[j+1]] ; 
                    follow[s][ss] = 1 ; 
                    break;
                }
                else if(j == len - 1){
                    // cout << 2 << endl; 
                    for(int w = 0 ; w <= cnt ; w ++){
                        follow[s][w] |= follow[i][w] ; 
                    }
                    break;
                }
                else{
                    // cout << t[j+1] << ' ' << t << ' ' <<j << endl;
                    while(first[wa[t[j+1]]][0] && j+1 < len){
                        j ++ ; 
                    }
                    // cout << j << ' ' << t[j+1] << endl; 
                    if(j < len && t[j+1] != x){
                        // cout << 3 << endl; 
                        for(int w = 0 ; w <= cnt ; w++){
                            follow[s][w] |= first[wa[t[j+1]]][w] ; 
                        }
                        break;
                    }
                    else {
                        for(int w = 0 ; w <= cnt ; w ++){
                            follow[s][w] |= follow[i][w] ; 
                        }
                        break;
                    }  
                }
            }  
        }
    }
    //     for(int i = 0 ; i < num ; i ++){
    //     cout << "follow[" << aw[i] << "] =" ;
    //     for(int j = 0 ; j <= cnt ; j ++){
    //         if(follow[i][j]){
    //             cout<< " " << bw[j] ; 
    //         }
    //     }
    //     cout << endl; 
    // }
    // cout << endl; 

    st[s] = 1 ; 
    return s ; 
}



