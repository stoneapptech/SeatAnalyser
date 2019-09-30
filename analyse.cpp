#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <io.h>
#include <direct.h>
int _push[36];
int _inst[36];
int _swap[36];
const int mode_inst=1, mode_swap=2, mode_push=3;
const int mode_count=3;
const int _f=1,b=2,r=3,_l=4,bl=5,br=6,fl=7,fr=8;
int seat[36];
int tmp[]= {-1,-1,-1,-1,-1,-1};
int reqs[][3]={1,_f,100,3,b,2,5,_f,3,6,_f,1000,7,fr,8,8,br,6,10,fr,3,12,fl,250,13,fl,1000,14,br,1000,15,_l,100,17,_f,10,18,_f,100,20,_f,99,21,bl,3,22,b,3,23,b,2,24,b,100,25,bl,100,26,_f,100,27,fr,100,28,_f,7,30,b,6,31,_f,1000,32,fl,99,33,bl,2,34,_f,87,36,fr,11,37,_l,6};
int order[sizeof(reqs)/sizeof(reqs[0])];
std::string numbers="0123456789";
#define renew(list) for(int i=0;i<sizeof(list)/sizeof(list[0]);i++)list[i]=-1
bool dirExists(std::string dirname){
	if(_access(dirname.c_str(),0)==0)return true;
    else return false;
}
std::string tos(int n){
	std::string l;
    int power=1, r=0;;
    while(power<=n){
        power*=10;
        r++;
    }
    while(r>0){
        power/=10;
        l+=numbers[n/power];
        n=n%power;
        r--;
    }
	if(l=="")l="0";
	return l;
}
void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}
int len(){
	for(int i=0;i<6;i++){
		if(tmp[i]==-1)return i;
	}
	return 6;
}
int length(std::string s){
	int i=0;
	while(1){
		if(s[i]=='\0')return i;
		i++;
	}
}
void PrintArr(int l[2]) {
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			if(l[i*6+j]<10) std::cout<<'0';
			std::cout<<l[i*6+j]<<' ';
		}
		std::cout<<std::endl;
	}
}
int find_place[]= {-1,-1};
void arrayfind(int *l,int number) {
	for(int i=0;i<=5;i++){
		for(int j=0;j<=5;j++){
			if (l[i*6+j]==number){
				find_place[0]=i, find_place[1]=j;
				return;
			}
		}
	}
	find_place[0]=-1, find_place[1]=-1;
}
int poss_rand[36]={0};
int poss_inst[36]={0};
int poss_swap[36]={0};
int poss_push[36]={0};
void writefile(int mode, int toana){
	int *poss;
	std::string md;
	switch(mode){
		case mode_inst:
		md="inst";
		poss=poss_inst;
		break;
		case mode_swap:
		md="swap";
		poss=poss_swap;
		break;
		case mode_push:
		md="push";
		poss=poss_push;
		break;
		default:
		md="rand";
		poss=poss_rand;
	}
	std::cout<<md<<':';
	char t;
    std::string number="";
    int l[36]={0}, index=0;
	std::fstream file;
    file.open(tos(toana)+"_"+md+".txt", std::ios::in);
	if(file){
		do{
			file.get(t);
			if(t!=' '){
				number+=t;
			}
			else{
				l[index]=atoi(number.c_str());
				number="";
				index++;
			}
		}while(index<36);
    	file.close();
	}
	std::string towrite;
	for(int x=0;x<sizeof(poss_rand)/sizeof(poss_rand[0]);x++){
		std::cout<<poss[x]<<' ';
		towrite+=tos(poss[x]+l[x]);
		towrite+=' ';
	}
	std::cout<<std::endl;
	file.open(tos(toana)+"_"+md+".txt", std::ios::out);
	file.write(towrite.c_str(),length(towrite));
	file.close();
}
void push(int index, int steps){
	if(steps>len()-index-1)steps=len()-index-1;
	int t[]= {-1,-1,-1,-1,-1,-1};
	for(int i=0;i<len();i++){
		t[i]=tmp[i];
	}
	for(int i=0;i<len();i++){
		if(i+steps>=len())tmp[i+steps-len()]=t[i];
		else tmp[i+steps]=t[i];
	}
}
void insert(int index, int steps){
	if(steps>len()-index-1)steps=len()-index-1;
	int t=tmp[index];
	for(int q=index;q<=index+steps;q++){
		if(q==index+steps)tmp[q]=t;
		else tmp[q]=tmp[q+1];
	}
}
void swap(int index, int steps){
	if(steps>len()-index-1)steps=len()-index-1;
	int t=tmp[index];
	tmp[index]=tmp[index+steps];
	tmp[index+steps]=t;
}
void right(int *l,int number,int steps,int method) {
	arrayfind(l,number);
	for(int index=0;index<=5;index++)tmp[index]=l[find_place[0]*6+index];
	switch(method){
		case mode_inst:
		insert(find_place[1], steps);
		break;
		case mode_swap:
		swap(find_place[1],steps);
		break;
		case mode_push:
		push(find_place[1], steps);
		break;
	}
	for(int j=0;j<=5;j++) l[find_place[0]*6+j]=tmp[j];
	renew(tmp);
}
void left(int *l,int number,int steps,int method){
	arrayfind(l,number);
	for(int index=0;index<6;index++){tmp[index]=l[(find_place[0]+1)*6-index-1];}
	find_place[1]=5-find_place[1];
	switch(method){
		case mode_inst:
		insert(find_place[1], steps);
		break;
		case mode_swap:
		swap(find_place[1], steps);
		break;
		case mode_push:
		push(find_place[1], steps);
		break;
	}
	for(int index=0;index<6;index++)l[find_place[0]*6+index]=tmp[len()-index-1];
	renew(tmp);
}
void down(int *l,int number,int steps,int method){
	arrayfind(l,number);
	for(int i=0;i<=5;i++)tmp[i]=l[i*6+find_place[1]];
	switch(method){
		case mode_swap:
		swap(find_place[0], steps);
		break;
		case mode_push:
		push(find_place[0], steps);
		break;
		case mode_inst:
		insert(find_place[0], steps);
		break;
	}
	for(int i=0;i<6;i++)l[i*6+find_place[1]]=tmp[i];
	renew(tmp);
}
void up(int *l,int number,int steps,int method){
	arrayfind(l,number);
	for(int i=0;i<6;i++)tmp[i]=l[(5-i)*6+find_place[1]];
	find_place[0]=5-find_place[0];
	switch(method){
		case mode_inst:
		insert(find_place[0], steps);
		break;
		case mode_swap:
		swap(find_place[0], steps);
		break;
		case mode_push:
		push(find_place[0], steps);
		break;
	}
	for(int i=0;i<6;i++)l[(5-i)*6+find_place[1]]=tmp[i];
	renew(tmp);
}
void downright(int *l,int number,int steps,int method){
	arrayfind(l,number);
	int times=0, index=0;
	while(1){
		if(find_place[0]*find_place[1]==0)break;
		find_place[0]--;
		index++;
		find_place[1]--;
	}
	while(1){
		tmp[times]=l[find_place[0]*6+find_place[1]];
		if(find_place[0]==5 or find_place[1]==5)break;
		times++;
		find_place[0]++;
		find_place[1]++;
	}
	switch(method){
		case mode_inst:
		insert(index, steps);
		break;
		case mode_swap:
		swap(index, steps);
		break;
		case mode_push:
		push(index, steps);
		break;
	}
	while(1){
		l[find_place[0]*6+find_place[1]]=tmp[times];
		find_place[0]--;
		find_place[1]--;
		times--;
		if(times<0)break;
	}

	renew(tmp);
}
void upleft(int *l,int number,int steps,int method) {
	arrayfind(l,number);
	int times=0, index=0;
	while(1){
		if(find_place[0]==5 or find_place[1]==5)break;
		find_place[0]++;
		find_place[1]++;
		index++;
	}
	while(1){
		tmp[times]=l[find_place[0]*6+find_place[1]];
		if(find_place[0]*find_place[1]==0)break;
		times++;
		find_place[0]--;
		find_place[1]--;
	}
	switch(method){
		case mode_inst:
		insert(index, steps);
		break;
		case mode_swap:
		swap(index, steps);
		break;
		case mode_push:
		push(index, steps);
		break;
	}
	while(1){
		l[find_place[0]*6+find_place[1]]=tmp[times];
		if(times==0)break;
		times--;
		find_place[0]++;
		find_place[1]++;
	}
	renew(tmp);
}
void upright(int *l,int number,int steps,int method) {
	arrayfind(l,number);
	int times=0,index=0;
	while(1){
		if(find_place[0]==5 or find_place[1]==0)break;
		find_place[0]++;
		find_place[1]--;
		index++;
	}
	while(1){
		tmp[times]=l[find_place[0]*6+find_place[1]];
		if(find_place[0]==0 or find_place[1]==5)break;
		times++;
		find_place[0]--;
		find_place[1]++;
	}
	switch(method){
		case mode_inst:
		insert(index, steps);
		break;
		case mode_swap:
		swap(index, steps);
		break;
		case mode_push:
		push(index, steps);
		break;
	}
	while(1){
		l[find_place[0]*6+find_place[1]]=tmp[times];
		if(times==0)break;
		times--;
		find_place[0]++;
		find_place[1]--;
	}
	renew(tmp);
}
void downleft(int *l,int number,int steps,int method) {
	arrayfind(l,number);
	int times=0, index=0;
	while(1){
		if(find_place[0]==0 or find_place[1]==5)break;
		index++;
		find_place[0]--;
		find_place[1]++;
	}
	while(1){
		tmp[times]=l[find_place[0]*6+find_place[1]];
		if(find_place[0]==5 or find_place[1]==0)break;
		find_place[0]++;
		find_place[1]--;
		times++;
	}
	switch(method){
		case mode_inst:
		insert(index, steps);
		break;
		case mode_swap:
		swap(index, steps);
		break;
		case mode_push:
		push(index, steps);
		break;
	}
	while(1){
		l[find_place[0]*6+find_place[1]]=tmp[times];
		if(times==0)break;
		times--;
		find_place[0]--;
		find_place[1]++;
	}
	renew(tmp);
}
//29=len(reqs)


