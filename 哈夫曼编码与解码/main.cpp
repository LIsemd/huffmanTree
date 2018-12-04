#include "head.h"
/*
*	运行前应将除ToBeTran以外各文件清空，方便测试  
*	连续地进行操作2可能会出现运行内存不足而导致无法处理的结果，退出后重新运行即可 
*/

HTNode* InitHTNode(int n){
	HTNode * ht;
	int m = 2*n-1;
	ht = new HTNode[m+1];
	return ht;
}
int select(HuffmanTree &HT,int i,int &s1,int &s2){
	int min1=100,min2=100;
	for(int j=0;j<i;j++){
		if(HT.node[j].parent==-1){
			if(HT.node[j].weigth<min1){
				min2 = min1;
				min1 = HT.node[j].weigth;
				s2 = s1;
				s1 = j;
			}else if(HT.node[j].weigth<min2){
				min2 = HT.node[j].weigth;
				s2 = j; 
			}
		}
	}
	
	
	return OK;
}
int CreateHuffmanTree(HuffmanTree &HT,int n,int *w){
	int m = 2*n-1,i;
	for(i=0;i<n;i++){
		HT.node[i].weigth = w[i];
		HT.node[i].parent = -1;
		HT.node[i].lchrld = -1;
		HT.node[i].rchrld = -1;
	}
	int s1=0,s2=0;
	for(i=n;i<m;i++){
		select(HT,i,s1,s2);
		HT.node[i].weigth = HT.node[s1].weigth+HT.node[s2].weigth;
		HT.node[i].parent = -1;
		HT.node[i].lchrld = s1;
		HT.node[i].rchrld = s2;
		HT.node[s1].parent =i;
		HT.node[s2].parent =i; 
	}
	for(i=0;i<m;i++){
		if(HT.node[i].parent==-1) HT.r = i;
	} 	
	return OK;
}
int countTree(Number &num,HuffmanTree &HT){
	//统计文件中每种字母的个数与种类，个数作为其权值保存，种类作为结点数
	string str;
	ifstream infile("/ToBeTran.txt"); 
	infile.open("ToBeTran.txt");
	getline(infile,str);
	int i,j;	
	num.length=0;
	for(i=0;i<str.length();i++){
		int count=0;
		num.data[i].num=0;
		for(j=0;j<num.length;j++){
			if(str[i]!=num.data[j].ch)
				count++;
			else
				num.data[j].num++;
		}
		if(count==num.length){
			num.data[num.length].ch=str[i];
			num.data[j].num++;
			num.length++;
		}
	}	
		HT.n=num.length;
		HT.m = HT.n*2-1;
		infile.close();
	return OK;
}
int outPut_CodeFile(Sqlist &CD){
	//将字符转化为各自的编码 
	string str,results;
	ifstream infile("/ToBeTran.txt"); 
	ofstream outfile("/CodeFile.txt"); 
	infile.open("ToBeTran.txt");
	getline(infile,str);
	infile.close();	
	outfile.open("CodeFile.txt");
	for(int i=0;i<str.length();i++){
		for(int j=0;j<CD.length;j++){
			if(str[i]==CD.chars[j].data)
				results+=CD.chars[j].code;
		}
	}
	//实现压缩 
	//CodeHuffman();
	outfile<<results;
	outfile.close();
	return OK;
}
int Coding(HuffmanTree HT,Sqlist &CD,Number num){
	//初始化Sqlist 
	CD.chars = new ElemType_2[2*HT.n];
	CD.length = HT.n;
	//定义指向char类型的指针 
	char *buffer;
	buffer = new char[2*HT.n-1];
	int m=0,i,j,p;
	//遍历哈夫曼树，逐个编码 
	for(int k=0;k<HT.n;k++){
		i=k;
		p=m-1;
		string code;
		while(HT.node[i].parent!=-1){
			j=HT.node[i].parent;
			if(HT.node[j].lchrld==i) buffer[m++]='0'; 
			else buffer[m++]='1';
			i=j;
		}
		for(int q=m-1;q>p;q--){
			code+=buffer[q];
		}
		CD.chars[k].code = code;
		CD.chars[k].data = num.data[k].ch;

	}	
	/*	
		0111	T
		11100	H
		001		I
		1010	S
		100		
		11101	P
		010		R	
		1011	O
		11110	G
		1100	A
		1101	M
		11111	Y
		0000	F
		0001	V
		0110	E
	*/
	return OK;
} 
int outPut_hfmTree(HuffmanTree HT){
	ofstream huffmanTree("/hfmTree.txt");
	huffmanTree.open("hfmTree.txt");
	huffmanTree<<"i\tweigth\tparent\tlchrld\trchrld"<<endl;
	for(int i=0;i<HT.m;i++){
		huffmanTree<<i<<"\t";
		huffmanTree<<HT.node[i].weigth<<"\t";
		huffmanTree<<HT.node[i].parent<<"\t";
		huffmanTree<<HT.node[i].lchrld<<"\t";
		huffmanTree<<HT.node[i].rchrld<<endl;
	} 	
	huffmanTree.close();
	return OK;
}
int DeCoding(HuffmanTree HT,Number num){
	//获取编码文件 
	string code;
	ifstream infile("/CodeFile.txt");
	infile.open("CodeFile.txt");
	infile>>code;
	infile.close();
	//cout<<code;
	ofstream outfile("/TextFile.txt");
	outfile.open("TextFile.txt");
	//从树根开始，0向左走，1向右走，到达叶子结点为止，获取叶子结点的值 
	int j=0;
	while(j<code.length()){
		int i=HT.r;
		while(HT.node[i].lchrld!=-1&&HT.node[i].rchrld!=-1){
			if(code[j]=='0') {
				i = HT.node[i].lchrld; 
				j++;
			}else  {
				i = HT.node[i].rchrld; 
				j++;
			}
		}
		 outfile<<num.data[i].ch;	
	}
	outfile.close();
	return OK; 
}
int Check(){
	string str_ToBeTran;
	string str_TextFile;
	ifstream ToBeTran("/ToBeTran.txt");
	ifstream TextFile("/TextFile.txt");
	ToBeTran.open("ToBeTran.txt");
	ToBeTran>>str_ToBeTran;
	//cout<<str_ToBeTran<<endl;
	TextFile.open("TextFile.txt");
	TextFile>>str_TextFile;
	//cout<<str_TextFile;
	int count=0;
	for(int i=0;i<str_ToBeTran.length();i++){
		if(str_ToBeTran[i]==str_TextFile[i]) count++;
	}
	if(str_ToBeTran.length()==str_TextFile.length()&&count==str_ToBeTran.length())
		cout<<"验证无误！"<<endl; 
	else cout<<"数据有误！"<<endl; 
	ToBeTran.close();
	TextFile.close();
	return OK;
}
int printCode(){
	string str;
	ifstream infile("/CodeFile.txt");
	infile.open("CodeFile.txt");
	getline(infile,str);
	infile.close();
	ofstream outfile("/CodePrin.txt");
	outfile.open("CodePrin.txt");
	for(int i=0;i<str.length();i++){
		if(i%50==0&&i!=0)
		{
			cout<<endl;
			outfile<<endl;
		}
		cout<<str[i];
		outfile<<str[i];
	}
	outfile.close();
	return OK;
}
int main(){
	HuffmanTree HT;
	Sqlist code;
	Number num;
	int input;
	cout<<"----欢迎使用哈夫曼编码测试系统----"<<endl;
	cout<<"----1.初始化----------------------"<<endl;
	cout<<"----2.编码------------------------"<<endl;
	cout<<"----3.译码（验证）-----------------"<<endl;
	cout<<"----4.打印代码文件----------------"<<endl;
	cout<<"----5.退出------------------------"<<endl;
	cout<<"请输入1-5进行操作"<<endl; 
	while(1){
	cin>>input;
	
	countTree(num,HT); //获取文本中各个字符权值
	HT.node = InitHTNode(HT.n);
	int w[HT.n];
	for(int i=0;i<HT.n;i++){
		w[i]=num.data[i].num;
	}
	CreateHuffmanTree(HT,HT.n,w);
	if(input==1){
		outPut_hfmTree(HT); //将生成的哈夫曼树保存到hfmTree.txt 
		cout<<"处理成功！"<<endl; 
	}else if(input==2){
		Coding(HT,code,num);//获得每个字符的编码
		outPut_CodeFile(code);//将字符转化为各自的编码[未实现压缩功能]写入CodeFile.txt 
		cout<<"处理成功！"<<endl; 
	}else if(input==3){
		DeCoding(HT,num);//解码并将结果写入TextFile.txt 
		Check();//验证操作
		cout<<"处理成功！"<<endl; 
	}else if(input==4){		 
   	 	printCode();//将文件CodeFile以紧凑格式显示在终端上，每行50个代码。同时将此字符形式的编码文件写入文件CodePrin中
   	 	cout<<"处理成功！"<<endl; 
	}else if(input==5) exit(0);
	else cout<<"请重新输入！"<<endl; 
}
	return OK;
}
