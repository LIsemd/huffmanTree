#include "head.h"
/*
*	����ǰӦ����ToBeTran������ļ���գ��������  
*	�����ؽ��в���2���ܻ���������ڴ治��������޷�����Ľ�����˳����������м��� 
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
	//ͳ���ļ���ÿ����ĸ�ĸ��������࣬������Ϊ��Ȩֵ���棬������Ϊ�����
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
	//���ַ�ת��Ϊ���Եı��� 
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
	//ʵ��ѹ�� 
	//CodeHuffman();
	outfile<<results;
	outfile.close();
	return OK;
}
int Coding(HuffmanTree HT,Sqlist &CD,Number num){
	//��ʼ��Sqlist 
	CD.chars = new ElemType_2[2*HT.n];
	CD.length = HT.n;
	//����ָ��char���͵�ָ�� 
	char *buffer;
	buffer = new char[2*HT.n-1];
	int m=0,i,j,p;
	//��������������������� 
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
	//��ȡ�����ļ� 
	string code;
	ifstream infile("/CodeFile.txt");
	infile.open("CodeFile.txt");
	infile>>code;
	infile.close();
	//cout<<code;
	ofstream outfile("/TextFile.txt");
	outfile.open("TextFile.txt");
	//��������ʼ��0�����ߣ�1�����ߣ�����Ҷ�ӽ��Ϊֹ����ȡҶ�ӽ���ֵ 
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
		cout<<"��֤����"<<endl; 
	else cout<<"��������"<<endl; 
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
	cout<<"----��ӭʹ�ù������������ϵͳ----"<<endl;
	cout<<"----1.��ʼ��----------------------"<<endl;
	cout<<"----2.����------------------------"<<endl;
	cout<<"----3.���루��֤��-----------------"<<endl;
	cout<<"----4.��ӡ�����ļ�----------------"<<endl;
	cout<<"----5.�˳�------------------------"<<endl;
	cout<<"������1-5���в���"<<endl; 
	while(1){
	cin>>input;
	
	countTree(num,HT); //��ȡ�ı��и����ַ�Ȩֵ
	HT.node = InitHTNode(HT.n);
	int w[HT.n];
	for(int i=0;i<HT.n;i++){
		w[i]=num.data[i].num;
	}
	CreateHuffmanTree(HT,HT.n,w);
	if(input==1){
		outPut_hfmTree(HT); //�����ɵĹ����������浽hfmTree.txt 
		cout<<"����ɹ���"<<endl; 
	}else if(input==2){
		Coding(HT,code,num);//���ÿ���ַ��ı���
		outPut_CodeFile(code);//���ַ�ת��Ϊ���Եı���[δʵ��ѹ������]д��CodeFile.txt 
		cout<<"����ɹ���"<<endl; 
	}else if(input==3){
		DeCoding(HT,num);//���벢�����д��TextFile.txt 
		Check();//��֤����
		cout<<"����ɹ���"<<endl; 
	}else if(input==4){		 
   	 	printCode();//���ļ�CodeFile�Խ��ո�ʽ��ʾ���ն��ϣ�ÿ��50�����롣ͬʱ�����ַ���ʽ�ı����ļ�д���ļ�CodePrin��
   	 	cout<<"����ɹ���"<<endl; 
	}else if(input==5) exit(0);
	else cout<<"���������룡"<<endl; 
}
	return OK;
}