int main(int argc, char *argv[]){
	for(int i=1, j=0;j<36;i++){
        if(i==4)continue;
        seat[j]=i;
        j++;
    }
	time_t start=time(NULL);
	srand(time(NULL));
	int final_time=-1, toana=-1;
	bool ext=0;
	if(argc==3){
		final_time=atoi(argv[2]), toana=atoi(argv[1]);
		if(!(final_time>0 and 38>toana>0 and toana!=4))ext=1;
	}
	else ext=1;
	if(ext){
		std::cout<<"please run this program with the given format:"<<std::endl;
		std::cout<<argv[0]<<" [number to find] [times to analyse]"<<std::endl;
		exit(1);
	}
	for(int i=0;i<29;i++)order[i]=i;
	for(int _times=0;_times<final_time;_times++){
		shuffle (seat,sizeof(seat)/sizeof(seat[0]));
		for(int i=0;i<36;i++){
			_push[i]=seat[i];
			_inst[i]=seat[i];
			_swap[i]=seat[i];
		}//copy the seats
		shuffle(order, sizeof(order)/sizeof(order[0]));//shuffle the order of the reqs
		for(int i=0;i<sizeof(order)/sizeof(order[0]);i++){
			int number=reqs[order[i]][0], way=reqs[order[i]][1], steps=reqs[order[i]][2];
			switch(way){
				case _f:
				up(_push, number, steps, mode_push);
				up(_swap, number, steps, mode_swap);
				up(_inst, number, steps, mode_inst);
				break;
				case b:
				down(_push, number, steps, mode_push);
				down(_swap, number, steps, mode_swap);
				down(_inst, number, steps, mode_inst);
				break;
				case r:
				right(_push, number, steps, mode_push);
				right(_swap, number, steps, mode_swap);
				right(_inst, number, steps, mode_inst);
				break;
				case _l:
				left(_push, number, steps, mode_push);
				left(_swap, number, steps, mode_swap);
				left(_inst, number, steps, mode_inst);
				break;
				case fr:
				upright(_push, number, steps, mode_push);
				upright(_swap, number, steps, mode_swap);
				upright(_inst, number, steps, mode_inst);
				break;
				case fl:
				upleft(_push, number, steps, mode_push);
				upleft(_swap, number, steps, mode_swap);
				upleft(_inst, number, steps, mode_inst);
				break;
				case br:
				downright(_push, number, steps, mode_push);
				downright(_swap, number, steps, mode_swap);
				downright(_inst, number, steps, mode_inst);
				break;
				case bl:
				downleft(_push, number, steps, mode_push);
				downleft(_swap, number, steps, mode_swap);
				downleft(_inst, number, steps, mode_inst);
				break;
			}
		}
		arrayfind(_inst, toana);
		poss_inst[find_place[0]*6+find_place[1]]++;
		arrayfind(_swap, toana);
		poss_swap[find_place[0]*6+find_place[1]]++;
		arrayfind(_push, toana);
		poss_push[find_place[0]*6+find_place[1]]++;
		arrayfind(seat, toana);
		poss_rand[find_place[0]*6+find_place[1]]++;
	}
	std::cout<<"data generated this time:"<<std::endl;
	std::string filname="data";
	if(!dirExists(filname))mkdir(filname.c_str());
	chdir(filname.c_str());
	for(int mode=0;mode<=mode_count;mode++)writefile(mode, toana);
	std::cout<<"execution time:"<<time(NULL)-start<<"secs"<<std::endl;
	return 0;
}
